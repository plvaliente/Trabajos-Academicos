
#ifndef LISTA_H
#define LISTA_H

#include <cassert> //agrega assert.

//Implementacion del modulo Lista(Elem) que se explica con el TAD Secuencia(Elem) 
//VERSION 1: nada implementado; solo la estructura.
//
//Para entender qué hace cada operacion, hay que entender el TAD Secuencia(Elem).
//Despues hay cuestiones que dependen del lenguaje.
//
//El modulo Lista(Elem) deberia proporcionar las siguientes complejidades temporales:
//
// - lista(), agregar_adelante, agregar_atras, primero, sacar_primero, ultimo, sacar_ultimo, longitud en O(1)
// - concatenar(otra) en O(longitud(otra))
// - esta(l, x) en tiempo O(longitud(l))
template<class Elem>
class lista {
    
    //Vamos a representar una secuencia usando un puntero al primer elemento de una lista circular! + un natural para la longitud
    //Recordar el uso de punteros y memoria dinamica visto en AED1
    //
    //Implementacion de la lista circular.  Uno nodo conoce al siguiente y al anterior.
    struct Nodo {
        Elem elem;
        Nodo* siguiente;
        Nodo* anterior;
    };
    
    //Representacion de la lista un único puntero al primero y un natural para la longitud
    Nodo* prim;
    unsigned int lon;
    
public:
    /** Constructores **/
    
    //construye <>
    lista();
    
    //transforma this en e * this
    void agregar_adelante(Elem e);

    /** Observadores **/
    
    //retorna prim(this)
    Elem primero();
    
    //retorna vacia?(this)
    bool es_vacia();
    
    //transforma this en fin(this)
    void sacar_primero();
    
    /** Otras operaciones **/
    
    //retorna ult(this)
    Elem ultimo();
    
    //transforma l en l ° e
    void agregar_atras(Elem e);

    //transforma this en com(this)
    void sacar_ultimo();
    
    //transforma this en this & other
    void concatenar(lista<Elem> otra);

    
    //Retorna long(this)
    unsigned int longitud();
};

//Funciones que quedan fuera de la estructura porque se pueden resolver por fuera con la misma eficiencia
//Nota: esto es un ejemplo, no tiene que estar afuera necesariamente, al igual que hay otras operaciones
//que podrian no estar adentro.
template<class Elem>
bool esta(lista<Elem> l, Elem x) {
    
}

#endif