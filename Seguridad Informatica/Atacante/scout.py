import grequests
import domain_search_helper as dsh
import sys

import re
from concurrent.futures import ThreadPoolExecutor
from bs4 import BeautifulSoup, SoupStrainer
import time


def correct_status_code(status_code):
    return status_code == 200 or status_code == 404 or status_code == 403 or \
           (status_code >= 200 and status_code < 300)


def filter_non_usable_responses(responses):
    return [i for i in responses if i is not None and \
            correct_status_code(i.status_code)]

# Regex para validar que un link esta completo o es relativo (hrefs)
hyperlink_validator_regex =  re.compile(
        r'^(?:http|ftp)s?://' # http:// or https://
        r'(?:(?:[A-Z0-9](?:[A-Z0-9-]{0,61}[A-Z0-9])?\.)+(?:[A-Z]{2,6}\.?|[A-Z0-9-]{2,}\.?)|' #domain...
        r'localhost|' #localhost...
        r'\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})' # ...or ip
        r'(?::\d+)?' # optional port
        r'(?:/?|[/?]\S+)$', re.IGNORECASE)


# Realizar los requests para todas las URLs pasadas, pero filtrar aquellas que hayan
# salido por timeout o devuelto algun otro codigo de resultado inesperado
def run_requests(urls):
    rs = (grequests.get(u, timeout=5) for u in urls)
    rs = grequests.map(rs, stream=True, size=8, gtimeout=60)
    rs = filter_non_usable_responses(rs)
    return rs


class RelativeScout:

    def __init__(self, url):
        # Listado de URLs canonicas para mantener un registro de aquellas que fueron visitadas. Sirve como politica para
        # restringir el horizonte de busqueda del Crawler, y podar pedidos que no ofrecen mucha nueva informacion
        # (por ejemplo, urls identicas pero con parametros distintos)
        self.http_endpoints_checked = [url]
        # Diccionario con los resultados de URLs completas y el tiempo de duración del pedido
        self.results = {}
        self.url_origin = url
        split_url_by_slash = url.split('/')
        split_url_by_dot = split_url_by_slash[2].split('.')
        if split_url_by_dot[0] == "www":
            self.domain = split_url_by_slash[2][4:]
        else:
            self.domain = split_url_by_slash[2]
        self.domain_searcher = dsh.DomainSearchHelper()
        self.politeness_sleep = 0.3

    @staticmethod
    def filter_parameters(url):
        return url.split('?')[0]

    # Cambie el if que checkea si esta la key en el caso de que haya un timeout
    # asi no la vuelve a checkear
    def search_suburls(self, url):
        if self.filter_parameters(url) not in self.http_endpoints_checked:
            #print("Found: " + url + ". Dict length is " + str(len(self.results)))
            self.http_endpoints_checked.append(self.filter_parameters(url))
            self.scout_vulnerable_requests(url)

    def add_domain_if_needed(self, link, father):
        if re.match(hyperlink_validator_regex, link['href']):
            return link['href']
        else:
            father_split = father.split('/')
            return father[:(len(father) - len(father_split[len(father_split) - 1]))] + link['href']


    # Parsear el HTML obtenido y analizarlo para encontrar URLs a nuevos recursos o paginas a navegar
    def search_in_page(self, response):
        # Hardcodeado en el constructor, politica de politeness
        time.sleep(self.politeness_sleep)

        endpoints = self.domain_searcher.get_http_in_js(response)
        
        # Filtrar aquellas que no sean parte del dominio a atacar, parte de la politica de seleccion
        endpoints = self.domain_searcher.check_scope(endpoints, self.domain)

        # Buscamos los hrefs con BeautifulSoup
        bsoup_hyperlinks = [self.add_domain_if_needed(link, response.url) for link in
                            BeautifulSoup(response.text, parse_only=SoupStrainer('a'),
                            features='html.parser') if link.has_attr('href') and link['href'] and
                            link['href'][0] != '#']

        bsoup_hyperlinks = self.domain_searcher.check_scope(bsoup_hyperlinks,
                self.domain)

        filtered_endpoints = list(set(endpoints + bsoup_hyperlinks))
        return filtered_endpoints

    # Agregar las responses a las estructuras necesarias si hace falta
    def add_responses_to_results(self, response_list):
        for r in response_list:
            # Revisar en funcion a un request ya hecho, si la diferencia de tiempo es tan grande como para
            # poder suponer si la pagina esta cacheada en el server. Si es el caso, se la descarta
            if (r.url in self.results and self.results[r.url] is not None and \
                 (r.elapsed.total_seconds()/ self.results[r.url]) <= 0.1):
                del self.results[r.url]
                continue

            rf = self.filter_parameters(r.url)
            # Consultar si la version canonica de la url ya fue visitada
            if rf not in self.all_explored_pages:
                # Guardar la url canonica para marcarla como visitada
                self.all_explored_pages.append(rf)
                # Guardar el resultado para la url con los parametros asi se puede recrear el request
                self.results[r.url] = r.elapsed.total_seconds()

    # Resuelve problema de intentar parsear paginas que no son HTMLs en las cuales BeatifulSoup falla
    # de la manera menos graceful existente
    def is_html_response(self, response):
        return response.headers["Content-Type"].upper() == 'TEXT/HTML; CHARSET=UTF-8'

    def scout_vulnerable_requests(self, url_scout, results_threshold=None):
        # Armamos una lista con el url inicial, medio hacky pero hay problemas
        # si usamos grequests y request.
        response = run_requests([url_scout])[0]
        self.results[response.url] = response.elapsed.total_seconds()

        # Marcar la url canonicas como visitadas
        self.all_explored_pages = list(self.filter_parameters(url_scout))

        to_explore = self.search_in_page(response)
        to_explore = list(set(to_explore))

        tp = ThreadPoolExecutor(max_workers=8)

        while len(to_explore):
            print("Running requests for the following urls")
            print('[%s]' % ', '.join(map(str, to_explore)))

            # Corremos el request para todos las urls que queremos explorar, dos veces, la segunda para revisar la condicion de cache
            rs_first = run_requests(to_explore)
            rs_check_cache = run_requests(to_explore)

            self.add_responses_to_results(rs_first)
            self.add_responses_to_results(rs_check_cache)

            if results_threshold and len(self.results) > results_threshold:
                break

            # Parseamos el texto en paralelo con el threadpool
            new_to_explore = tp.map(self.search_in_page, [r for r in rs_first if self.is_html_response(r) and r.text[0:15].upper() == "<!DOCTYPE HTML>"])

            # Esto devuelve una lista de listas, la aplanamos, la pasamos a un
            # set para sacar los repetidos y luego la volvemos a convertir en
            # una lista.
            to_explore = list(set([i for l in new_to_explore for i in l]))

            # Filtramos los links que no hayamos visto (incluye urls que no son
            # de la página).
            to_explore = [i for i in to_explore if self.filter_parameters(i) not in self.all_explored_pages]


def main(url, results_threshold):
    scout = RelativeScout(url)
    try:
        scout.scout_vulnerable_requests(url, results_threshold)
        # Algunos links se agregan aunque timeoutean, los remuevo, sino tira error
        # al sortear
        sortedEndpoints = sorted(scout.results.items(), key=lambda item: item[1], reverse=True)
        sys.stdout.flush()
        print("Sorted endpoints")
        for i in sortedEndpoints:
            print (i)

    except (KeyboardInterrupt, SystemExit):
        print("Found pages: {}".format(scout.results))


if __name__ == '__main__':
    main(sys.argv[1], int(sys.argv[2]))
