// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "aed2.h"
#include "Modulos.h"
#include "Tabla.h"

using namespace std;
using namespace modulos;
using namespace aed2;

// string remove_spaces(const string& s) {
//   string out(s);
//   out.erase(remove(out.begin(), out.end(), ' '), out.end());
//   out.erase(remove(out.begin(), out.end(), '\n'), out.end());
//   return out;
// }

// template<typename T>
// string to_s(const T& m) {
// 	ostringstream os;
// 	os << m;
// 	return os.str();
// }

void test1() {
  DiccNat<int> uno;
  ASSERT_EQ( uno.Definido(1) , false );
  int i = 2;
  int m = 4;
  int n = 6;
  uno.Definir(2, i);
  uno.Borrar(2);
  ASSERT_EQ(uno.Definido(2), false);
  
  uno.Definir(2,i);
  ASSERT_EQ(uno.Definido(2), true);
  uno.Definir(1, m);
  uno.Borrar(2);
  ASSERT_EQ(uno.Definido(2), false);
  ASSERT_EQ(uno.Definido(1), true);
  uno.Definir(3, n);
  uno.Definir(0, i);
  uno.Borrar(1);
  ASSERT_EQ(uno.Definido(1), false);
  ASSERT_EQ(uno.Definido(3), true);
  ASSERT_EQ(uno.Definido(0), true);
  DiccNat<int> dos(uno);
  ASSERT_EQ(dos.Definido(1), false);
  ASSERT_EQ(dos.Definido(3), true);
  ASSERT_EQ(dos.Definido(0), true);
  uno.Borrar(0);
  ASSERT_EQ(dos.Definido(0), true);
  ASSERT_EQ(uno.Definido(0), false);
  ASSERT_EQ(dos.Obtener(0) == i, true);
  ASSERT_EQ(dos.MinimaClave(), 0);
  ASSERT_EQ(dos.MaximaClave(), 3);
  
  DiccNat<int> tres = dos;
  
}

void test2() {
  DiccNat< Conj<int> > dic;
  Conj<int> c1, c2, c3, c4, c5, c6, c7, c8;
  for(int i=1; i<11; i++){
    c1.AgregarRapido(i);
    c2.AgregarRapido(i+1);
    c3.AgregarRapido(i+2);
    c4.AgregarRapido(i+3);
    c5.AgregarRapido(i+4);
    c6.AgregarRapido(i+5);
    c7.AgregarRapido(i+6);
    c8.AgregarRapido(i+7);
  }
  dic.Definir(4,c4);
  dic.Definir(6,c6);
  dic.Definir(2,c2);
  dic.Definir(1,c1);
  dic.Definir(3,c3);
  dic.Definir(5,c5);
  dic.Definir(7,c7);
  dic.Definir(8,c8);
  ASSERT_EQ(dic.Definido(1), true);
  ASSERT_EQ(dic.Obtener(1) == c1, true);
  dic.Borrar(6);
  ASSERT_EQ(dic.Definido(6), false);
  ASSERT_EQ(dic.Definido(8), true);
}

void test3() {
  TuplaConjRegistros TCR1, TCR2;
  Registro reg1, reg2;                       
  campo cmp1 = "aa";
  campo cmp2 = "bb";
  Dato dat1 = Dato(0);
  reg1.Definir(cmp1, dat1);
  reg2.Definir(cmp2, dat1);  
  Conj<Registro> CR1, CR2;
  Conj<Registro>::Iterador it1 = CR1.AgregarRapido(reg1);
  Conj<Registro>::Iterador it2 = CR2.AgregarRapido(reg2);
  TCR1._reg = it1;
  TCR2._reg = it2;
  
  Lista<TuplaConjRegistros> CTCR;
  CTCR.AgregarAdelante(TCR1);
  CTCR.AgregarAdelante(TCR2);
  
  ContenedorReg ConReg;
  ConReg._indiceNat.Definir(4,CTCR);
  ConReg._indiceNat.Definir(6,CTCR);
  ConReg._indiceNat.Definir(2,CTCR);
  ConReg._indiceNat.Definir(1,CTCR);
  ConReg._indiceNat.Definir(3,CTCR);
  ConReg._indiceNat.Definir(5,CTCR);
  ConReg._indiceNat.Definir(7,CTCR);
  ConReg._indiceNat.Definir(8,CTCR);
  ASSERT_EQ(ConReg._indiceNat.Definido(1), true);
  ASSERT_EQ(ConReg._indiceNat.Obtener(1) == CTCR, true);
  ConReg._indiceNat.Borrar(6);
  ASSERT_EQ(ConReg._indiceNat.Definido(6), false);
  ASSERT_EQ(ConReg._indiceNat.Definido(8), true);                    //Test de DiccNat que se usa en ContenedorReg
}
  
Tabla crearTabla() {
  Conj<campo> cnj;
  campo clave1 = "cmp1";
  cnj.AgregarRapido(clave1);
  Registro reg1;
  Dato dat1 = Dato(1);
  reg1.Definir(clave1, dat1);
  reg1.Definir(campo("cmp2"), dat1);
  Tabla tbl = Tabla("tabla1", cnj, reg1);         // test constructor
  return tbl;
}

Tabla crearTabla2() {
  Conj<campo> cnj;
  campo clave1 = "cmp1";
  cnj.AgregarRapido(clave1);
  Registro reg1;
  Dato dat1 = Dato(1);
  reg1.Definir(clave1, dat1);
  reg1.Definir(campo("cmp2"), dat1);
  Tabla tbl = Tabla("tabla2", cnj, reg1);         // test constructor
  return tbl;
}

void testDiccStrConTablas() {
    Tabla tbl1 = crearTabla();
    Tabla tbl2 = crearTabla2();
    DiccNat<Tabla> tablas;
    tablas.Definir(1, tbl1);
    tablas.Definir(2, tbl2);
    Tabla t2 = tablas.Obtener(1);

}
  
  
int main()
{
  RUN_TEST( test1 );
  RUN_TEST( test2 );
  RUN_TEST( test3 );
  RUN_TEST( testDiccStrConTablas );
  return 0;
}
