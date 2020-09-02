/**
 * Programa de test muy basico para las distintas clases de lista que vemos en la teorica de implementacion en C++.
 * Al igual que las listas, seguimos el estandar C++03, salvo por aquellos conceptos fundamentales que requieren C++11.
 * Vale remarcar que el estilo de programacion en C++11/14 es muy distinto al de C++03, razon por la cual se podria
 * simplificar el codigo.  
 * 
 * El programa compila unicamente con GCC, ya que usa caracteristicas que le son propias.
 * 
 * Test basico: simplemente revisa el conjunto de operaciones minimales que implementamos para satisfacer los requerimientos
 *   del TAD.  Estan sacados del apunte de TADs.
 * 
 * Test sin constructor: verifica que no estemos suponiendo que el tipo parametrico \alpha (o Elem en este caso) tenga un 
 *   constructor por defecto o una operacion de asignacion.  Sí requiere que tenga un constructor por copia, ya que es lo minimo
 *   que requieren los contenedores en C++03.  En C++11/14 esta condicion se puede relajar aun mas, pidiendo que exista el constructor
 *   por movimiento (por ejemplo, cuando tenemos muchos recursos reservados puede ser eficiente "transferir" la propiedad de los mismos,
 *   pero no asi copiarlos).
 * 
 * Test eficiencia de copias: verifica que hagamos la minima cantidad de copias necesarias de un Elem al hacer un agregar_atras o 
 *   agregar_adelante.  Notar que siempre se hace la copia, salvo en C++11 si es posible "transferir" el elemento.
 * 
 * Test constness: verifica que no las operaciones respeten el constness (algo que en parte ya chequean los otros test cuando se usan
 *   rvalues) en las funciones primero y ultimo.  Notar que estas funciones son especiales en el sentido de que uno puede asignarle un
 *   valor al resultado, pero solamente cuando la lista es modificable.  En otras palabras:
 *   lista<int> l; l.agregar_atras(1); l.primero() = 2
 *   Es valido.  Ahora,
 *   const lista<int>& cl = l; cl.primero() = 3;
 *   Es invalido.  Notar que, a pesar que suene extraño, es posible asignar a l.primero() porque retorna una referencia!.  Entonces,
 *   tenemos un alias al primer elemento de la lista (que es un entero).
 * 
 * Test eficiencia de movimientos: muestra cómo usar las operaciones con semantica de movimiento para evitar las copias.  En la consola se
 *   ve que muchas copias se "evitan".  Esto requiere la nueva semantica de movimientos de C++11.
 * 
 * Test recorrido: muestra el uso de un iterador simple (mucho mas que el del estandar) para recorrer una lista constante (falta el caso
 *   de la lista modificable).  La idea es tener un objeto que nos permita recorrer en lugar de tener que construir una copia de la lista
 *   para recorrerla (copia innecesaria cuando queremos tomar, por ejemplo, los primeros 4 elementos de una lista de 10000000000).
 */


#include<cassert>
#include <iostream>

#include "lista.h" //Incluye la lista "adecuada" de acuerdo al test a realizar.
#include "print.h"

void message(const std::string& msg) {
    Print::get_instance().set(true);
    print(msg);
    Print::get_instance().set(false);
}

#if defined(TEST_BASICO)
void test_basico() {
    
    message("**** INICIANDO TEST BASICO ****");

    //Test de generadores
    lista<int> l; //idem <>
    
    for(int i = 999; i > -1; --i) {
        l.agregar_adelante(i); //idem puntito
    }
    
    lista<int> m;
    m = l; //operacion de asignacion.
    
    //Test de observadores
    for(int i = 0; i < 1000; ++i) {
        assert(l.primero() == i);  //idem prim
        assert(not l.es_vacia());   
        
        l.sacar_primero();    //idem fin
    }
    assert(l.es_vacia());
    assert(m.primero() == 0 && m.longitud() == 1000);
    
    //Test de otras operaciones
    for(int i = 0; i < 1000; ++i) {
        l.agregar_atras(i);      //idem circulito
    }
    
    assert(l.longitud() == 1000);
    
    assert(esta(l, 999));
    assert(esta(l, 0));
    assert(not esta(l, 1000));
    
    while(not l.es_vacia()) {
        int ultimo = l.ultimo();  //idem ult
        l.sacar_ultimo();          //idem com
        assert(l.es_vacia() || ultimo == l.ultimo() + 1);
    }
      
    m = l;
    l.agregar_adelante(1);
    for(int i = 0; i < 10; ++i) {
        l.concatenar(l);
    }
    assert(lista<int>(l).longitud() == 1024);
    assert(m.es_vacia());

    
}
#else
void test_basico() {}
#endif //defined(TEST_BASICO)


