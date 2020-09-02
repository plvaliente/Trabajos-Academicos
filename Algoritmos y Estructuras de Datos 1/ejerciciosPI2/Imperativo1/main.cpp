#include <iostream>

using namespace std;

int cuadruple(int a);

int main()
{
    int a;
    cout << "Que número desea cuadruplicar?" << endl;
    cin >> a;
    cout << "El resultado es " << cuadruple(a) << endl;

    return 0;
}

/**
problema cuadruple(a : Int) = res : Int
    asegura res == 4 * a;
*/

int cuadruple(int a)
{
    int b;
    // Estado E1
    // vale a == pre(a)
    b = a + a;
    // Estado E2
    // vale b == a@E1 + a@E1
    //	implica b == 2 * pre(a)
    b = b + b;
    // Estado E3
    // vale b == b@E2 + b@E2
    //	implica b == 2 * a@E1 + 2 * a@E1
    //	implica b == 4 * pre(a)
    return b;
    // vale res == b@E3
    //  implica res == 4 * pre(a)
}
