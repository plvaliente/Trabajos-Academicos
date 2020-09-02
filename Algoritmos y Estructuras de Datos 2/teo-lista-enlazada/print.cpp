#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include <execinfo.h>
#include <cxxabi.h>

#include "print.h"

#ifndef nullptr
#define nullptr 0
#endif

Print& Print::get_instance() {
    if(print.get() == nullptr) {
        print.reset(new Print());
    }
    return *print;
}

void Print::set(bool val) {
    this->do_print = val;
}

void Print::output(std::ostream* os) {
    this->os = os;
    do_print = false;
}

Print::Print() : os(&(std::cerr)) {
    do_print = false;
}

std::auto_ptr<Print> Print::print(nullptr);


std::string call(std::string command, std::string args) {

    FILE* raw_res = popen((command + args).c_str(), "r");
    std::string res; 
    char c;
    while ((c = fgetc(raw_res)) != EOF) { // standard C I/O file reading loop
        res += c;
    }
    pclose(raw_res);
    return res;
}


void Print::stacktrace(int from_frame, int skip_frames, int max_frames)
{    
    // storage array for stack trace address data
    void* addrlist[max_frames];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, max_frames);
    assert(addrlen != 0);

    // resolve addresses into strings containing "filename(function+offset) [address]",
    // this array must be free()-ed
    char** symbollist = backtrace_symbols(addrlist, addrlen);
    assert(symbollist != nullptr);

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for (int i = addrlen-skip_frames-1; i >= from_frame; i--)
    {
        std::istringstream trace(symbollist[i]);

	// find parentheses and +address offset surrounding the mangled name:
	// ./module(function+0x15c) [0x8048a6d]     
        std::string module; std::getline(trace, module, '(');
        std::string address; std::getline(trace, address, '['); std::getline(trace, address, ']');
        
        std::istringstream addr2line(call("/usr/bin/addr2line -C -f -i -e ", module + ' ' + address));
        std::string function; std::getline(addr2line, function);
        std::string filename; std::getline(addr2line, filename, ':');
        filename = filename.substr(filename.find_last_of('/')+1);
        std::string line; std::getline(addr2line, line);
        line = line.substr(0, line.find(' '));
        
        *os << filename << ":" << line << " " << function << std::endl;
        
    }

    free(symbollist);
}


