#include "surtidor.h"
#include "automovil.h"
#include <iostream>

using namespace std;

int main(int argn, char* args[]) {
    
    int litrosSurt, precio;
    int litrosTanque, capTotal;
    
    cout << endl << "******SURTIDOR******" << endl;
    
    cout << "Litros de combustible en el surtidor: ";
    cin >> litrosSurt;
    cout << "Precio por litro de combustible: ";
    cin >> precio;
    Surtidor s(litrosSurt,precio);

    cout << endl << "******AUTOMOVIL******" << endl;
    
    cout << "Capacidad total del tanque: ";
    cin >> capTotal;
    cout << "Litros de combustible en el tanque: ";
    cin >> litrosTanque;
    Automovil a(capTotal,litrosTanque);

	int cargar = a.capacidadDelTanque() - a.litrosEnElTanque();

    if(s.litrosDisponibles() >= cargar){
		
		s.expender(cargar);
		a.llenalo();
		 
		cout << endl << "Llenamos el tanque, el auto ahora tiene  " << a.litrosEnElTanque() 
			<< " litros de combustible, y al surtidor le quedan " << s.litrosDisponibles() 
			<< " litros de combustible." << endl << "Al duenio del auto le salio $" << cargar*s.precioPorLitro() << endl;
	}else{
		cout << endl << "No se puede llenar el tanque." << endl;
	}
	
    return 0;
}
