#include "auxiliares.h"

/**
problema swap(x, y : Int)
    modifica x, y;
    asegura x == pre(y) && y == pre(x);
*/

// esta implementación cumple con la especificación?
void swapA(int x, int y){
    //local x, y;
    int t;
    t= x;
    //Estado 1;
    //vale x == pre(x) && y == pre(y) && t == x;
    x= y;
    //Estado 2;
    //vale y == y@1 && x == y@1 && t == t@1;
    //implica x == pre(y);
    y= t;
    //Estado 3;
    //vale y == t;
    //implica y == pre(x)
}//Pero que pasa al salir de esta funcion? Tiene algo que ver con el local?


void swapB(int &x, int &y){
    int t;
    t= x;
    //Estado 1;
    //vale x == pre(x) && y == pre(y) && t == x;
    x= y;
    //Estado 2;
    //vale y == y@1 && x == y@1 && t == t@1;
    //implica x == pre(y);
    y= t;
    //Estado 3;
    //vale y == t;
    //implica y == pre(x)
}//ahora sí!


void swapC(int &x, int &y){
    //Estado 0;
    //vale x == pre(x) && y == pre(y);
    x= x + y;
    //Estado 1;
    //vale x == x@0 + y@0 && y == y@1;
    //implica x== pre(x) + pre(y) && y == pre(y);
    y= x - y;
    //Estado 2;
    //vale y == x@1 - y@1 && x == x@1;
    //implica x== pre(x) + pre(y) && y == (pre(x) + pre(y)) - pre(y);
    //implica x== pre(x) + pre(y) && y == pre(x);
    x= x - y;
    //Estado 3;
    //vale y == y@2 && x= x@2 - y@2;
    //implica y == pre(x) && x== (pre(x) + pre(y)) - pre(x);
    //implica y == pre(x) && x== pre(y);
}


/**problema sumax(x: Int) = result: Int {
  requiere P: x >= 0;
  asegura result == sum([0..x])
}
*/
int sumax (int x) {
int s = 0, i = 0;
//vale P: x >= 0 && s == i == 0;
while (i < x) {
//invariante I: 0 <= i <= x && s == sum([0..i]);
i = i + 1;
s = s + i;
}
//vale Q: s == sum([0..x]);
return s;
//vale res == sum([0..x]);
}
