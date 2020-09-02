#include "lista_alumnos.h"
#include "mini_test.h"

// para compilar:$ g++ -g test.cpp lista_alumnos.cpp -o lista_alumnos
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./lista_alumnos

void test_lista_nueva_es_vacia() {
  ListaAlumnos l;
  ASSERT_EQ(l.longitud(), 0);
}

void test_a_la_lista_vacia_se_le_agrega_alumno() {
  ListaAlumnos l;

  Alumno a;
  a.LU = 78403;
  a.edad = 29;
  l.agAdelante(a);

  ASSERT_EQ(l.longitud(), 1);
}

void test_agAdelante() {
	ASSERT(false);
}

void test_agAtras() {
	ASSERT(false);
}

void test_longitud() {
	ASSERT(false);
}

void test_iesimo() {
	ASSERT(false);
}

int main() {
  RUN_TEST(test_lista_nueva_es_vacia);
  RUN_TEST(test_a_la_lista_vacia_se_le_agrega_alumno);

  // completar y agregar mas!
  RUN_TEST(test_agAdelante);
  RUN_TEST(test_agAtras);
  RUN_TEST(test_longitud);
  RUN_TEST(test_iesimo);

  return 0;
}
