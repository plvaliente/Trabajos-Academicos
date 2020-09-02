/*
 * Author: grupo_14
 *
 * DiccStr.
 * 
 */

#ifndef MODULOS_DICCSTR_H_
#define MODULOS_DICCSTR_H_

#include <ostream>
//#include "../modulos/Pila.h"
//#include "aed2/Arreglo.h"
#include "aed2.h"
#include "Pila.h"
//#include <string>


//using namespace std;



namespace modulos {
    template<typename T>
    class DiccStr {
        public:
            DiccStr();                      //Constructor
            DiccStr(const DiccStr&);        //Constructor por copia
            ~DiccStr();                     //Destructor 
            DiccStr<T>& operator=(const DiccStr<T>&); //Asignación
            bool Definido(String) const;          //Retorna si la clave esta definida
            void Definir(String, const T&);       //Define la clave s y el significado a
            T& Obtener(String) const;              //Retorna el Significado de la clave s por ref.
            void Borrar(String);             //Borra la clave s con su significado
            String MinimaClave() const;             //Retorna la minima clave del diccionario por ref.
            String MaximaClave() const;             //Retorna la máxima clave del diccionario por ref.
            
        private:
          // la representación de un nodo interno.
          struct Nodo
          {
           
              T* significado;               //Significado del nodo
              Arreglo<Nodo*> prefijos;      //Puntero a los hijos de cada nodo (1 por cada caracter en ASCII)
              Nodo(){
               significado = NULL;
               Arreglo<Nodo*> a (256);
               prefijos = a;
               
              }
          };
  
