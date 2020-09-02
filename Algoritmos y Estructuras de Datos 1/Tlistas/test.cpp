#include "lista.h"
#include <iostream>

using namespace std;

int main(int argn, char* args[]) {
	Lista l1;
	Lista l2;
	int tam;
	int i;
	
	cout << "Ingrese la cantidad de elementos de la lista: ";
	cin >> tam;
	cout << "Ingrese un valor para el primer elemento: ";
	cin >> i;
	
	l1.cabeza = new Nodo(i);
	imprimirLista(l1);
	
	cout << "Ingrese un valor para agregar adelante: ";
	cin >> i;
	
	agregarAdelante(l1, i);
	imprimirLista(l1);
	
	cout << "Ingrese un valor para agregar atras: ";
	cin >> i;
	
	agregarAtras(l1, i);
	imprimirLista(l1);
	
	cout << "Ingrese otro valor para agregar atras: ";
	cin >> i;
	
	agregarAtras(l1, i);
	imprimirLista(l1);
	
	cout << "Se copiara la lista creada" << endl;

	l2 = copiar(l1);
	
	cout << "l1 : ";
	imprimirLista(l1);
	cout << "l2 : ";
	imprimirLista(l2);
	
	cout << "Ingrese un valor para agregar adelante de la lista 2: ";
	cin >> i;
	
	agregarAdelante(l2,i);
	
	cout << "l1 : ";
	imprimirLista(l1);
	cout << "l2 : ";
	imprimirLista(l2);

	cout << "Ingrese un valor para agregar atras de la lista 2: ";
	cin >> i;

	agregarAtras(l2,i);
	
	cout << "l1 : ";
	imprimirLista(l1);
	cout << "l2 : ";
	imprimirLista(l2);

	cout << "Se ordenara la lista 1: " << endl;

	ordenar(l1);
	
	cout << "l1 ordenado: " << endl;
	imprimirLista(l1);
	cout << "l2 : ";
	imprimirLista(l2);
	
    return 0;
}
