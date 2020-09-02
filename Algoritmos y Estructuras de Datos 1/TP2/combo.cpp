#include "combo.h"
#include <string.h>
Combo::Combo(){
	_bebida = PestiCola ;
	_sandwich = McGyver ;
	_dificultad = 0;
}

Combo::Combo(const Bebida b, const Hamburguesa h, const Energia d ){
	_bebida = b ;
	_sandwich = h ;
	_dificultad = d;
}

Bebida Combo::bebidaC() const{
	Bebida res = this->_bebida ;
	return res ;
}

Hamburguesa Combo::sandwichC() const{
	Hamburguesa res = this->_sandwich ;
	return res ;
}

Energia     Combo::dificultadC() const{
	Energia res = this->_dificultad ;
	return res ;
}

void Combo::mostrar(std::ostream& os) const{
    os << "Bebida: " << _bebida << " | " << "Sandwich: " << _sandwich << " | " << "Dificultad: " << _dificultad ;
}


void Combo::guardar(std::ostream& os) const{
    os << " { C " << bebidaC() << " " <<  sandwichC() << " " << dificultadC() << " }" ;
}


void Combo::cargar (std::istream& is){
    //{ C FalsaNaranja CukiQueFresco 12 }
    string line;
    Bebida _b;
    string _sb;
    string _sh;    
    Hamburguesa _h;
    Energia _d;

    //leo el { 
    is >> line;
    //leo el 'C '
    is >> line;
    
    if (line == "C") {
        //sigo leyendo

        //leo la bebida
        is >> _sb;
        _b = recuperarBebidaDeString(_sb);
        //leo la hamburguesa
        is >> _sh;
        _h = recuperarHamburguesaDeString(_sh);
        //leo la dificultad
        is >> _d;

        //leo la }
        is >> line;

        this->_bebida = _b;
        this->_sandwich = _h;
        this->_dificultad = _d;
    } else {
        cout << "Archivo Invalido Combo";
    }
}

bool Combo::operator==(const Combo& otroCombo) const{
	bool igual = true ;
	if(this->_bebida != otroCombo._bebida){
		igual = false ;
	}
	else if(this->_sandwich != otroCombo._sandwich){
		igual = false ;
		}
	else if(this->_dificultad != otroCombo._dificultad){
		igual = false ;
		}
	return igual ;
}

std::ostream & operator<<(std::ostream & os,const Combo & c){
    c.mostrar(os);
	return os;
}

std::ostream & operator<<(std::ostream & os,const Hamburguesa & h){
    switch (h) {
        case McGyver:{
            os <<"McGyver";
            break;
        }
        case CukiQueFresco:{
            os <<"CukiQueFresco";
            break;            
        }
        case McPato:{
            os << "McPato";
            break;
        }
        case BigMacabra:{
            os <<"BigMacabra";
            break;            
        }
    }
    return os;

}

std::ostream & operator<<(std::ostream & os,const Bebida & b){
    switch (b) {
        case PestiCola:{
            os <<"PestiCola";
            break;
        }
        case FalsaNaranja:{
            os <<"FalsaNaranja";
            break;            
        }
        case SeVeNada:{
            os << "SeVeNada";
            break;
        }
        case AguaConGags:{
            os <<"AguaConGags";
            break;            
        }
        case AguaSinGags:{
            os <<"AguaSinGags";
            break;            
        }
    }
    return os;
}


Bebida recuperarBebidaDeString(string b) {
    Bebida _b;
    if (b ==  "PestiCola") { 
        _b = PestiCola;
    }
    if (b ==  "FalsaNaranja") { 
        _b = FalsaNaranja;
        
    }
    if (b ==  "SeVeNada") { 
        _b = SeVeNada;
        
    }
    if (b ==  "AguaConGags") { 
        _b = AguaConGags;
        
    }
    if (b ==  "AguaSinGags" ) { 
        _b = AguaSinGags;
        
    }
    return _b;
}

Hamburguesa recuperarHamburguesaDeString(string h) {
    Hamburguesa _h; 
    if(h=="McGyver") {
        _h = McGyver;
    }
    if(h=="CukiQueFresco") {
        _h = CukiQueFresco;
    }
    if(h=="McPato") {
        _h = McPato;
    }
    if(h=="BigMacabra") {
        _h = BigMacabra;
    }        
    return _h;
}