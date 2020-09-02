/**
 * El siguiente header decide, en tiempo de compilacion, qué version de la lista cargar y cuáles de los tests ejecutar 
 * automaticamente.
 * 
 * Ademas setea las macros CPP03 y CPP11 para poder determinar el estandar usado.
 * 
 * Resumen:
 * TEST1: incluye lista-1.h -> compila el codigo objeto del test basico, pero como no tiene codigo, no linkea.
 * TEST2: incluye lista-2.h -> compila y linkea contra el test basico, aunque pierde memoria.
 * TEST3: incluye lista-3.h -> compila y linkea contra el test basico.
 * TEST4: incluye lista-4.h -> compila y linkea contra el test basico y el test sin constructor.
 * TEST5: incluye lista-5.h -> compila y linkea contra el test de eficiencia de copias.
 * TEST5full: incluye lista-5.h y trata de compilar con los test anteriores, pero falla.
 * TEST6: incluye lista-6.h -> compila y linkea contra los test basico, sin constructor y eficiencia de copias
 * TEST7: incluye lista-7.h -> compila y linkea contra los test basico, sin constructor, eficiencia de copias y constness
 * TEST8: incluye lista-8.h -> compila y linkea contra los test basico, sin constructor, eficiencia de copias, constness y eficiencia de movimientos.
 * TEST9: incluye lista-9.h -> compila y linkea contra todos los tests.
 * 
 * Hay que incluir el define correspondiente en tiempo de compilacion.  Por ejemplo:
 * - g++ -c test.cpp -DTEST1 -otest.o
 * - g++ test.cpp -DTEST8 --std=c++11 -otest8
 * 
 * Uno tambien puede incluir los siguientes defines para comprobar algun test no corroborado automaticamente:
 * - TEST_BASICO: incluye el test basico
 * - TEST_SIN_CONSTRUCTOR: incluye el test sin constructor
 * - TEST_EFICIENCIA_DE_COPIAS: incluye el test de eficiencia de copias
 * - TEST_CONSTNESS: incluye el test de constness
 * - TEST_EFICIENCIA_MOVIMIENTO: incluye el test de eficiencia de movimientos
 * - TEST_RECORRIDO: incluye el test de recorridos.
 *
 * Asi pues, si queremos comprobar como funciona list-6.h junto con el test de constness, podemos compilar usando
 * - g++ test.cpp -DTEST6 -DTEST_CONSTNESS -otest
 * y esperar a ver los errores de compilacion.
 * 
 * Para simplificar la vida, conviene usar el makefile, que nos permite compilar todo usando:
 * - make test#
 * donde # es el numero de test.  Tambien podemos ejecutar:
 * - make test#-extra
 * que compila el test # junto con la opcion siguiente (donde falla la compilacion o la ejecucion es mas ineficiente).
 * 
 * En cualquier caso, leer el makefile (no documentado) o apretar <TAB> en consola de shell (Linux) para ver las opciones.
 */

#if __cplusplus < 201103L 
    #define CPP03
#else
    #define CPP11
#endif

#if (defined(TEST8) or defined(TEST9)) and !defined(CPP11)
    #error "Los tests 8 y 9 requieren C++11; incluir --std=c++11 o --std=c++14."
#endif


#if defined(TEST9)
    #pragma message "Including lista-9.h"
    #include "lista-9.h"
#elif defined(TEST8)
    #pragma message "Including lista-8.h"
    #include "lista-8.h"
#elif defined(TEST7)
    #pragma message "Including lista-7.h"
    #include "lista-7.h"
#elif defined(TEST6)
    #pragma message "Including lista-6.h"
    #include "lista-6.h"
#elif defined(TEST5full)
    #pragma message "Including lista-5.h"
    #include "lista-5.h"
#elif defined(TEST5)
    #pragma message "Including lista-5.h"
    #include "lista-5.h"
#elif defined(TEST4)
    #pragma message "Including lista-4.h"
    #include "lista-4.h"
#elif defined(TEST3)
    #pragma message "Including lista-3.h"
    #include "lista-3.h"
#elif defined(TEST2)
    #pragma message "Including lista-2.h"
    #include "lista-2.h"
#elif defined(TEST1)
    #pragma message "Including lista-1.h"
    #include "lista-1.h"
#else
    #error "Incluir el numero de test de acuerdo a la version de lista usada. Ejemplo: TEST1 -> lista-1.h"
#endif

#if defined(TEST9)
#define APPLY8
#define TEST_RECORRIDO
#endif

#if defined(TEST8) or defined(APPLY8)
#define APPLY7
#define TEST_EFICIENCIA_MOVIMIENTO
#endif

#if defined(TEST7) or defined(APPLY7)
#define APPLY6
#define TEST_CONSTNESS
#endif

#if defined(TEST6) or defined(APPLY6)
#define APPLY5
#endif

#if defined(TEST5full) or defined(APPLY5)
#define APPLY4
#define TEST_EFICIENCIA_DE_COPIAS
#endif

#if defined(TEST5)
#define TEST_EFICIENCIA_DE_COPIAS
#endif

#if defined(TEST4) or defined(APPLY4)
#define APPLY3
#define TEST_SIN_CONSTRUCTOR
#endif

#if defined(APPLY3) or defined(TEST3) or defined(TEST2)
#define APPLY1
#endif

#if defined(APPLY1) or defined(TEST1)
#define TEST_BASICO
#endif

#if defined(TEST_BASICO)
#pragma message "+TEST_BASICO"
#else
#pragma message "-TEST_BASICO"
#endif

#if defined(TEST_SIN_CONSTRUCTOR)
#pragma message "+TEST_SIN_CONSTRUCTOR"
#else
#pragma message "-TEST_SIN_CONSTRUCTOR"
#endif //TEST_SIN_CONTRUCTOR


#if defined(TEST_EFICIENCIA_DE_COPIAS)
#pragma message "+TEST_EFICIENCIA_DE_COPIAS"
#else
#pragma message "-TEST_EFICIENCIA_DE_COPIAS"
#endif //TEST_EFICIENCIA_DE_COPIAS

#if defined(TEST_CONSTNESS)
#pragma message "+TEST_CONSTNESS"
#else
#pragma message "-TEST_CONSTNESS"
#endif //TEST_CONSTNESS

#if defined(TEST_EFICIENCIA_MOVIMIENTO)
#pragma message "+TEST_EFICIENCIA_MOVIMIENTO"
#else
#pragma message "-TEST_EFICIENCIA_MOVIMIENTO"
#endif //TEST_EFICIENCIA_MOVIMIENTO

#if defined(TEST_RECORRIDO)
#pragma message "+TEST_RECORRIDO"
#else
#pragma message "-TEST_RECORRIDO"
#endif //TEST_RECORRIDO
