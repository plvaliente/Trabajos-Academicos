#include "surtidor.h"

Surtidor::Surtidor() {

	ltsDisponibles = 0 ;
	precioXLitro = 0 ;
}

Surtidor::Surtidor(int litros, int precio) {

	ltsDisponibles = litros ;
	precioXLitro = precio ;
}

int Surtidor::litrosDisponibles() const {

	int ltDisp ;
	ltDisp = this->ltsDisponibles ;
	return ltDisp ;
}

int Surtidor::precioPorLitro() const {

	int PrecioLt ;
	PrecioLt = this->precioXLitro ;
	return PrecioLt ;
}

void Surtidor::expender(int cant) {

	this->ltsDisponibles = this->ltsDisponibles - cant ;
}
