// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "aed2.h"
#include "BaseDeDatos.h"

using namespace modulos;
Registro crearRegistro(Dato clave, Dato n) {
  campo cmp1 = "cmp1";
  Registro reg1;
  reg1.Definir(cmp1, clave);
  reg1.Definir(campo("cmp2"), n);
  return reg1;
}

Registro crearRegistro(Dato clave, Dato n, Dato s) {
  campo cmp1 = "cmp1";
  Registro reg1;
  reg1.Definir(cmp1, clave);
  reg1.Definir(campo("cmp2"), n);
  reg1.Definir(campo("cmp3"), s);
  return reg1;
}

Tabla crearTabla() {
  Conj<campo> cnj;
  campo clave1 = "cmp1";
  cnj.AgregarRapido(clave1);
  assert(cnj.Cardinal() != 0);
  Registro reg1;
  Dato dat1 = Dato(1);
  reg1.Definir(clave1, dat1);
  reg1.Definir(campo("cmp2"), dat1);
  Tabla tbl = Tabla("tabla1", cnj, reg1);         // test constructor
  assert(tbl.Claves().Cardinal() != 0);
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

void testRegistrosTabla() {
  BaseDeDatos b;
  Tabla tbl1 = crearTabla();
  b.AgregarTabla(tbl1);
  ASSERT_EQ(b.Registros(tbl1.Nombre()).Cardinal(),0);
  //tbl1.Indexar("cmp2");
  b.InsertarEntrada(crearRegistro(Dato(2), Dato(2)), tbl1.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(3), Dato(4)), tbl1.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(4), Dato(3)), tbl1.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(5), Dato(2)), tbl1.Nombre());
  //tbl1.AgregarRegistro(crearRegistro(Dato(5), Dato(2)));
  //ASSERT_EQ(tbl1.Registros().Cardinal(), 4);
  ASSERT_EQ(b.Registros(tbl1.Nombre()).Cardinal(),4);
}

void testfuncbasicas() {
  BaseDeDatos b;
  Tabla tbl = crearTabla();
  Registro reg = crearRegistro(Dato(2), Dato(2));
  // tbl.AgregarRegistro(reg);
  Registro regB;
  campo clave1 = "cmp1";
  regB.Definir(clave1 , Dato(2));
  assert(regB.Definido("cmp1"));
  //tbl.BorrarRegistro(regB);                        //Test borrar registro de tabla sin indices.
  b.AgregarTabla(tbl);
  nombreTabla s = tbl.Nombre();
  ASSERT_EQ(b.DameTabla(s).Nombre(), s );
  b.InsertarEntrada(reg, s);
  ASSERT_EQ( b.Registros(s).Cardinal() == 1 , true );
  Conj<campo> cnj;
  cnj.AgregarRapido("cmp1");
  ASSERT_EQ(cnj == regB.Campos(), true);
  ASSERT_EQ(cnj == b.DameTabla(s).Claves(), true);
  assert(b.DameTabla(s).Claves().Cardinal() != 0);
 //b.Borrar(regB, s); 
 b.DameTabla(s).Indexar("cmp1");
 ASSERT(b.DameTabla(s).Indices().Cardinal() != 0);
  //falta hacer ASSERT_EQ probando que las funciones andan bien 
  Conj<Registro> regBusc = b.Buscar(reg, s);
  ASSERT_EQ(regBusc.Cardinal(), 1); //test buscar
  
  itTablas itTbl = b.Tablas();
  ASSERT_EQ(itTbl.HaySiguiente(), true); //test Tablas
  
  Conj<Registro> creg = b.Registros(tbl.Nombre());
  ASSERT_EQ(creg.Cardinal() != 0, true); //test registros
  
  int n = b.CantidadDeAccesos(tbl.Nombre());
  ASSERT_EQ(n!=0, true); //test cantidad de accesos
  b.TablaMaxima();
  
}


