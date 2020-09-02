#ifndef MEJOR_H
#define MEJOR_H

#include "ArregloDimensionable.h"

template<typename T>
const T& mejor(ArregloDimensionable<T>& ad) {
	typename T::Criterio criterio;
    int mejor = 0;
    for (int i = 1; i < ad.tamanio(); i++) {
        if (criterio.esMejor(ad.iesimo(i), ad.iesimo(mejor)))
            mejor = i;
    }
    return ad.iesimo(mejor);
}

template<>
const int& mejor(ArregloDimensionable<int>& ad) {
    int mejor = 0;
    for (int i = 1; i < ad.tamanio(); i++) {
        if (ad.iesimo(i) > ad.iesimo(mejor))
            mejor = i;
    }
    return ad.iesimo(mejor);
}

template<typename T, typename Comparador>
const T& mejor(ArregloDimensionable<T>& ad, Comparador comp) {
    int mejor = 0;
    for (int i = 1; i < ad.tamanio(); i++) {
        if (comp.esMejor(ad.iesimo(i), ad.iesimo(mejor)))
            mejor = i;
    }
    return ad.iesimo(mejor);
}

#endif // MEJOR_H
