// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "PlanificadorRR.h"

using namespace std;

string remove_spaces(const string& s) {
  string out(s);
  out.erase(remove(out.begin(), out.end(), ' '), out.end());
  out.erase(remove(out.begin(), out.end(), '\n'), out.end());
  return out;
}

template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
}

/**
 * Crea un planificador sin procesos.
 */

void planificadorVacio()
{
  PlanificadorRR<int> planificador;
  ASSERT_EQ(planificador.hayProcesos(), false);
  ASSERT_EQ(planificador.hayProcesosActivos(), false);
  ASSERT_EQ(to_s(planificador), "[]");
}
void planificadorUnario()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(1);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[1*]");
}

void planificadorDec()
{
  PlanificadorRR<int> planificador;
  PlanificadorRR<int> vacio;
  PlanificadorRR<int> uno;
  uno.agregarProceso(1);
  int i = 0;
  while(i < 10){
    planificador.agregarProceso(i);
    i++;
  }

  ASSERT_EQ(planificador.estaActivo(4), true);

  planificador.pausarProceso(4);
  planificador.pausarProceso(7);
  planificador.pausarProceso(5);
  planificador.pausarProceso(1);
  planificador.pausarProceso(0);

  ASSERT_EQ(planificador.esPlanificado(2), true);
  ASSERT_EQ(planificador.estaActivo(4), false);

  planificador.eliminarProceso(2);
  planificador.eliminarProceso(6);

  ASSERT_EQ(planificador.esPlanificado(2), false);

  planificador.ejecutarSiguienteProceso();
  PlanificadorRR<int> copia(uno);
  PlanificadorRR<int> copia1(planificador);
  copia1.detener();
  ASSERT_EQ(copia1.detenido(), true);
  copia1.reanudar();
  ASSERT_EQ(copia1.detenido(), false);
  ASSERT_EQ(planificador.procesoEjecutado(), copia1.procesoEjecutado());
  
  
  ASSERT_EQ(planificador.cantidadDeProcesos(), 8);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(), 3);
  assert(uno == copia);
  assert(planificador == copia1);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(planificador.procesoEjecutado(), 8);
  ASSERT_EQ(to_s(planificador), "[8*, 9, 0 (i), 1 (i), 3, 4 (i), 5 (i), 7 (i)]");
  ASSERT_EQ(to_s(copia1), "[8*, 9, 0 (i), 1 (i), 3, 4 (i), 5 (i), 7 (i)]");
}

void test_copia() {
    
    
    //Test de generadores
    PlanificadorRR<int> p1; //planificador vacio

    for(int i = 0; i < 100; ++i) {
        p1.agregarProceso(i); //agregar 100 procesos
    }

   
    PlanificadorRR<int> p2(p1); //prueba constructor por copia y ==
    
    assert(p1 == p2);
  assert(p2.hayProcesos() == true);
    assert(p2.hayProcesosActivos() == true);
  assert(p1.procesoEjecutado() == p2.procesoEjecutado());
  
  
  p1.pausarProceso(5); //pausar y reanudar proceso afectan ==
  assert(!(p1 == p2));
  ASSERT_EQ(p1.estaActivo(5), false);
  ASSERT_EQ(p1.cantidadDeProcesos(),p2.cantidadDeProcesos()); //son distintos pero tienen la misma cantidad de procesos
  assert(p1.cantidadDeProcesosActivos() != p2.cantidadDeProcesosActivos());
  p1.reanudarProceso(5);
  assert(p1 == p2); //vuelven a ser iguales
  
  p2.detener(); //detener y reanudar afectan ==
  assert(!(p1 == p2));
  ASSERT_EQ(p2.detenido(), true);
  ASSERT_EQ(p1.cantidadDeProcesos(),p2.cantidadDeProcesos()); //son distintos pero tienen la misma cantidad de procesos
  p2.reanudar();
  assert(p1 == p2); //vuelven a ser iguales 
  
  p1.ejecutarSiguienteProceso(); //ejecutarSiguienteProceso afecta ==
  assert(!(p1 == p2));
  assert(p1.procesoEjecutado() != p2.procesoEjecutado());
  ASSERT_EQ(p1.cantidadDeProcesos(),p2.cantidadDeProcesos()); //son distintos pero tienen la misma cantidad de procesos
  p2.ejecutarSiguienteProceso();
  assert(p1 == p2); //vuelven a ser iguales
  
  
  p2.eliminarProceso(10); //eliminar y agregar mismo elemento no queda igual que antes
  ASSERT_EQ(p2.esPlanificado(10), false);
  ASSERT_EQ(p1.esPlanificado(10), true);
  assert(p1.cantidadDeProcesos() != p2.cantidadDeProcesos());
  ASSERT_EQ(p1.procesoEjecutado() , p2.procesoEjecutado());
  p2.agregarProceso(10);
  ASSERT_EQ(p2.esPlanificado(10), true);
  ASSERT_EQ(p1.esPlanificado(10), true);
  ASSERT_EQ(p1.cantidadDeProcesos() ,p2.cantidadDeProcesos());
  assert(!(p1 == p2)); 
  
}

