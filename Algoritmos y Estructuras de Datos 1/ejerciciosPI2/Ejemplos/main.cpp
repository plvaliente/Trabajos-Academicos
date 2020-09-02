#include <iostream>
#include "auxiliares.h"

using namespace std;

int main()
{
    int x, y;
    cout << "Ingrese dos numeros enteros:" << endl;
    cout << "Valor para x: ";
    cin >> x;
    cout << "Valor para y: ";
    cin >> y;
    cout << "El valor de x es: " << x << ".El de y es: "<< y << endl << endl;

    cout << "Haciendo swapA..." << endl;
    swapA(x, y);
    cout << "El valor de x es: " << x << ".El de y es: "<< y << endl;
    cout << "Haciendo swapB..." << endl;
    swapB(x, y);
    cout << "El valor de x es: " << x << ".El de y es: "<< y << endl;
    cout << "Haciendo swapC..." << endl;
    swapC(x, y);
    cout << "El valor de x es: " << x << ".El de y es: "<< y << endl;

    // Si llegamos
    int n;
    cout << "Ingrese un numero natural:" << endl;
    cin >> n;
    cout << "La suma desde 0 hasta " << n << " es: "<< sumax(n) << endl;


    system("pause");
    return 0;
}
