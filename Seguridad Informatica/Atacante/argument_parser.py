import argparse

def make_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("--host", help="URL of the host to attack", required = True)
    parser.add_argument("-p", "--port", help="Port of the host to attack", type=int, default=80)
    parser.add_argument("-sn", "--sockets", help="Number of sockets to use in the attack", type=int, default=200)
    parser.add_argument("-sl", "--sleep", help="Number of seconds to delay between sending headers", type=int,
                        default=15)
    parser.add_argument("-pt", "--pages_threshold", help="Approximate number of max pages to explore", type=int,
                        default=50)
    return parser


def print_help():
    parser = make_parser()
    parser.print_help()

def parse_arguments(args = None):
    parser = make_parser()
    args = parser.parse_args(args)
    return args
