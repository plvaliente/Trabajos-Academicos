
#ifndef LISTA_H
#define LISTA_H

#include <cassert> //agrega assert.
#include <utility> //agrega swap (para copy-and-swap).  Notar que hacer swap es fundamental y mas dificil de lo que parece; ver libro de C++.

//Obs: nullptr es un concepto del estandar C++11.  Antes vamos a usar 0, que no es lo mismo, pero bueh...
#define nullptr 0

//Implementacion del modulo Lista(Elem) que se explica con el TAD Secuencia(Elem) 
//VERSION 4: pasa el test basico y el test de constructores, pero hace muchas copias en el test de eficiencia de copias.
//
//El modulo Lista(Elem) deberia proporcionar las siguientes complejidades temporales:
//
// - lista(), primero, ultimo, longitud  en O(1)
// - agregar_adelante, agregar_atras en O(1) copias
// - sacar_primero, sacar_ultimo en O(1) destruccion
// - concatenar(otra) en O(longitud(otra)) copias
// - esta(l, x) en tiempo O(longitud(l))
// 
// - copia y asignacion: O(longitud(copiando)) copias
// - swap (funcion importante!): en O(1)
//
// REQUIERE:
// Elem es copiable (podria no ser asignable y no tener constructor por defecto)
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
        Nodo(Elem e, Nodo* p, Nodo* a) : elem(e) { //invoca al constructor por copia
            siguiente = p; anterior = a;
            siguiente->anterior = this;
            anterior->siguiente = this;
        }
        
        //Constructor de un nodo "circular"
        Nodo(Elem e) : elem(e) {
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
    lista(lista& other) {
        //Ojo!, no podemos modificar other
        lon = 0; prim = nullptr;
        if(other.es_vacia()) return;
        
        agregar_atras(other.prim->elem);
        for(Nodo* iter = other.prim->siguiente; iter != other.prim; iter = iter->siguiente) {
            agregar_atras(iter->elem);
        }
    }
    
    //Operador de asignacion.  Se invoca cuando se asigna una lista a otro.
    //La idea es copiar la lista, asi que nos aprovechamos de un "idioma" de C++:
    // - recibimos el argumento por copia y simplemente "pasamos" la estructura de other a la nueva lista
    //Ojo!: hay que eliminar los elementos de this y a la vez eliminar el aliasing entre this y other.  Por eso, conviene hacer el swap.
    //Desventaja: en el caso de hacer this = this, cuesta O(longitud) cuando podria costar O(1).  No nos importa.
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

//Funcion global de swap, para que la encuentre la biblioteca estandar
template<class Elem, class T>
void swap(lista<Elem>& l, lista<T>& other) {
    l.swap(other);
}

#endif