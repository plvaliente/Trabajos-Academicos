/*
 * Solucion de la ejercitacion del uso de iteradores.
 */

#include "Lista.h"
#include "mini_test.h" 

#include <iostream>				// std::std::cout, std::endl

using namespace aed2;

/**
 * Cantidad de elementos de l
 */
template<typename T>
int cant( const Lista<T>& l ) {
  typename Lista<T>::const_Iterador it = l.CrearIt();
  int result = 0;
  while(it.HaySiguiente()){
  	++result;
  	it.Avanzar();
  }
  return result;
}

/**
 * String con el contenido de l
 */
template<typename T>
void mostrar( const Lista<T>& l ) {
 typename Lista<T>::const_Iterador it = l.CrearIt();
  std::cout << "[ ";
  while(it.HaySiguiente()){
  	std::cout << it.Siguiente();
  	it.Avanzar();
  	it.HaySiguiente() ? std::cout << ", " : std::cout << " ]" << std::endl;
  }
}
/**
 * Modifica una lista, duplicando todos los elementos 
 * de la lista original, y devuelve esa misma.
 */
template<typename T>
Lista<T>& dobles( Lista<T>& l ) {
	typename Lista<T>::Iterador it = l.CrearIt();
 	while(it.HaySiguiente()){
  		it.AgregarComoAnterior(it.Siguiente());
  		it.Avanzar();
  	}
}

/**
 * Devuelve una lista que tiene unicamente los elementos primos 
 * contenidos en la lista original.
 * Un numero entero se considera primo sii unicamente tiene 
 * dos divisores enteros, a si mismo y al numero 1.
 */
template<typename T>
Lista<T> primos( const Lista<T>& l ) {
	Lista<T> lprima;
 	T num;
 	bool isPrime;
 	typename Lista<T>::const_Iterador it = l.CrearIt();
 	typename Lista<T>::Iterador itprimo = lprima.CrearIt();
 	while(it.HaySiguiente()){
 		isPrime = true;
		num = it.Siguiente() - 1;
		if(it.Siguiente() <= 1){
			for(num; num > 1; --num){
				if(it.Siguiente() % num == 0) isPrime = false;
			}
		} else{
			isPrime = false;
		}
		if(isPrime){
			itprimo.AgregarComoSiguiente(it.Siguiente());
			itprimo.Avanzar();
			it.Avanzar();
		} else{
			it.Avanzar();
		}	
	}
	return lprima;
}
void cant_ok() {
	Lista<int> l;
	for(int i = 50; i >= 0; --i) l.AgregarAdelante(i);
	ASSERT( cant(l) == l.Longitud() );
}

int main(int argc, char **argv) {
	RUN_TEST(cant_ok);
  return 0;
}

