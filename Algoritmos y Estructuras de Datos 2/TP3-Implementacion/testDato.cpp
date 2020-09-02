// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "aed2.h"
#include "Modulos.h"


using namespace modulos;

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

void test() {
    Dato cero = Dato(0);
    Dato tuvieja = Dato("tuvieja") ;
    Dato tuvieja2 = Dato("tuvieja2");
    String s1 = "suno";
    String s2 = "sdos";
    ASSERT(s1 != s2);
    ASSERT_EQ( tuvieja == tuvieja2 , false );
    ASSERT_EQ( cero.Tipo() , true );
    ASSERT_EQ( cero.esNat() , true );
    ASSERT_EQ( tuvieja.Tipo() , false );
    ASSERT_EQ( cero.ValorN() , 0 );
    ASSERT_EQ( tuvieja.ValorS() , "tuvieja" );
    ASSERT_EQ( tuvieja.mismoTipo(cero) , false );
    ASSERT_EQ( tuvieja != cero , true );
    
    
    
}
  
int main()
{
  RUN_TEST( test );
  return 0;
}