#if defined(TEST_SIN_CONSTRUCTOR)
class NoAsignableNiConstruiblePorDefecto {
    int x;
    
    NoAsignableNiConstruiblePorDefecto& operator=(NoAsignableNiConstruiblePorDefecto); //no se puede asignar!!!
    NoAsignableNiConstruiblePorDefecto(); //no se puede construir por defecto
    
public:
    NoAsignableNiConstruiblePorDefecto(int y) : x(y) {};
#if defined(CPP11)
    //Prohibimos el constructor por copia, fortaleciendo aun mas el tipo lista, al mostrar que funciona
    //siempre que exista el constructor por movimiento (si no existe, se usa el de por copia, asi que 
    //no se pierde generalidad).
    NoAsignableNiConstruiblePorDefecto(const NoAsignableNiConstruiblePorDefecto&) = delete; 
    NoAsignableNiConstruiblePorDefecto(NoAsignableNiConstruiblePorDefecto&& o) {x = o.x;}
#endif
    
};


void test_asignacion() {
    message("**** INICIANDO TEST SIN CONSTRUCTOR ****");

    lista<NoAsignableNiConstruiblePorDefecto> l;
    l.agregar_atras(NoAsignableNiConstruiblePorDefecto(4));
}
#else
void test_asignacion() {}
#endif //TEST_SIN_CONTRUCTOR


#if defined(TEST_EFICIENCIA_DE_COPIAS)
struct DificilDeCopiar {
    int copias;
    
    DificilDeCopiar(const DificilDeCopiar& otro) : copias(otro.copias + 1) {
        PRINT("estamos copiando algo dificil de copiar");
    }
    DificilDeCopiar() : copias(0) {}
    
    DificilDeCopiar& operator=(const DificilDeCopiar& otro) {
        copias = otro.copias + 1;
        PRINT("estamos asignando algo dificil de copiar");
    }
    
#ifdef CPP11 //C++11
    //tenemos que agregar constructor por movimiento, sino siempre copia.
    DificilDeCopiar(DificilDeCopiar&& otro) : copias(otro.copias) { }
    
    //y tenemos que recargar el operator= para movimientos
    DificilDeCopiar& operator=(DificilDeCopiar&& otro) {copias = otro.copias;}
#endif //C++11
};

void test_eficiencia() {
    message("**** INICIANDO TEST EFICIENCIA DE COPIAS ****");

    lista<DificilDeCopiar> l;
    
    Print::get_instance().set(true);
    DificilDeCopiar dificil;
#if defined(CPP11)
    //en el caso de C++11 evitamos la copia transfiriendo.
    l.agregar_atras(std::move(dificil));
#else
    l.agregar_atras(dificil);
#endif
    Print::get_instance().set(false);
    
    assert(l.primero().copias == l.ultimo().copias);

#if defined(CPP11)
    //no se deberian haber hecho copias, porque agregarmos atras "moviendo" el dificil de copiar
    assert(l.primero().copias == 0);
#else
    //se deberia haber hecho una unica copia, porque hicimos un unico agregar atras
    assert(l.primero().copias == 1);
#endif
}
#else
void test_eficiencia() {}
#endif //TEST_EFICIENCIA_DE_COPIAS

#if defined(TEST_CONSTNESS)
bool requiere_const(const lista<int>& l) {
    return (l.primero() == l.ultimo());
}

lista<int>& requiere_no_const(lista<int>& l) {
    l.primero() = l.ultimo();
    return l;
}

void test_constness() {
    message("**** INICIANDO TEST EFICIENCIA CONSTNESS ****");

    lista<int> l;
    l.agregar_atras(1);
    l.agregar_atras(2);
    assert(requiere_const(requiere_no_const(l)));
}
#else
void test_constness() {}
#endif //TEST_CONSTNESS

