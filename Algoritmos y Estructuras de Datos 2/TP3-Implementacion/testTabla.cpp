// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "aed2.h"
#include "Tabla.h"

using namespace modulos;

Registro crearRegistro(Dato clave, Dato n) {
  campo cmp1 = "cmp1";
  Registro reg1;
  reg1.Definir(cmp1, clave);
  reg1.Definir(campo("cmp2"), n);
  Dato dat2 = Dato("ss");
  reg1.Definir(campo("otro"), dat2);
  
  return reg1;
}



Tabla crearTabla() {
  Conj<campo> cnj;
  campo clave1 = "cmp1";
  cnj.AgregarRapido(clave1);
  Registro reg1;
  Dato dat1 = Dato(1);
  Dato dat2 = Dato("ss");
  reg1.Definir(clave1, dat1);
  reg1.Definir(campo("otro"), dat2);
  reg1.Definir(campo("cmp2"), dat1);
  Tabla tbl = Tabla("tabla1", cnj, reg1);         // test constructor
  return tbl;
}
void test() {
  Tabla tbl = crearTabla();
  Registro reg = crearRegistro(Dato(2), Dato(2));
  tbl.AgregarRegistro(reg);
  Registro regB;
  regB.Definir(campo("cmp1"),Dato(2));
  tbl.BorrarRegistro(regB);                        //Test borrar registro de tabla sin indices.
  tbl.Registros();
  ASSERT_EQ(tbl.Claves().Cardinal() != 0, true);
}

void testIndexar() {
  Tabla tbl = crearTabla();
  tbl.AgregarRegistro(crearRegistro(Dato(2), Dato(2)));
  tbl.AgregarRegistro(crearRegistro(Dato(3), Dato(4)));
  tbl.AgregarRegistro(crearRegistro(Dato(4), Dato(3)));
  tbl.AgregarRegistro(crearRegistro(Dato(5), Dato(2)));
  //ASSERT_EQ(tbl.Maximo("cmp1").ValorN(), 3);
  tbl.Indexar("cmp2");
  tbl.Indexar("otro");
  ASSERT_EQ(tbl.Maximo("cmp2").ValorN(), 4);
  ASSERT_EQ(tbl.Minimo("cmp2").ValorN(), 2);
  tbl.Registros();
}

void testTablaConMuchosCambosConDatosDistintos() {
  
  //Creo Tabla
  Conj<campo> cnj;
  campo clave1 = "cmp1";
  cnj.AgregarRapido(campo("clave1"));
  cnj.AgregarRapido(campo("clave2"));
  cnj.AgregarRapido(campo("clave3"));
  cnj.AgregarRapido(campo("clave4"));
  Registro reg1;
  Dato dat1 = Dato(1);
  reg1.Definir(campo("clave1"), Dato("S"));
  reg1.Definir(campo("clave2"), Dato("S"));
  reg1.Definir(campo("clave3"), Dato("S"));
  reg1.Definir(campo("clave4"), Dato(2));
  reg1.Definir(campo("cmp1"), Dato(2));
  reg1.Definir(campo("cmp2"), Dato("S"));
  reg1.Definir(campo("cmp3"), Dato("S"));
  reg1.Definir(campo("cmp4"), Dato(2));
  Tabla tbl = Tabla("tabla1", cnj, reg1);         // test constructor
  
  //Agrego un Registro
  Registro reg2;
  reg2.Definir(campo("clave1"), Dato("Ivan"));
  reg2.Definir(campo("clave2"), Dato("Vercinsky"));
  reg2.Definir(campo("clave3"), Dato("1914"));
  reg2.Definir(campo("clave4"), Dato(141));
  reg2.Definir(campo("cmp1"), Dato(26));
  reg2.Definir(campo("cmp2"), Dato("Casa"));
  reg2.Definir(campo("cmp3"), Dato("Estudianta"));
  reg2.Definir(campo("cmp4"), Dato(500));
  
  //Agrego un Registro
  Registro reg3;
  reg3.Definir(campo("clave1"), Dato("Agustin"));
  reg3.Definir(campo("clave2"), Dato("Delma"));
  reg3.Definir(campo("clave3"), Dato("1915"));
  reg3.Definir(campo("clave4"), Dato(142));
  reg3.Definir(campo("cmp1"), Dato(26));
  reg3.Definir(campo("cmp2"), Dato("Casa"));
  reg3.Definir(campo("cmp3"), Dato("Estudiante"));
  reg3.Definir(campo("cmp4"), Dato(500));
  
  //Agrego un Registro
  Registro reg4;
  reg4.Definir(campo("clave1"), Dato("Ciro"));
  reg4.Definir(campo("clave2"), Dato("Zar"));
  reg4.Definir(campo("clave3"), Dato("1916"));
  reg4.Definir(campo("clave4"), Dato(143));
  reg4.Definir(campo("cmp1"), Dato(26));
  reg4.Definir(campo("cmp2"), Dato("Casa"));
  reg4.Definir(campo("cmp3"), Dato("Trola"));
  reg4.Definir(campo("cmp4"), Dato(500));
  
  tbl.AgregarRegistro(reg2);
  tbl.AgregarRegistro(reg3);
  tbl.AgregarRegistro(reg4);
  
  tbl.Indexar("clave4");
  tbl.Indexar("cmp3");
  
  ASSERT_EQ(tbl.Maximo("clave4").ValorN(), 143);
  ASSERT_EQ(tbl.Minimo("clave4").ValorN(), 141);
  
  ASSERT_EQ(tbl.Maximo("cmp3").ValorS(), "Trola");
  ASSERT_EQ(tbl.Minimo("cmp3").ValorS(), "Estudianta");
  
  
  
}

