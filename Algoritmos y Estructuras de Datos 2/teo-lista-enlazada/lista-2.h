
#ifndef LISTA_H
#define LISTA_H

#include <cassert> //agrega assert.

//Obs: nullptr es un concepto del estandar C++11.  Antes vamos a usar 0, que no es lo mismo, pero bueh...
#define nullptr 0

//Implementacion del modulo Lista(Elem) que se explica con el TAD Secuencia(Elem) 
//VERSION 2: compila y ejecuta, pero no funciona correctamente: tiene un segmentation fault y pierde memoria.
//Ejecutar: valgrind --leack-check=yes <ejecutable>
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
        
        //Constructor de un nodo que se agrega a una lista no vacia.
        //Dado un puntero p al siguiente nodo y otro a al anterior, crea el nodo correspondiente y
        //actualiza los nodos apuntados por p y a para "reencadenar" correctamente sus nodos.
        //
        //Requiere: p != nullptr; a != nullptr (podria ocurrir p == a)
        Nodo(Elem e, Nodo* p, Nodo* a) {
            elem = e;
            siguiente = p; anterior = a;
            siguiente->anterior = this;
            anterior->siguiente = this;
        }
        
        //Constructor de un nodo "circular"
        Nodo(Elem e) {
            elem = e;
            siguiente = anterior = this;
        }
    };
    
    //Representacion de la lista un único puntero al primero y un natural para la longitud
    Nodo* prim;
    unsigned int lon;
        
public:
    /** Constructores **/
    
    //construye <>
    lista() {
        lon = 0;
        //este paso no es necesario, porque podemos usar lon para saber si la lista esta vacia.
        //Pero..., esta bueno no tener un puntero a algo "valido"
        prim = nullptr;
    }    
    
    //transforma this en e * this
    void agregar_adelante(Elem e) {
        prim = es_vacia() ? new Nodo(e) : new Nodo(e, prim, prim->anterior);
        ++lon;
    };

    /** Observadores **/
    
    //retorna prim(this)
    Elem primero() {
        return prim->elem;
    };
    
    //retorna vacia?(this)
    bool es_vacia() {
        return lon == 0;
    };
    
    //transforma this en fin(this)
    void sacar_primero() {
        Nodo* removido = prim;
        prim->siguiente->anterior = prim->anterior;
        prim->anterior->siguiente = prim->siguiente;
        --lon;
        prim = es_vacia() ? nullptr : prim->siguiente;
        delete removido;
    };
    
    /** Otras operaciones **/
    
    //retorna ult(this)
    Elem ultimo() {
        return prim->anterior->elem;
    };
    
    //transforma l en l ° e
    void agregar_atras(Elem e) {
        agregar_adelante(e);
        prim = prim->siguiente;
    }

    //transforma this en com(this)
    void sacar_ultimo() {
        prim = prim->anterior;
        sacar_primero();
    }
    
    //transforma this en this & other
    void concatenar(lista<Elem> otra) {
        //Hay una implementacion trivial, pero requiere de mas conceptos; la dejamos para mas adelante.
    }
    
    //Retorna long(this)
    unsigned int longitud() {
        return lon;
    };
};

//Funciones que quedan fuera de la estructura porque se pueden resolver por fuera con la misma eficiencia
//Nota: esto es un ejemplo, no tiene que estar afuera necesariamente, al igual que hay otras operaciones
//que podrian no estar adentro.
template<class Elem>
bool esta(lista<Elem> l, Elem x) {
    while(not l.es_vacia() and l.primero() != x)
        l.sacar_primero();
    
    return not l.es_vacia();
}

#endif