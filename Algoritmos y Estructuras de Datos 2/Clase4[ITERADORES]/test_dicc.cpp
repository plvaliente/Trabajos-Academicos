// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "mini_test.h"
#include "Lista.h"


template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }

/*
 * Descripcion del test1
 */
void test1() {
  
  ASSERT(false);
}


/*
 * Descripcion del test2
 */
void test2() {
  
  ASSERT(false);
}



int main() {
  RUN_TEST(test1);
  RUN_TEST(test2); 

  return 0;
}

