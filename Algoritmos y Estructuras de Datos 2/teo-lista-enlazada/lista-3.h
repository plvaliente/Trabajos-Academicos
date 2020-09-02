
#ifndef LISTA_H
#define LISTA_H

#include <cassert> //agrega assert.
#include <utility> //agrega swap (para copy-and-swap).  Notar que hacer swap es fundamental y mas dificil de lo que parece; ver libro de C++.

//Obs: nullptr es un concepto del estandar C++11.  Antes vamos a usar 0, que no es lo mismo, pero bueh...
#define nullptr 0

//Implementacion del modulo Lista(Elem) que se explica con el TAD Secuencia(Elem) 
//VERSION 3: pasa un test basico sin perder memoria.  No funciona a no ser que Elem sea construible por defecto y asignable.
//
//El modulo Lista(Elem) deberia proporcionar las siguientes complejidades temporales:
//
// - lista(), agregar_adelante, agregar_atras, primero, sacar_primero, ultimo, sacar_ultimo, longitud en O(1)
// - concatenar(otra) en O(longitud(otra))
// - esta(l, x) en tiempo O(longitud(l))
// 
// - copia y asignacion: O(longitud(copiando))
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
        std::swap(prim, other.prim);
        std::swap(lon, other.lon);
        return *this;
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
        //TODO: hay que sacar este codigo duplicado a una funcion auxiliar.  Esto es simplemente una explicacion.
        if(es_vacia()) {
            std::swap(prim, other.prim);
            std::swap(lon, other.lon);
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

#endif