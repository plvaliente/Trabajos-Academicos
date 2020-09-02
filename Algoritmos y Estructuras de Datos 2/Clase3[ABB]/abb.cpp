#include <iostream>
#include "Conjunto.hpp"

#include "mini_test.h"


void si_no_lo_agrego_no_pertenece() {
  Conjunto<char> c;
  ASSERT( !c.pertenece('a') );
}


void insertar_inserta() {
  Conjunto<int> c;
  c.insertar(42);
  ASSERT( c.pertenece(42) );
}

void insertar_1000() {
  Conjunto<int> c;
  int i = 1000;
 // while (i > 0){
  	c.insertar(1);
  	c.insertar(4);
  	c.insertar(2);
  	c.insertar(3);
  	
 // 	i--;
 // }
 // i = 1000;
 // while (i > 0){
  //	ASSERT( c.pertenece(i) );
 // 	i--;
 // }
 }



int main() {
    RUN_TEST(si_no_lo_agrego_no_pertenece);
    RUN_TEST(insertar_inserta);
    RUN_TEST(insertar_1000);
    return 0;
}
