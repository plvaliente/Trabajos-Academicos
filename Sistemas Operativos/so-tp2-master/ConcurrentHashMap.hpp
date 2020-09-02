#include <string>
#include <map>
#include <list>
#include <vector>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include "ListaAtomica.hpp"

using std::string;
using std::pair;
using std::map;
using std::list;
using std::make_pair;
using std::vector;
using std::ifstream;

#define CANT_LETRAS 26

class ConcurrentHashMap
{
public:
    ConcurrentHashMap();

    //Igual que addAndInc pero suma n en vez de 1, y crea los pares (key, n) si key no existe.
    void addAndIncN(string key, unsigned int n);
    
    void addAndInc(string key);
    
    bool member(string key);

    unsigned int search(string key);

    pair<string, unsigned int> maximum(unsigned int nt);

    static ConcurrentHashMap count_words(string arch);

    static ConcurrentHashMap count_words(list<string> archs);

    static ConcurrentHashMap count_words(unsigned int n, list<string> archs);

    static pair<string, unsigned int> maximum(unsigned int p_archivos, unsigned int p_maximos, list<string> archs);

    static pair<string, unsigned int> maximum_concurrente(unsigned int p_archivos, unsigned int p_maximos, list<string> archs);

    map<int, Lista<pair<string, unsigned int> >* > tabla;

private:
    map<char, pthread_mutex_t*> mutexes;
};
