
#ifndef LISTA_H
#define LISTA_H

#include <cassert> //agrega assert.
#include <utility> //agrega swap (para copy-and-swap).  Notar que hacer swap es fundamental y mas dificil de lo que parece; ver libro de C++.

#include "print.h"


//Implementacion del modulo Lista(Elem) que se explica con el TAD Secuencia(Elem)
//VERSION 8: agrega move semantics, que permite evitar algunas copias de Elem.  Tambien agrega la semantica para evitar copias de listas.
//Notar que todavia tenemos que destruir una lista para resolver la funcion esta.
//
//El modulo Lista(Elem) deberia proporcionar las siguientes complejidades temporales:
//
// - lista(), primero, ultimo, longitud  en O(1)
// - agregar_adelante, agregar_atras en O(1) copias u movimientos
// - sacar_primero, sacar_ultimo en O(1) destruccion
// - concatenar(otra) en O(longitud(otra)) copias si hay que copiar
//   concatenar(otra) requiere O(1) en la version de movimiento.
// - esta(l, x) en tiempo O(longitud(l))
// 
// - copia y asignacion: O(longitud(copiando)) copias, o un movimiento si es un rvalue
//
// REQUIERE:
// Elem es copiable (podria no ser asignable y no tener constructor por defecto)
// o Elem es movible.
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
        Nodo(const Elem& e, Nodo* p, Nodo* a) : Nodo(Elem(e),p,a) {}
        
        Nodo(Elem&& e, Nodo* p, Nodo* a) : elem(std::move(e)) {
            siguiente = p; anterior = a;
            siguiente->anterior = this;
            anterior->siguiente = this;            
        }
        
        //Constructor de un nodo "circular".
        Nodo(const Elem& e) : Nodo(Elem(e)) {}
        
        Nodo(Elem&& e) : elem(std::move(e)) {
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
    
    //destruye la lista, liberando la memoria.  Se invoca cada vez que se elimina una lista
    ~lista() {
        while(not es_vacia()) sacar_primero();
    }
    
    //Constructor por copia.  Se invoca cada vez que se copia una lista, ya sea explicitamente (e.g., lista<int> copia(l)) o implicitamente
    //cuando se invoca una funcion que toma una lista o cuando se retorna un valor de lista.
    //Tiene que tomar una referencia!!!!.  Sino, se haria una copia recursiva!!!
    lista(const lista& other) {
        PRINT("Copia de una lista -> costo lineal.");
        
        //Ojo!, no podemos modificar other
        lon = 0; prim = nullptr;
        if(other.es_vacia()) return;
        
        agregar_atras(other.prim->elem);
        for(Nodo* iter = other.prim->siguiente; iter != other.prim; iter = iter->siguiente) {
            agregar_atras(iter->elem);
        }
    }
    
    //Constructor por movimiento.  Se invoca cada vez que se copia una lista que es un rvalue.
    //Notar que hay que dejar a la lista other en un estado valido, aunque pierda sus datos.
    //La solucion mas simple, invocar al constructor por defecto (C++11) y luego swap
    lista(lista&& other) : lista() {
        PRINT("Movimiento de una lista -> costo constante");
        
        swap(other);
    }
    
    //Operador de asignacion.  Se invoca cuando se asigna una lista a otro.  
    //La idea es copiar la lista, asi que nos aprovechamos del "idioma" de C++, aunque la copia se explicita
    //Ojo!: hay que eliminar los elementos de this y a la vez eliminar el aliasing entre this y other.  Por eso, conviene hacer el swap.
    //Desventaja: en el caso de hacer this = this, cuesta O(longitud) cuando podria costar O(1).  No nos importa.
    //
    //C++11.  En C++11 el parametro other puede ser una copia (cuando other proviene de un lvalue) o un movimiento
    //(cuando other proviene de un rvalue).  No lo tenemos que decidir nosotros; lo hace el compilador.
    //Nosotros simplemente seguimos el copy-and-swap.
    lista& operator=(lista other) {
        swap(other);
        return *this;
    }
    
    //Funcion de swap.  Es tan importante que va junto a los constructores!!!
    template<class T>
    void swap(lista<T>& other) {
        using std::swap;
        swap(prim, other.prim);
        swap(lon, other.lon);
    }

    
    //transforma this en e * this
    void agregar_adelante(const Elem& e) {
        //Ahora usamos la version de movimiento, luego de copiar.
        agregar_adelante(Elem(e));
    };

    //transforma this en e * this, traspasando e al domino de this (es decir, no copia)
    void agregar_adelante(Elem&& e) {
        //Obs: e es un lvalue; tenemos que usar std::move para "reconvertirlo" al rvalue
        prim = es_vacia() ? new Nodo(std::move(e)) : new Nodo(std::move(e), prim, prim->anterior);
        ++lon;
    };

    /** Observadores **/
    
    //retorna prim(this)
    Elem& primero() {
        return prim->elem;
    };
    
    const Elem& primero() const {
        return prim->elem;
    }
    
    //retorna vacia?(this)
    bool es_vacia() const {
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
    Elem& ultimo() {
        return prim->anterior->elem;
    };
    
    const Elem& ultimo() const {
        return prim->anterior->elem;
    }

    
    //transforma l en l ° e
    void agregar_atras(const Elem& e) {
        //copiar y mover
        agregar_atras(Elem(e));
    }
    
    //transforma l en l ° e, traspasando e al domino de this (es decir, no copia)
    void agregar_atras(Elem&& e) {
        //Obs: e es un lvalue; tenemos que usar std::move para "reconvertirlo" al rvalue
        agregar_adelante(std::move(e));
        prim = prim->siguiente;
    };


    //transforma this en com(this)
    void sacar_ultimo() {
        prim = prim->anterior;
        sacar_primero();
    }
    
    //transforma this en this & other.  Otra vez usamos la estrategia copy-and-swap.
    //Notar que si other es rvalue, entonces se llamo al constructor por
    //movimiento.  Ergo, no hubo copia!!!
    void concatenar(lista<Elem> other) {
        //Ya copiamos la lista otra.  Entonces, podemos "pasar" la estructura, como hacemos en el operador de asignacion.
        //La diferencia es que no hay que eliminar los elementos de this, pero si borrar el aliasing.
        if(other.es_vacia()) return;
        if(es_vacia()) {
            swap(other);
            return;
        }

        //Para no meter la pata, me acuerdo de los nodos involucrados
        Nodo* a = prim, *b = prim->anterior, *c = other.prim, *d = other.prim->anterior;

        a->anterior = d;
        c->anterior = b;
        b->siguiente = c;
        d->siguiente = a;
        lon += other.lon;
        
        //borramos el aliasing de otra, porque se va a llamar a su destructor
        other.prim = nullptr; other.lon = 0;
    }
    
    //Retorna long(this)
    unsigned int longitud() const {
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

//Funcion global de swap, para que la encuentre la biblioteca estandar
template<class Elem, class T>
void swap(lista<Elem>& l, lista<T>& other) {
    l.swap(other);
}

#endif