#include <iostream>

#include "ArregloDimensionable.h"
#include "Par.h"
#include "Mejor.h"

using namespace std;

int main(){

    Par<int, float> p1(1, 2.0);
    Par<int, float> p2(2, 2.0);
    Par<int, float> p3(3, 2.0);
    ArregloDimensionable< Par<int, float> > arregloDePares;
    arregloDePares.insertarAtras(p1);
    arregloDePares.insertarAtras(p2);
    arregloDePares.insertarAtras(p3);
    
    cout << "mejor par (criterio interno): " << mejor(arregloDePares) << endl;
    
    Par<int, float>::Criterio comp;
    cout << "mejor par (con comparador): " << mejor(arregloDePares, comp) << endl;
    
    ArregloDimensionable<int> arregloDeInts;
    arregloDeInts.insertarAtras(1);
    arregloDeInts.insertarAtras(3);
    arregloDeInts.insertarAtras(2);

	cout << "mejor int (criterio interno): " << mejor(arregloDeInts) << endl << endl;
	
	return 0;
}
