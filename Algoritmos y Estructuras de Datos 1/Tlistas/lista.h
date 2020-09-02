#include <iostream>

using namespace std;

class Nodo{
  public:
    int valor;
    Nodo* proximo;
    Nodo(int x){ valor = x;}
};

class Lista{
  public:
    Nodo* cabeza;
};


void imprimirLista(Lista &l){
}

void agregarAdelante(Lista &l, int x){
}

void agregarAtras(Lista &l, int x){
}

void swapN(Nodo* ant, Nodo* act, Nodo* prox){
  Nodo* n = prox->proximo;
  ant->proximo = prox;
  prox->proximo = act;
  act->proximo = n;
}

void ordenar(Lista &l){
  // Pueden usar swapN para swapear la posicion de dos nodos.
 
}

Lista copiar(Lista &l1){
}

