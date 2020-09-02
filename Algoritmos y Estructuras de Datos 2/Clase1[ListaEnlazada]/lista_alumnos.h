#ifndef _LISTA_ALUMNOS_H_
#define _LISTA_ALUMNOS_H_

typedef unsigned long Nat;

#include <string>
#include <ostream>

using namespace std;

// Los datos de un alumno
struct Alumno {
  public:
  int LU, edad;

  // Como mostrar un alumno
  friend ostream& operator<<(ostream& os, const Alumno& a) {
     os << "{L.U: " << a.LU << "," << "Edad:" << a.edad << "}";
     return os;
  }

};

class ListaAlumnos {
  public:
  //constructores
  ListaAlumnos();
  ListaAlumnos(const ListaAlumnos& l);

  // destructor de lista
  ~ListaAlumnos();

  // asignacion
  ListaAlumnos& operator=(const ListaAlumnos& aCopiar);

  //observadores
  int longitud() const;
  const Alumno& iesimo(Nat i) const;
  Alumno& iesimo(Nat i);

  //algunas operaciones de lista
  void agAdelante(const Alumno& elem);
  void agAtras(const Alumno& elem);
  void eliminar(Nat i);

  // Muestra la lista en un ostream
  // formato de salida: [a_0, a_1, a_2, ...]
  // donde a_i es el resultado del "mostrar" del alumno i de la lista (ya definido)
  void mostrar(ostream& o) const;

  friend ostream& operator<<(ostream& os, const ListaAlumnos &l) {
    l.mostrar(os);
    return os;
  }

  private:

  struct Nodo {
    Alumno alumno;
    Nodo* sig;
  };

  int len;
  Nodo* prim;
  Nodo* fin;
};

#endif
