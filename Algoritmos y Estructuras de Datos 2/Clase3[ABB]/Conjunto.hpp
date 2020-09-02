#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <assert.h>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si éste ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // borra un elemento del conjunto. Si éste no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:

        // la representación de un nodo interno.
        struct Nodo
        {
            // el constructor, toma el elemento al que representa el nodo.
            Nodo(const T& v);
            // el elemento al que representa el nodo.
            T valor;
            // puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // puntero a la raíz del subárbol derecho.
            Nodo* der; 
        };

        Nodo* buscarPadre(const T&) const;
        Nodo* dameInmediato(Nodo* nodo) const;    
        // puntero a la raíz de nuestro árbol.
        Nodo* raiz;
        unsigned int _cardinal;

};

template <class T>
Conjunto<T>::Conjunto() : raiz(NULL), _cardinal(0)
{}

template <class T>
Conjunto<T>::~Conjunto(){ 
    while(raiz != NULL){
        remover(raiz->valor);
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
	bool value = false;
	Nodo* pos = raiz;
	if(pos != NULL){
		while(pos != NULL && pos->valor != clave ){
			if(clave > pos->valor){
				pos = pos->der;
			}
			else{
				pos = pos->izq;
			}
		}
		if(pos != NULL){
			value = true;
		}	
	}	
    return value;
}

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
//	assert(not pertenece(clave));
	if(raiz == NULL){
		raiz = new Nodo(clave);
	}
	else{
        Nodo* pos = raiz;
        while(pos != NULL){
            if(clave > pos->valor){
                pos = pos->der;
            }
            else{
                pos = pos->izq;
            }
        }
    	pos = new Nodo(clave);
    	}	
	_cardinal++;
}

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
     : valor(v), izq(NULL), der(NULL)
{}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    assert(cardinal() > 0 && pertenece(clave));
    char vengoDe; 
    Nodo* padre;
    Nodo* del = NULL;
    if(cardinal() < 4){
        padre = raiz;
    }
    else{
        padre = buscarPadre(clave);
        del = NULL;   
    }
    if(clave > padre->valor){
        del = padre->der;
        vengoDe = 'd';
    }
    else if(clave == padre->valor){
        del = padre;
        vengoDe = 'r';
    }
    else{
        del = padre->izq;
        vengoDe = 'i';
    }
    if(del->izq == NULL && del->der == NULL){
        delete del;
        if(vengoDe == 'd'){
            padre->der = NULL;
        }
        else if (vengoDe == 'r'){
            raiz = NULL;
        }
        else{
            padre->izq = NULL;
        }
        del = NULL;
    }
    else{
        if(del->izq == NULL && del->der != NULL){
            if(vengoDe == 'd'){
                padre->der = del->der;
                delete del;
                del = NULL; 
            }
            else if (vengoDe == 'r'){
                raiz = raiz->der;
                delete del;
                del = NULL;
            }
            else{
                padre->izq = del->der;
                delete del;
                del = NULL; 
            }
        }    
        else{
            if(del->izq != NULL && del->der == NULL){
                if(vengoDe == 'd'){
                    padre->der = del->izq;
                    delete del;
                    del = NULL; 
                }
                else if (vengoDe == 'r'){
                    raiz = raiz->izq;
                    delete del;
                    del = NULL;
                }
                else{
                    padre->izq = del->izq;
                    delete del;
                    del = NULL; 
                }
            }
            else{
                Nodo* suple = dameInmediato(del);       // Busco el proximo inmediato [pi]     
                del->valor = suple->valor;              // Guardo el valor [vpi] 
                delete suple;                           // elimino el elem. pi
                suple = NULL;                           // y le asigo vpi a clave
            }
        }   
    }
    _cardinal--;
}
template <class T>
const T& Conjunto<T>::minimo() const {
    assert(cardinal() > 0);
    Nodo* pos = raiz;
	while(pos->izq != NULL){
		pos = pos->izq;
	} 
    return pos->valor;
}
template <class T>
const T& Conjunto<T>::maximo() const {
    assert(cardinal() > 0);
    Nodo* pos = raiz;
	while(pos->der != NULL){
		pos = pos->der;
	} 
    return pos->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscarPadre(const T& clave) const {
    Nodo* prev = raiz;
    Nodo* pos = NULL;
    if(clave > prev->valor){
        pos = prev->der;
    }
    else{
        pos = prev->izq;
    }
    while( pos->valor != clave ){
        prev = pos;
        if(clave > pos->valor){
            pos = pos->der;
        }
        else{
            pos = pos->izq;
        }
    }
    return prev;
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::dameInmediato(Nodo* nodo) const{
    Nodo* aux = nodo->der;
    while(aux->izq != NULL){
        aux = aux->izq;
    }
    return aux;
}

#endif // CONJUNTO_HPP_
