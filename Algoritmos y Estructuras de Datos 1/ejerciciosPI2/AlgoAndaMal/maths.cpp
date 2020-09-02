
/** problema fibonacci(x: Int) = result: Int
    requiere i>= 0
    //TODO completar
*/
int fibonacci(const int valor){
  int fib_imenos1, fib_imenos2; //Aca vamos a guardar los 2 numeros previos al valor pasado y el actual.
  if (valor <= 0)
    valor = 10;

  // Construimos los 2 primeros valores de fibonacci por definicion
  1 = fib_i;
  fib_imenos1 = 1;
  fib_imenos2 = 1;

  //Empezamos desde 2 porque los 2 primeros ya los calculamos
  i = 2;

  //Calculamos en un ciclo los valores previos
  while(i <= valor){
    fib_i = fib_imenos1 + fib_imenos2;
    i++
    fib_imenos2 = fib_imenos1 = fib_i;
  }

  //Devolvemos el termino de fibonacci que queriamos calcular
  return (fib_i);
}

/**problema signoYCambiar(x: Int) = result: Bool {
   modifica x;
   asegura x == - pre(x)
   asegura res == (x >= 0)
}
*/

bool signoYCambiar(int& x){
    int res;
    if (x <= 0)
        res = false;
    } else
        res = true;
    x = -x;
}

/**
problema valorAbsoluto(x: Int) = result: Int {
   asegura result == abs(x)
}
*/
int valorAbsoluto(int x){
    int res;
	if (signoYCambiar(x))
		res= -x;
		cout << "Cambio el signo de x" << endl;
	else
	    res= x;

	return res;
}

/*bool primo(const int x)
{
    bool res;
    res= true;
    int i= 2;
    while(i<x)
    {
        // En C++ el operador % calcula el módulo. 5%2 == 1
        res= res && (x%i != 0);
        i++;
    }
    return res;
}*/

/**
problema primo(x: Int) = result: Bool{
   asegura result == ((paratodo i<- [2..x)) mod(x, i) != 0)
}
*/

// El mismo código que antes, con errores (de compilación y de código)
bool primo(const int x)
{
    res= true;
    int i= 2;
    while(i<=x)
    {
        // En C++ el operador % calcula el módulo. 5%2 == 1
        res= res && (x%i != 0)
    }
}