            Nodo* raiz;                              //Puntero a la raíz de nuestro árbol.
            bool todoNULL(Arreglo<Nodo*> a) const;
            Nodo* copiarNodo(const Nodo* original);  //copia recursivamente un Nodo
            void DestruirNodo(Nodo* borrar);         //borra nodos 
        
    };
    

template <class T>
DiccStr<T>::DiccStr(){ //Constructor
    Nodo* nuevo = new Nodo;
    nuevo->significado = NULL;
    raiz = nuevo;
    //Arreglo<Nodo*> a (256);
    /*for(int i=0; i<=255; i++){
        a.Borrar(i);
    }
    assert(todoNULL(a));*/
    //nuevo->prefijos = a;

    
}     


template <class T>
DiccStr<T>::DiccStr(const DiccStr& otra): raiz(NULL){   //Constructor por copia
    *this = otra;
}


template <class T>
bool DiccStr<T>::todoNULL(Arreglo<Nodo*> a) const{
    bool res = true;
    Nat i = 0;
    while (i < a.Tamanho()){
        if (a.Definido(i)){
            res = false;
        }
        i++;
    }
    return res;
}


template <class T>
DiccStr<T>::~DiccStr(){                     //Destructor 
    if (raiz != NULL){
        Nodo* actual = this->raiz;
        String s;
        while(!(todoNULL(actual->prefijos))){
            s = MinimaClave();
            Borrar(s);
            }
        delete raiz; //probando
        raiz = NULL;
    }
}


template <class T>
DiccStr<T>& DiccStr<T>::operator=(const DiccStr<T>& otra){ //Asignación
    DestruirNodo(raiz);    
    raiz = copiarNodo(otra.raiz);
}


template <class T>
bool DiccStr<T>::Definido(String s) const{          //Retorna si la clave esta definida
    assert (raiz != NULL);
    int i = 0;
    bool noesta = false;
    Nodo* actual = this->raiz;
    while(i < s.length() && (! noesta)){
        if (!(actual->prefijos.Definido(s[i]))){
            noesta = true;
        }else{
            actual = actual->prefijos[s[i]];
        }
        i++;
    }
    return (!(noesta) && (actual->significado != NULL));    
}


template <class T>
void DiccStr<T>::Definir(String s, const T& a){       //Define la clave s y el significado a
    assert (raiz != NULL);
    int i = 0;
    Nodo* actual = this->raiz;
    while(i < s.length() ){
        if (!(actual->prefijos.Definido(s[i]))){
            Nodo* nuevo = new Nodo;
            assert(todoNULL(nuevo->prefijos));
            assert(nuevo->significado == NULL);
            actual->prefijos.Definir(s[i], nuevo );
            assert(actual->prefijos.Definido(s[i]));
        }
        assert(actual->prefijos.Definido(s[i]));
        actual = actual->prefijos[s[i]];
        i++;
        
    }
    actual->significado = new T(a);
    assert(Definido(s));
}


template <class T>
T& DiccStr<T>::Obtener(String s) const{              //Retorna el Significado de la clave s por ref.
    assert(Definido(s));
    int i = 0;
    Nodo* actual = this->raiz;
    while(i < s.length() ){
        actual = actual->prefijos[((int) s[i])];
        i++;
        }
    return *(actual->significado);
}

template <class T>
bool hayHermanos(const Arreglo<T*> a){
    Nat j = 0;
    Nat i = 0;
    while (i < a.Tamanho() && (j < 2)){
        if (a.Definido(i)){
            j++;
        }
        i++;
    }
    return (j == 2);
}


template <class T>
void DiccStr<T>::Borrar(String s){             //Borra la clave s con su significado

assert(Definido(s));
    int i = 0;
    Pila<Nodo*> p;  
    Nodo* actual = this->raiz;
    p.apilar(actual);
    while(i < s.length() ){
        actual = actual->prefijos[((int) s[i])];
        p.apilar(actual);
        i++;
    }
    p.desapilar(); //probando algo
    delete actual->significado; //va a perder memoria si no libero el significado
    actual->significado = NULL;
    if (todoNULL(actual->prefijos)){
        Nodo* ant = actual;
        while(!(hayHermanos(actual->prefijos)) && (actual->significado == NULL) && !(p.esVacia())){
            for(int i = 0; i<=255; i++){
                if(actual->prefijos.Definido(i)){
                    //actual->prefijos[i] = NULL; probando
                    actual->prefijos.Borrar(i);
                }
            }
            ant = actual;
           // ant->prefijos.~Arreglo<Nodo*>(); PRUEBA NO DESCOMENTAR
            delete ant; //esta bien borrar el nodo aca?
            actual = p.desapilar();
        }
        if(actual != ant){
            for(int i = 0; i<=255; i++){
                if(actual->prefijos.Definido(i)){
                    if(actual->prefijos[i] == ant){ // aca entra asi los punteros quedan apuntando bien
                        //actual->prefijos[i] = NULL; probando
                        actual->prefijos.Borrar(i);
                    }
                }
            }
        }
    }

}


template <class T>
String DiccStr<T>::MinimaClave() const{             //Retorna la minima clave del diccionario por ref.
    Nodo* actual=this->raiz;
    assert(!todoNULL(actual->prefijos));
    String res;
    bool tengoPrefijo = false;
    bool encontreMin = false;
    while(! encontreMin){
        if(actual->significado != NULL){
            encontreMin = true;
        }else{
            int i = 0;
            while(i < 256 && ! tengoPrefijo){
                if(actual->prefijos.Definido(i)){
                    actual = actual->prefijos[i];
                    tengoPrefijo = true;
                    res.push_back((char) i);
                }
                i++;
            }
            tengoPrefijo = false;
        }
    }
    return res;
}

template <class T>
String DiccStr<T>::MaximaClave() const{             //Retorna la máxima clave del diccionario por ref.
    Nodo* actual= this->raiz;
    assert(!todoNULL(actual->prefijos));
    String res;
    bool tengoPrefijo = false;
    bool encontreMax = false;
    while(! encontreMax){
        if(actual->significado != NULL){
            encontreMax = true;
        }else{
            int i = 255;
            while(i >= 0 && ! tengoPrefijo){
                if(actual->prefijos.Definido(i)){
                    actual = actual->prefijos[i];
                    tengoPrefijo = true;
                    res.push_back((char) i);
                }
                i--;
            }
            tengoPrefijo = false;
        }
    }
    return res;
}

    template <class T>
    typename DiccStr<T>::Nodo* DiccStr<T>::copiarNodo(const Nodo* original){
        if (original == NULL) {
            return NULL;
        } else{
            Nodo* copia = new Nodo;
            copia->significado = original->significado; //acordarse de alocar, no lo hacemos porq no hay 
            Arreglo<Nodo*> a (256);                     //const. por copia de varias cosas  
            copia->prefijos = a;
            if( !(todoNULL(original->prefijos)) ){
                for(int i = 0; i<=255; i++){
                    if(original->prefijos.Definido(i)){
                        //copia->prefijos[i] = copiarNodo(original->prefijos[i]);
                        copia->prefijos.Definir(i, copiarNodo(original->prefijos[i]));
                    }
                }
            }
            return copia;
        }
    }
    
    template <class T>
    void DiccStr<T>::DestruirNodo(Nodo* borrar){
        if(borrar != NULL){
            if(borrar->significado != NULL ){
                delete borrar->significado;
            }
            if( !(todoNULL(borrar->prefijos)) ){
                for(int i = 0; i<=255; i++){
                    if(borrar->prefijos.Definido(i)){
                        DestruirNodo(borrar->prefijos[i]);
                    }
                }
            }
            delete borrar;
            borrar= NULL;
        }
    }
    
}




#endif 