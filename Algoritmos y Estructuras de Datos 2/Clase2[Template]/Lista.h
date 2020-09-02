#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include <ostream>

typedef unsigned long Nat;

template <typename T>
class Lista
{
	public:

		/**
		 * Constructor por defecto.
		 * Crea una lista enlazada vacía. ( Operación Vacia() )
		 */
		Lista();

		/**
		 * Constructor por copia.
		 * Crea, por copia, una lista enlazada. (operación Copiar())
		 */
		Lista(const Lista& otra);

		/**
		 * Destructor.
		 * Destruye la lista, incluyendo los elementos 'T' alojados.
		 */
		~Lista();

		/**
		 * Operacion de asignacion.
		 * Recrea a la lista como una copia de la pasada como parámetro.
		 */
		Lista<T>& operator=(const Lista<T>& otra);

		//observadores

		/**
		 * Devuelve la cantidad de elementos almacenados en la lista.
		 */
		Nat longitud() const;

		/**
		 * Devuelve el i-esimo elemento (versión modificable)
		 */
		T& iesimo(Nat i);

		/**
		 * Devuelve el i-esimo elemento (versión no modificable)
		 */
		const T& iesimo(Nat i) const;

		/**
		 * Operacion de comparacion.
		 * Retorna verdadero si la lista es igual a otra pasada como
		 * parámetro, falso en caso contrario.
		 */
		bool operator==(const Lista<T>& otra) const;

		// algunas operaciones de lista

		/**
		 * Agrega un nuevo elemento como primer elemento de la lista.
		 */
		void agAdelante(const T& elem);

		/**
		 * Agrega un nuevo elemento como último elemento de la lista.
		 */
		void agAtras(const T& elem);

		/**
		 * Elimina al i-ésimo elemento de la lista.
		 */
		void eliminar(Nat i);

		/**
		 * Muestra la lista en un ostream
		 * formato de salida: [a_0, a_1, a_2, ...], donde a_i es
		 * el resultado del "mostrar" el elemento i de la lista
		 */
		void mostrar(std::ostream& o) const;

		template <typename S>
		friend std::ostream& operator<<(std::ostream& os, const Lista<S> &l);

	private:

		struct Nodo {
			T dato;
			Nodo* sig;
		};

		Nat len;
		Nodo* prim;
		Nodo* fin;
};

template <typename T>
Lista<T>::Lista()
	: len(0), prim(NULL), fin(NULL) {
}

template <typename T>
Lista<T>::Lista(const Lista& otra) {
	Lista<T> aux = Lista<T>();
	int i = 0;
	while (i < otra.longitud()){
		aux.agAtras(otra.iesimo(i));
		i++;
	}
	len = aux.longitud();
	prim = aux.prim;
	fin = aux.fin;
}

template <typename T>
Lista<T>::~Lista() {
   while(longitud() > 0){
     eliminar(0);
   } 
 }


template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra) {
	Lista<T> aux = Lista<T>();
	unsigned int i = 0;
	while (i < otra.longitud()){
		aux.agAtras(otra.iesimo(i));
		i++;
	}
	return aux;
}

template <typename T>
Nat Lista<T>::longitud() const {
	return len;
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
 	if(longitud() - 1 < i){
    	throw "NO SE PUEDE VIEJA";
  	}
  	Nodo* iesimo = prim;
  	for(i ; i>0 ; i--){
   		iesimo = iesimo->sig;
  	}
  	return *iesimo->dato;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
  	if(longitud() - 1 < i){
    	throw "NO SE PUEDE VIEJA";
  	}
  	Nodo* iesimo = prim;
  	for(i ; i>0 ; i--){
    	iesimo = iesimo->sig;
  	}
  	return *iesimo->dato;
 }

template <typename T>
bool Lista<T>::operator==(const Lista<T>& otra) const {
	bool value;
	if(longitud() == otra.longitud()){
		if(longitud() == 0){
			value = true;
		}
		else{
			Nat i = 0;
			while(i < longitud()){
				if(iesimo(i) != otra.iesimo(i)){
					value = false;
				}
				i++;
			}
		}
	}
	else{
		value = false;
	}
	return value;
}

template <typename T>
void Lista<T>::agAdelante(const T& elem) {
	/**
	 * COMPLETAR!!!
	 */
}

template <typename T>
void Lista<T>::agAtras(const T& elem) {
	/**
	 * COMPLETAR!!!
	 */
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
	/**
	 * COMPLETAR!!!
	 */
}

template <typename T>
void Lista<T>::mostrar(std::ostream& o) const {
	/**
	 * COMPLETAR!!!
	 */
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Lista<T> &l) {
	l.mostrar(os);
	return os;
}
#endif // LISTA_H_


// ListaAlumnos::ListaAlumnos()
//   : len(0), prim(NULL), fin(NULL) {
// }

// //ListaAlumnos::ListaAlumnos(const ListaAlumnos& l){}

// ListaAlumnos::~ListaAlumnos() {
//   while(longitud() > 0){
//     eliminar(0);
//   } 
// }

// int ListaAlumnos::longitud() const {
//   return len;
// }

// void ListaAlumnos::agAdelante(const Alumno& elem) {
//   Nodo* head = new Nodo;
//   head->alumno = elem;
//   head->sig = prim;
//   prim = head;
//   if (len == 0){
//     fin = head;
//   }
//   len++;
// }

// void ListaAlumnos::agAtras(const Alumno& elem) {
//   Nodo* feet = new Nodo;
//   feet->alumno = elem;
//   feet->sig = NULL;
//   fin->sig = feet;
//   fin = feet;
//   if (len == 0){
//     prim = feet;
//   }  
//   len++;
// }

// const Alumno& ListaAlumnos::iesimo(Nat i) const{
//   if(longitud() - 1 < i){
//     throw "NO SE PUEDE VIEJA";
//   }
//   Nodo* iesimo = prim;
//   for(i ; i>0 ; i--){
//     iesimo = iesimo->sig;
//   }
//   return iesimo->alumno; 
// }

// Alumno& ListaAlumnos::iesimo(Nat i){
//   if(longitud()-1 < i){
//     throw "NO SE PUEDE VIEJA";
//   }
//   Nodo* iesimo = prim;
//   for(i ; i>0 ; i--){
//     iesimo = iesimo->sig;
//   }
//   return iesimo->alumno; 
// }


// void ListaAlumnos::eliminar(Nat i){
//   if(longitud() - 1 < i){
//     throw "NO SE PUEDE VIEJA";
//   }
//   if(longitud() == 1){
//     Nodo* util = prim;
//     prim = NULL;
//     fin = NULL;
//     delete util;
//   }
//   else{
//     Nodo* i_1esimo = prim;
//     unsigned int sop = i; 
//     while(i>1){
//       i_1esimo = i_1esimo->sig;
//       i--;   
//     } 
//     if(longitud()-1 == sop){
//       fin = i_1esimo;
//     }
//     Nodo* util = i_1esimo;
//     if(sop > 0){
//       util = i_1esimo->sig;
//     }  
//     i_1esimo->sig = i_1esimo->sig->sig;
//     delete util;
//   }
//   len--;  
// }
//  ListaAlumnos& operator=(const ListaAlumnos& aCopiar);
//  void mostrar(ostream& o) const;

