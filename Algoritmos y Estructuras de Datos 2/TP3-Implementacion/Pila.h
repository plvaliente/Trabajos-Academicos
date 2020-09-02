/*
 * Author: grupo_14
 *
 * Pila.
 * 
 */

#ifndef MODULOS_PILA_H_
#define MODULOS_PILA_H_

#include <ostream>
#include "aed2/Lista.h"

namespace modulos {
  
    template<typename T>
    class Pila {
        public:
            Pila();
            Pila(const Pila& otra);
            ~Pila();
            Pila<T>& operator=(const Pila<T>& otra);
            void apilar(T elem);
            bool esVacia();
            const T& tope();
            T desapilar();
        private:
            aed2::Lista<T> lista;
    };
    
    template<class T>
    std::ostream& operator << (std::ostream& os, const Pila<T>& p);

    template<class T>
    bool operator == (const Pila<T>& l1, const Pila<T>& k2);
    
    template <typename T>
    Pila<T>::Pila() {
        this->lista = aed2::Lista<T>();
    }
    
    template <typename T>
    Pila<T>::Pila(const Pila<T>& otra)
    {
      // TODO la idea es que haga shallow copy?
      // Pense que por convencon definiamos este operador con deep copy
      // de hecho el operador = hace deep copy
      *this = otra;
    }
    
    template <typename T>
    void Pila<T>::apilar(T elem) {
        (this->lista).AgregarAtras(elem);
    }
    
    template <typename T>
    bool Pila<T>::esVacia() {
        return (this->lista).EsVacia();
    }
    
    template <typename T>
    const T& Pila<T>::tope() {
        return (this->lista).Ultimo();
    }
    
    template <typename T>
    T Pila<T>::desapilar() {
        T res = lista.Ultimo();
        lista.Comienzo();
        return res;
    }
    
    template <typename T>
    Pila<T>& Pila<T>::operator = (const Pila<T>& otra)
    {
      // Limpio mi pila
      while( !esVacia() ) {
        desapilar();
      }
      Pila<T> aux = otra;
      // Copio la otra pila
      while( !aux.esVacia() ) {
        apilar(aux.tope());
        aux.desapilar();
      }
    
      return *this;
    }
    
    template <typename T>
    Pila<T>::~Pila()
    {
      while(!esVacia()) {
        desapilar();
      }
    }
    
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Pila<T>& p)
    {
      return os;
    }
    
    template <typename T>
    bool operator == (const Pila<T>& l1, const Pila<T>& l2)
    {
      Pila<T> aux = l1;
      Pila<T> aux2 = l2;
      while(!aux.esVacia() && !aux2.esVacia() && aux.tope() == aux2.tope()) {
          aux.desapilar();
          aux2.desapilar();
      }
      return aux.esVacia() && aux2.esVacia();
    }
    
}
#endif 