void testCombinarRegistros(){
  Tabla t = crearTabla();
  
  Registro reg1;
  Dato dat1 = Dato(1);
  reg1.Definir(campo("clave1"), Dato("S"));
  reg1.Definir(campo("clave2"), Dato("S"));
  reg1.Definir(campo("clave3"), Dato("S"));
  reg1.Definir(campo("clave4"), Dato(2));
  reg1.Definir(campo("cmp1"), Dato(2));
  reg1.Definir(campo("cmp2"), Dato("S"));
  reg1.Definir(campo("cmp3"), Dato("S"));
  reg1.Definir(campo("cmp4"), Dato(2));
  
  
  Registro reg2;
  reg2.Definir(campo("clave1"), Dato("Ivan"));
  reg2.Definir(campo("clave2"), Dato("Vercinsky"));
  reg2.Definir(campo("clave3"), Dato("1914"));
  reg2.Definir(campo("clave4"), Dato(141));
  reg2.Definir(campo("cmp1"), Dato(26));
  reg2.Definir(campo("cmp2"), Dato("Casa"));
  reg2.Definir(campo("cmp3"), Dato("Estudianta"));
  reg2.Definir(campo("cmp4"), Dato(500));
  
  Registro reg3;
  reg3.Definir(campo("clave1"), Dato("Ivan"));
  reg3.Definir(campo("clave2"), Dato("Vercinsky"));
  reg3.Definir(campo("clave3"), Dato("1914"));
  reg3.Definir(campo("clave4"), Dato(141));
  reg3.Definir(campo("cmp1"), Dato(26));
  reg3.Definir(campo("cmp2"), Dato("Casa"));
  reg3.Definir(campo("cmp3"), Dato("Estudianta"));
  reg3.Definir(campo("cmp4"), Dato(500));
  
  Conj<Registro> c1;
  c1.AgregarRapido(reg1);
  c1.AgregarRapido(reg2);

  Conj<Registro> c2;
  c2.AgregarRapido(reg3);
  
  Conj<Registro> regComb = t.CombinarRegistros("clave1", c1, c2);
  Conj<Registro>::Iterador itReg = regComb.CrearIt();
  // Registro r = itReg.Siguiente();
  ASSERT_EQ(regComb.Cardinal(), 1);
  // ASSERT_EQ(regComb == c1, false);
  // ASSERT_EQ(r.Campos().Cardinal(), 8);
  
  

  
  
}
int main()
{
  RUN_TEST( test );
  RUN_TEST( testIndexar );
   RUN_TEST( testTablaConMuchosCambosConDatosDistintos );
  RUN_TEST(testCombinarRegistros);
  return 0;
}