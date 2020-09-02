#include "Lista.h"
#include "mini_test.h"

void lista_vacia_mide_cero() {
  Lista<int> l;
  ASSERT_EQ( l.longitud(), 0 );
}

void listas_vacias_son_iguales() {
  Lista<int> l1, l2;
  ASSERT( l1 == l2 );
}

void agregar_un_elemento_incrementa_logitud() {
  Lista<char> l;
  l.agAdelante('a');
  ASSERT_EQ( l.longitud(), 1 );
}

int main() {
  RUN_TEST(lista_vacia_mide_cero);
  RUN_TEST(listas_vacias_son_iguales);
  RUN_TEST(agregar_un_elemento_incrementa_logitud);

  return 0;
}
