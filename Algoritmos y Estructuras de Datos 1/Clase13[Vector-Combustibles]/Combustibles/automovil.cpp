#include "automovil.h"

Automovil::Automovil() {

	capTanque = 0 ;
	litrosEnTanque = 0 ;
}

Automovil::Automovil(int cap, int litros) {

	capTanque = cap ;
	litrosEnTanque = litros ;
}

int Automovil::capacidadDelTanque() const {

	int cap ;
	cap = this->capTanque ;
	return cap ;
}

int Automovil::litrosEnElTanque() const {

	int litros ;
	litros = this->litrosEnTanque ;
	return litros ;
}

void Automovil::llenalo() {

	this->litrosEnTanque = this->capTanque ;
}
