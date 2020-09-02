#include <iostream>
#include "maths.h"

using namespace std;

int main()
{
  int valor; //Este va a ser el valor de fibonacci para calcular
  cout << "Ingresa el termino de fibonacci que queres calcular (max 100): ";
  cin >> valor;

  //Construimos la sucesion de fibonacci en el arreglo pasado por parametro
  cout << "Fibonacci de " << valor << " es: " ;
  cout << fibonacci(valor, valor) << endl;

  cout << "El valor absoluto de " << valor << " es: " ;
  cout << valorAbsoluto(valor) << endl;

  cout << "El signo de 5 es:" ;
  cout << signoYCambiar(5) << endl;

  cout << "El signo de " << valor << " es: " ;
  cout << signoYCambiar(valor) << endl;
  cout << "Y el numero quedó así: " << valor << endl;

  cout << "Es primo el número " << valor << "?" ;
  cout << primo(valor) << endl;

  return 0;
}
