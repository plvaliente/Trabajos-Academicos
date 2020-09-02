#include "lista_alumnos.h"

ListaAlumnos::ListaAlumnos()
  : len(0), prim(NULL), fin(NULL) {
}

//ListaAlumnos::ListaAlumnos(const ListaAlumnos& l){}

ListaAlumnos::~ListaAlumnos() {
  while(longitud() > 0){
    eliminar(0);
  } 
}

int ListaAlumnos::longitud() const {
  return len;
}

void ListaAlumnos::agAdelante(const Alumno& elem) {
  Nodo* head = new Nodo;
  head->alumno = elem;
  head->sig = prim;
  prim = head;
  if (len == 0){
    fin = head;
  }
  len++;
}

void ListaAlumnos::agAtras(const Alumno& elem) {
  Nodo* feet = new Nodo;
  feet->alumno = elem;
  feet->sig = NULL;
  fin->sig = feet;
  fin = feet;
  if (len == 0){
    prim = feet;
  }  
  len++;
}

const Alumno& ListaAlumnos::iesimo(Nat i) const{
  if(longitud() - 1 < i){
    throw "NO SE PUEDE VIEJA";
  }
  Nodo* iesimo = prim;
  for(i ; i>0 ; i--){
    iesimo = iesimo->sig;
  }
  return iesimo->alumno; 
}

Alumno& ListaAlumnos::iesimo(Nat i){
  if(longitud()-1 < i){
    throw "NO SE PUEDE VIEJA";
  }
  Nodo* iesimo = prim;
  for(i ; i>0 ; i--){
    iesimo = iesimo->sig;
  }
  return iesimo->alumno; 
}


void ListaAlumnos::eliminar(Nat i){
  if(longitud() - 1 < i){
    throw "NO SE PUEDE VIEJA";
  }
  if(longitud() == 1){
    Nodo* util = prim;
    prim = NULL;
    fin = NULL;
    delete util;
  }
  else{
    Nodo* i_1esimo = prim;
    unsigned int sop = i; 
    while(i>1){
      i_1esimo = i_1esimo->sig;
      i--;   
    } 
    if(longitud()-1 == sop){
      fin = i_1esimo;
    }
    Nodo* util = i_1esimo;
    if(sop > 0){
      util = i_1esimo->sig;
    }  
    i_1esimo->sig = i_1esimo->sig->sig;
    delete util;
  }
  len--;  
}
  // ListaAlumnos& operator=(const ListaAlumnos& aCopiar);
  // void mostrar(ostream& o) const;
// Completar
