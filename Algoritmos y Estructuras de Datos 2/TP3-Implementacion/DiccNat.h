/*
 * Author: grupo_14
 *
 * DiccNat.
 * 
 */

#ifndef MODULOS_DICCNAT_H_
#define MODULOS_DICCNAT_H_

#include <ostream>

#include "aed2.h"
//#include "Basicos.h"

namespace modulos {
    template<typename T>
    class DiccNat {
        public:
            DiccNat();                              //Constructor
            DiccNat(const DiccNat<T>&);             //Constructor por copia
            ~DiccNat();                             //Destructor 
            DiccNat<T>& operator =(const DiccNat<T>&);  //Asignación
            bool Definido(Nat) const;               //Retorna si la clave esta definida
            void Definir(Nat, T&);                  //Define la clave n y el significado a
            T& Obtener(Nat) const;                  //Retorna el Significado de la clave n por ref.
            void Borrar(Nat);                       //Borra la clave n con su significado
            Nat& MinimaClave() const;               //Retorna la minima clave del diccionario por ref.
            Nat& MaximaClave() const;               //Retorna la máxima clave del diccionario por ref.
        
        private:
          // la representación de un nodo interno.
          struct Nodo
          {
              Nodo(const T& v, Nat& n) : significado(v), clave(n), izq(NULL), der(NULL){}   //Constructor
//              Nodo(const T& v) : significado(v), izq(NULL), der(NULL){}   //Constructor
              Nodo() : izq(NULL), der(NULL){}       //Constructor de nodo sin parametros  
              Nat clave;                            //Clave del nodo
              T significado;                        //Significado del nodo
              Nodo* izq;                            //Puntero a la raíz del subárbol izquierdo.
              Nodo* der;                            //Puntero a la raíz del subárbol derecho.
          };
            Nodo* copiarNodo(const Nodo* original); //copia recursivamente un Nodo
            Nodo* raiz;                             //Puntero a la raíz de nuestro árbol.
            void DestruirNodo(Nodo* borrar);         //borra nodos             
    };


    template <typename T>   
    DiccNat<T>::DiccNat(){                 //Constructor
        raiz = NULL;
    }
    
    template <typename T>
    DiccNat<T>::DiccNat(const DiccNat<T>& otro) : raiz(NULL){        //Constructor por copia
        *this = otro;
    }
    
    template <typename T>
    DiccNat<T>::~DiccNat(){                             //Destructor
        while(raiz != NULL){
            Borrar(raiz->clave);
        }
    }
    
    template <typename T>
    bool DiccNat<T>::Definido(Nat n) const{
        Nodo* actual = raiz;
        while(actual != NULL && actual->clave != n){
            if(actual->clave > n){
                actual = actual->izq;
            }
            else{
                actual = actual->der;
            }
        }
        return (actual != NULL);
    }
    
    template <typename T>
    void DiccNat<T>::Definir(Nat n, T& sign) {
        // aca no se asignaba nunca cuando era vacio, osea raiz
        // Ciro: Para mi ahora debería andar bien.
        // por alguna razon no anda, (double free or corruption) 
        if(raiz == NULL){
            raiz = new Nodo(sign,n);
        }
        else{
            Nodo* actual = raiz;
            Nodo* padre = raiz;
            while(actual != NULL && actual->clave != n){
                padre = actual;
                if(actual->clave > n ){
                    actual = actual->izq;
                }
                else{
                    actual = actual->der;
                }
            }
            if(actual == NULL){
                if(padre->clave > n){
                    padre->izq = new Nodo(sign, n);
                }
                else{
                    padre->der = new Nodo(sign, n);
                }
            }
            else{
                actual->significado = sign;
            }
        }
    }

    
    template <typename T>
    T& DiccNat<T>::Obtener(Nat n) const{
        assert(Definido(n));
        Nodo* actual = raiz;
        while(actual != NULL && actual->clave != n){
            if(actual->clave > n){
                actual = actual->izq;
            }
            else{
                actual = actual->der;
            }
        }
        return actual->significado;
    }

    template <typename T>
    void DiccNat<T>::Borrar(Nat n) {
        assert(Definido(n));
        Nodo* actual = raiz;
        Nodo* padre = NULL;
        Nodo* borrar = NULL;                            //Acá voy a guardar el nodo a liberar de memoria
        while(actual->clave != n){
            padre = actual;
            if(actual->clave > n){
                actual = actual->izq;
            }
            else{
                actual = actual->der;
            }
        }
        if(padre == NULL){
            borrar = actual;
            if(actual->izq == NULL){
                raiz = actual->der;
            }
            else if(actual->der == NULL){
                raiz = actual->izq;
            }
            else{
                Nodo* maximo = actual->izq;
                Nodo* padreMax = actual;
                while(maximo->der != NULL){
                    padreMax = maximo;
                    maximo = maximo->der;
                }
                actual->clave = maximo->clave;
                actual->significado = maximo->significado;
                if(padreMax->der == maximo){
                    padreMax->der = maximo->izq;
                }
                else{
                    padreMax->izq = maximo->izq;
                }
                borrar = maximo;
            }
        }
        else if(actual->izq == NULL){
            if(padre->izq == actual){
                padre->izq = actual->der;
            }
            else{
                padre->der = actual->der;
            }
            borrar = actual;
        }
        else{
            if(actual->der == NULL){
                if(padre->izq == actual){
                    padre->izq = actual->izq;
                }
                else{
                    padre->der = actual->izq;
                }
                borrar = actual;
            }
            else{
                Nodo* maximo = actual->izq;
                Nodo* padreMax = actual;
                while(maximo->der != NULL){
                    padreMax = maximo;
                    maximo = maximo->der;
                }
                actual->clave = maximo->clave;
                actual->significado = maximo->significado;
                if(padreMax->der == maximo){
                    padreMax->der = maximo->izq;
                }
                else{
                    padreMax->izq = maximo->izq;
                }
                borrar = maximo;
            }
        }
        delete borrar;
    }
    
    template <typename T>
    Nat& DiccNat<T>::MinimaClave() const{
        assert(raiz != NULL);
        Nodo* min = NULL;
        Nodo* actual = raiz;
        while(actual != NULL){
            min = actual;
            actual = actual->izq;
        }
        return min->clave;
    }
    
    template <typename T>
    Nat& DiccNat<T>::MaximaClave() const{
        assert(raiz != NULL);
        Nodo* max = NULL;
        Nodo* actual = raiz;
        while(actual != NULL){
            max = actual;
            actual = actual->der;
        }
        return max->clave;
    }
    template <typename T>
    void  DiccNat<T>::DestruirNodo(Nodo* borrar){         //borra nodos     
    if (borrar != NULL){
        DestruirNodo(borrar->izq);
        DestruirNodo(borrar->der);
        delete borrar;
        borrar=NULL;
    }
        
    }
    
    template <typename T>
    DiccNat<T>& DiccNat<T>::operator = (const DiccNat<T>& otro){
        DestruirNodo(raiz);
        raiz = copiarNodo(otro.raiz);
    }
    
    template <class T>
    typename DiccNat<T>::Nodo* DiccNat<T>::copiarNodo(const Nodo* original){
        if(original == NULL){
            return NULL;
        }
        else{
            Nodo* copia = new Nodo();
            copia->significado = original->significado;
            copia->clave = original->clave;
            copia->izq = copiarNodo(original->izq);
            copia->der = copiarNodo(original->der);
            return copia;            
        }
    }
    
}
#endif 