void testJoins() {
  BaseDeDatos b;
  
  Tabla tbl = crearTabla();

  tbl.Indexar("cmp1");
  b.AgregarTabla(tbl);
  b.InsertarEntrada(crearRegistro(Dato(2), Dato(2)), tbl.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(3), Dato(4)), tbl.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(4), Dato(3)), tbl.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(5), Dato(2)), tbl.Nombre());


  Tabla tbl2 = crearTabla2();
  b.AgregarTabla(tbl2);
  b.InsertarEntrada(crearRegistro(Dato(2), Dato(2)), tbl2.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(3), Dato(4)), tbl2.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(4), Dato(3)), tbl2.Nombre());
  b.InsertarEntrada(crearRegistro(Dato(5), Dato(2)), tbl2.Nombre());
  tbl2.Indexar("cmp2");

  //test generar vista join
  b.GenerarVistaJoin(tbl.Nombre(), tbl2.Nombre(), campo("cmp1"));
  ASSERT_EQ(b.HayJoin(tbl.Nombre(), tbl2.Nombre()), true);
  ASSERT_EQ(b.HayJoin(tbl2.Nombre(), tbl.Nombre()), false);
  ASSERT_EQ(b.CampoJoin(tbl.Nombre(), tbl2.Nombre()), "cmp1");

  //creo tabla3 y genero join
  
  Conj<campo> claves;
  campo clave1 = "cmp1";
  claves.AgregarRapido(clave1);
  Registro reg;
  Dato dat1 = Dato(1);
  reg.Definir(clave1, Dato(0));
  reg.Definir(campo("cmp2"), Dato("S"));
  Tabla tbl3 = Tabla("tabla3", claves, reg);
  b.AgregarTabla(tbl3);
  

  Conj<Registro>::const_Iterador itGVJ = b.GenerarVistaJoin(tbl.Nombre(), tbl3.Nombre(), "cmp1");
  Conj<Registro>::const_Iterador itGVJ2 = b.GenerarVistaJoin(tbl3.Nombre(), tbl.Nombre(), "cmp1");
  ASSERT(!(itGVJ.HaySiguiente()));
  
  Registro r1 = crearRegistro(Dato(2), Dato("dos"));
  b.InsertarEntrada(r1, tbl3.Nombre());
  Registro r2 = crearRegistro(Dato(4), Dato("cuatro"));
  b.InsertarEntrada(r2, tbl3.Nombre());
  tbl3.Indexar("cmp2");
  
  ASSERT_EQ(itGVJ.HaySiguiente(), false);
  
  //test vista join
  Conj<Registro>::const_Iterador vistaJ = b.VistaJoin(tbl.Nombre(), tbl3.Nombre() );
  Conj<Registro>::const_Iterador vistaJ2 = b.VistaJoin(tbl3.Nombre(), tbl.Nombre() );
  
  // Registro regComb1 = crearRegistro(Dato(2), Dato(2));        <-- No debería quedar asi?
  Registro regComb1 = crearRegistro(Dato(4), Dato("cuatro"));
  ASSERT(vistaJ2.HaySiguiente());
  ASSERT(vistaJ2.Siguiente() == regComb1);

  Registro regComb2 = crearRegistro(Dato(4), Dato(3));
  ASSERT(vistaJ.HaySiguiente());
  ASSERT(vistaJ.Siguiente() == regComb2);
  // ASSERT_EQ(vistaJ.HaySiguiente(), true)
  
  //test borrar join
  //b.BorrarJoin(tbl.Nombre(), tbl2.Nombre());
  //ASSERT_EQ(b.HayJoin(tbl.Nombre(), tbl2.Nombre()), false);
  
  // test vistaJoin despues de borrado.
  Registro crit;
  crit.Definir(campo("cmp1"), Dato(2));

  b.Borrar(crit, tbl3.Nombre());
  Conj<Registro> b1 = b.Buscar(crit, tbl3.Nombre());
  ASSERT(b1.EsVacio())

  Registro crit2;
  crit2.Definir(campo("cmp1"), Dato(4));
  Conj<Registro> bb2 = b.Buscar(crit2, tbl3.Nombre());
  ASSERT(!bb2.EsVacio())


  vistaJ = b.VistaJoin(tbl.Nombre(), tbl3.Nombre());
  // ASSERT(!vistaJ.HaySiguiente());
  

  //b.Borrar(crit, tbl.Nombre());
  
  b1 = b.Buscar(crit, tbl.Nombre());
  std::cout << b1 << std::endl;
  Conj<Registro> b2;
  Registro regB = crearRegistro(Dato(2), Dato(2));
  b2.AgregarRapido(regB);
  ASSERT(b1 == b2);


}
void testP(){
  BaseDeDatos b;
  Conj<campo> cnj;
  campo dni = "dni";
  campo nombre = "nombre";
  campo apellido = "apellido";
  cnj.AgregarRapido(dni);
  Registro columna;
  Dato nt = Dato(1);
  Dato str1 = Dato("juan");
  Dato str2 = Dato("perez");
  columna.Definir(dni, nt);
  columna.Definir(nombre, str1);
  columna.Definir(apellido, str2);
  Tabla tbl = Tabla("personas", cnj, columna);  
  b.AgregarTabla(tbl);
  b.InsertarEntrada(columna, "personas");
}


int main()
{
  RUN_TEST(testRegistrosTabla);
  RUN_TEST( testfuncbasicas );
  RUN_TEST(testJoins);
  RUN_TEST(testP);
  return 0;
}