#if defined(TEST_EFICIENCIA_MOVIMIENTO)
#if defined(CPP03)
lista<int> concatenar(const lista<int>& l1, const lista<int>& l2) {
    lista<int> res(l1);
    res.concatenar(l2);
    return res;
}
#endif //CPP03

#if defined(CPP11)
/** 
 * Con la semantica de movimiento, se abren 4 posibilidades para los parametros:
 * - ambos son const ref
 * - uno es const ref y el otro ref-ref (2 posibilidades)
 * - ambos son ref-ref.
 * En general, una funcion con k parametros genera 2^k posibilidades.  Para 
 * evitar la explosion combinatoria, uno puede aprovecharse de la semantica de 
 * copia, que NO copia cuando los argumentos son rvalues.  Luego, escribe una
 * sola funcion.  Notar que un inconveniente de tal funcion es que *siempre* que
 * uno pasa un lvalue, el mismo se copia y no se reaprovecha su memoria (lo
 * que podria hacerse eventualmente).
 */

//Opcion multiples posibilidades:
// lista<int> concatenar(const lista<int>& l1, lista<int>&& l2) {
//     lista<int> res(l1);
//     res.concatenar(std::move(l2));
//     return res;
// }
// lista<int> concatenar(lista<int>&& l1, const lista<int>& l2) {
//     lista<int> res(std::move(l1));
//     res.concatenar(l2);
//     return res;
// }
// lista<int> concatenar(lista<int>&& l1, lista<int>&& l2) {
//     lista<int> res(std::move(l1));
//     res.concatenar(std::move(l2));
//     return res;
// }

//Opcion unica funcion
lista<int> concatenar(lista<int> l1, lista<int> l2) {
    lista<int> res(std::move(l1));
    res.concatenar(std::move(l2));
    return res;    
}
#endif //CPP11

void test_eficiencia_movimiento() {
    message("**** INICIANDO TEST EFICIENCIA DE MOVIMIENTOS ****");
    
    Print::get_instance().set(true);

    lista<int> l;
    lista<int> m;
    for(int i = 0; i < 1000; ++i) 
        l.agregar_atras(i);
    
    //Estamos copiando l dos veces (para concatenar)
    //pero no copiamos para asignar
    m = concatenar(l, l);

    //Estamos copiando l 4 veces para las concatenaciones internas,
    //pero luego no mas copias
    m = concatenar(concatenar(l, l), concatenar(l, l));

    lista<DificilDeCopiar> ds;
    ds.agregar_atras(DificilDeCopiar());

#if defined(CPP11)
    //En C++11 ya no se deberia copiar; usa movimiento!
    assert(ds.primero().copias == 0);
#endif
    
    //En C++11 ya no copia!!.
    ds.primero() = DificilDeCopiar();
#if defined(CPP11)
    //En C++11 ya no se deberia copiar; usa movimiento!
    assert(ds.primero().copias == 0);
#endif
    
    DificilDeCopiar dif;
    
#if defined(TEST7) or defined(CPP03)  //move existe en C++11
    ds.primero() = dif;
#else
    ds.primero() = std::move(dif); //lo transformo en rvalue para no copiar.
    assert(ds.primero().copias == 0);
#endif
    
    Print::get_instance().set(false);
}
#else
void test_eficiencia_movimiento() {}
#endif //TEST_EFICIENCIA_MOVIMIENTO


#if defined(TEST_RECORRIDO)
void test_recorrido() {
    message("**** INICIANDO TEST DE RECORRIDO ****");
    
    lista<int> l;

    //Test de otras operaciones
    for(int i = 0; i < 1000; ++i) {
        l.agregar_atras(i);      //idem circulito
    }
    
    Print::get_instance().set(true);
    assert(esta(l, 0));
    assert(esta(l, 999));
    assert(not esta(l, 1000));    
    Print::get_instance().set(false);
}
#else
void test_recorrido() {}
#endif

int main() {
    test_basico();
    test_asignacion();
    test_eficiencia();
    test_constness();
    test_eficiencia_movimiento();
    test_recorrido();
}