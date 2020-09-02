#include "vector.h"
#include <math.h>


Vector::Vector() {

	abscisa = 0 ;
	ordenada = 0 ;
}

Vector::Vector(float a, float o) {

	abscisa = a ;
	ordenada = o ;
}

bool Vector::igualX (const Vector v) {

	bool res ;
	res = this->abscisa == v.abscisa ;
	return res ;
}

bool Vector::igualY (const Vector v) {

	bool res ;
	res = this->ordenada == v.ordenada ;
	return res ;
}

float Vector::modulo() const {

	float modulo;
	modulo = sqrt ( pow(this->abscisa,2) + pow(this->ordenada,2) ) ;
	return modulo ;

}

float Vector::prodEscalar(const Vector v) const {

	float prodE ;
	prodE = (this->abscisa * v.abscisa) + (this->ordenada * v.ordenada) ;
	return prodE ;
}

void Vector::resta(const Vector v) {

	this->abscisa = this->abscisa - v.abscisa ;
	this->ordenada = this->ordenada - v.ordenada ;
}