void test_bordes() {
//probar bordes, eliminar y que quede vacio, recorrer el final de lista circular etc
  PlanificadorRR<int> p;
  p.agregarProceso(1); //agregar un elemento a vacio cambia todo bien
  ASSERT_EQ(p.procesoEjecutado(), 1);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 1);
  ASSERT_EQ(p.esPlanificado(1), true);  
  ASSERT_EQ(p.hayProcesos(), true);
  ASSERT_EQ(p.hayProcesosActivos(), true);
  ASSERT_EQ(p.cantidadDeProcesos(), 1);
  ASSERT_EQ(p.detenido(), false);
  ASSERT_EQ(to_s(p), "[1*]");
  
  p.ejecutarSiguienteProceso(); //si ejecuto el siguiente de pl con 1 elemento queda igual
  ASSERT_EQ(p.procesoEjecutado(), 1);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 1);
  ASSERT_EQ(p.esPlanificado(1), true);  
  ASSERT_EQ(p.hayProcesos(), true);
  ASSERT_EQ(p.hayProcesosActivos(), true);
  ASSERT_EQ(p.cantidadDeProcesos(), 1);
  ASSERT_EQ(p.detenido(), false);
  ASSERT_EQ(to_s(p), "[1*]"); 
  
  p.pausarProceso(1); 
  ASSERT_EQ(p.hayProcesosActivos(), false);
  
  p.reanudarProceso(1);
  ASSERT_EQ(p.hayProcesosActivos(), true);
  
  p.eliminarProceso(1); //queda vacia y vuelve todo como antes
  ASSERT_EQ(p.hayProcesos(), false);
  ASSERT_EQ(p.hayProcesosActivos(), false);
  ASSERT_EQ(p.cantidadDeProcesos(), 0);
  ASSERT_EQ(p.detenido(), false);
  ASSERT_EQ(to_s(p), "[]"); 
    
}
  
void test_otrasop(){
  
  //las operaciones andan bien
  
  //ejecutarSiguienteProceso anda
  PlanificadorRR<int> p;
  p.agregarProceso(1);
  p.ejecutarSiguienteProceso();
  p.agregarProceso(2);

  ASSERT_EQ(p.procesoEjecutado(), 1);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.pausarProceso(1);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.reanudarProceso(1);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 1); 
  ASSERT_EQ(to_s(p), "[1*, 2]");
  p.agregarProceso(3);
  ASSERT_EQ(to_s(p), "[1*, 2, 3]");
  p.pausarProceso(2);
  ASSERT_EQ(to_s(p), "[1*, 2 (i), 3]");
  
  PlanificadorRR<PlanificadorRR<int> > pp;
  pp.agregarProceso(p);
  ASSERT_EQ(to_s(pp), "[[1*, 2 (i), 3]*]");

  PlanificadorRR<int> p2;
  pp.agregarProceso(p2);  
  
  PlanificadorRR<PlanificadorRR<int> > pp2(pp);
  
  assert(pp == pp2);
  assert(pp2.hayProcesos() == true);
  assert(pp2.hayProcesosActivos() == true);
  assert(pp.procesoEjecutado() == pp2.procesoEjecutado());
  assert(pp.esPlanificado(p));
  
  pp.eliminarProceso(p);
  pp2.eliminarProceso(p);
  
  assert(pp == pp2);
  //p con 1 elemento inactivo == p con 1 elemento detenido?
  //probar mostrar    
}


int main()
{
  RUN_TEST( planificadorVacio );
  RUN_TEST( planificadorUnario );
  RUN_TEST( planificadorDec );
  RUN_TEST( test_copia );
  RUN_TEST( test_bordes );
  RUN_TEST( test_otrasop );
  // AGREGAR MAS TESTS...

  return 0;
}
