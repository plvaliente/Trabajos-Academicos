import re
import math


class DomainSearchHelper:

    # Regex used
    regex_str = r"""
          (?:"|')                               # Start newline delimiter
          (
            ((?:[a-zA-Z]{1,10}://|//)           # Match a scheme [a-Z]*1-10 or //
            [^"'/]{1,}\.                        # Match a domainname (any character + dot)
            [a-zA-Z]{2,}[^"']{0,})              # The domainextension and/or path
            |
            ((?:/|\.\./|\./)                    # Start with /,../,./
            [^"'><,;| *()(%%$^/\\\[\]]          # Next character can't be...
            [^"'><,;|()]{1,})                   # Rest of the characters can't be
            |
            ([a-zA-Z0-9_\-/]{1,}/               # Relative endpoint with /
            [a-zA-Z0-9_\-/]{1,}                 # Resource name
            \.(?:[a-zA-Z]{1,4}|action)          # Rest + extension (length 1-4 or action)
            (?:[\?|#][^"|']{0,}|))              # ? or # mark with parameters
            |
            ([a-zA-Z0-9_\-/]{1,}/               # REST API (no extension) with /
            [a-zA-Z0-9_\-/]{3,}                 # Proper REST endpoints usually have 3+ chars
            (?:[\?|#][^"|']{0,}|))              # ? or # mark with parameters
            |
            ([a-zA-Z0-9_\-]{1,}                 # filename
            \.(?:php|asp|aspx|jsp|json|
                 action|html|js|txt|xml)        # . + extension
            (?:[\?|#][^"|']{0,}|))              # ? or # mark with parameters
          )
          (?:"|')                               # End newline delimiter
        """

    invalid_substrings = ['.png','.jpg','.mp4','.mp3']

    def get_http_in_js(self, response):
        regex = re.compile(self.regex_str, re.VERBOSE)
        http_endpoints = list()
        matches_in_js = [(m.group(1), m.start(0), m.end(0)) for m in re.finditer(regex, response.text)]
        for match in matches_in_js:
            if 'http' in list(match)[0] and '.js' not in list(match)[0] and '.css' not in list(match)[0]:
                if not any(substring in list(match)[0] for substring in self.invalid_substrings):
                    http_endpoints.append(list(match)[0])

        return http_endpoints

    def get_css_in_url(self, session, url):

        regex = re.compile(self.regex_str, re.VERBOSE)

        try:
            response = session.get(url, verify = False)
        except Exception:
            return []

        all_matches = [(m.group(1), m.start(0), m.end(0)) for m in re.finditer(regex, response.text)]
        css_endpoints = list()
        for match in all_matches:
            if '.css' in list(match)[0] and 'http' in list(match)[0]:
                css_endpoints.append(list(match)[0])

        return css_endpoints


    @staticmethod
    def check_scope(url_list, domain):

        if domain == 'None':
            return url_list
        else:
            tmp = list()
            for url in url_list:
                split_url = url.split('/')
                try:
                    # Este es un mal intento de poda. Basicamente primero descartamos los //
                    # Despues descartamos todo lo que sea un parametro, ya que pueden haber un monton de llamadas a
                    # otras direcciones que pasan como parametro el dominio
                    # Finalmente validamos que el dominio este de la manera http://<dominio> o http://www.<dominio>
                    split_url = split_url[2].split('?')
                    if domain in split_url[0]:
                        tmp.append(url)
                except IndexError:
                    continue

        return tmp

    @staticmethod
    def sufficient_string_entropy(string):

        """Calculate the entropy of a string."""
        entropy = 0
        for number in range(256):
            length = len(string.encode('utf-8'))
            result = float(string.encode('utf-8').count(number)) / length
            if result != 0:
                entropy = entropy - result * math.log(result, 2)

        if entropy >= 4:
            return True
        else:
            return False

    @staticmethod
    def normalize_list(listToFix):

        output = listToFix
        output = filter(None, output)
        output = [item for sublist in output for item in sublist]
        output = list(dict.fromkeys(output))

        return output
