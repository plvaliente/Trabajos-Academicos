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
void test(){
    
    DiccStr<int> d;
    //DiccStr< Lista< TuplaConjRegistros > > ds;
    
    //ds.~DiccStr< Lista< TuplaConjRegistros > >();
    String s = "aaa";
    
     d.Definir(s, 10);
      bool res = d.Definido(s);
      ASSERT_EQ(res, true);
      ASSERT_EQ(d.Obtener(s), 10);
      d.Definir("zaaa", 33);
      ASSERT_EQ(d.MinimaClave(), "aaa");
      ASSERT_EQ(d.MaximaClave(), "zaaa");
      ASSERT_EQ(d.Definido("zaaa"), true);
      
    //Join join("aa");
    //DiccStr<Join> diccJoin;
    //DiccStr<Join> diccJoin2 = diccJoin;
    //diccJoin.Definir("tabla", join);
    // ASSERT_EQ(diccJoin.Definido("tabla"), true);

     
    
   
}



void testPruebaESTR(){
    /*Join join("aa");
    Registro r;
    Modificacion(false, r);
    join._modificaciones.Agregar(Modificacion(false, r));
    join._conjJoin._registros.Agregar(r);*/
   
}

void testMem(){
    
    DiccStr<int> d;
    String s = "aaa";
    d.Definir(s, 10);
    d.Definir("zaaa", 33);
    d.Definir("zaxa", 31);
    d.Definir("zada", 32);
}

void test2() {
    DiccStr< Lista < TuplaConjRegistros > > ds;
    Conj<Registro> cr;
    Registro r;
    r.Definir(campo("campo1"), Dato(2));
    r.Definir(campo("campo2"), Dato(4));
    r.Definir(campo("campo3"), Dato("Torta"));
    cr.AgregarRapido(r);
    Conj<Registro>::Iterador itc = cr.CrearIt();
    
    Lista< TuplaConjRegistros > l;
    TuplaConjRegistros tp;
    l.AgregarAdelante(tp);
    Lista<TuplaConjRegistros>::Iterador itl = l.CrearIt();
    
    TuplaConjRegistros tupF(itc, itl);
    Lista < TuplaConjRegistros > listaF;
    listaF.AgregarAdelante(tupF);
    
    ds.Definir("abcdefghijklmnopqrstuvwxyz", listaF);
    
}

void test3() {
    ContenedorReg rg;
    Registro r;
    r.Definir(campo("campo1"), Dato(2));
    r.Definir(campo("campo2"), Dato(4));
    r.Definir(campo("campo3"), Dato("Torta"));
    rg._registros.AgregarRapido(r);
    Lista< TuplaConjRegistros > l;
    TuplaConjRegistros tp;
    l.AgregarAdelante(tp);
    
    rg._indiceNat.Definir(32, l);
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
    DiccStr<Tabla> tablas;
    tablas.Definir(tbl1.Nombre(), tbl1);
    tablas.Definir(tbl2.Nombre(), tbl2);
    //DiccStr<Tabla> t2p = tablas;
    DiccStr< DiccStr<int> > dtrie;
    DiccStr< DiccStr<int> > dasig = dtrie;
    DiccStr< DiccStr<int> > dcop(dtrie); 
    DiccStr<int> d;
    String s = "aaa";
    d.Definir(s, 10);
    dtrie.Definir("a", d);
    //Tabla t2 = tablas.Obtener(tbl1.Nombre());

}


int main()
{
     RUN_TEST( testPruebaESTR );
    RUN_TEST(test);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(testDiccStrConTablas);
    RUN_TEST(testMem);
  // AGREGAR MAS TESTS...

  return 0;
}