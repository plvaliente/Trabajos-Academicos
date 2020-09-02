#include "Dato.h"

using namespace modulos;
using namespace aed2;

std::ostream& operator << (std::ostream &os, const Dato& d){
    if(d.Tipo()){
        os << d.ValorN();
    }
    else{
        os << d.ValorS();
    }
    return os;
}

Dato::Dato(String s){                                   //Constructor string
    DatoString = s; 
    DatoNat = 0;
    DatoTipo = false;
}

Dato::Dato(Nat n){                                      //Constructor nat
    DatoString = "";
    DatoNat = n;
    DatoTipo = true;
}

Dato& Dato::operator =(const Dato& otro){
    DatoString = otro.DatoString;
    DatoNat = otro.DatoNat;
    DatoTipo = otro.DatoTipo;
    return *this;
}

bool Dato::operator <=(const Dato& otro) const{
    assert(mismoTipo(otro));
    if(esNat()){
        return (DatoNat <= otro.DatoNat);
    }
    else{
        return (DatoString <= otro.DatoString);
    }
}

bool Dato::operator <(const Dato& otro) const{
    assert(mismoTipo(otro));
    if(esNat()){
        return (DatoNat < otro.DatoNat);
    }
    else{
        return (DatoString < otro.DatoString);
    }
}

bool Dato::operator >(const Dato& otro) const{
    assert(mismoTipo(otro));
    if(esNat()){
        return (DatoNat > otro.DatoNat);
    }
    else{
        return (DatoString > otro.DatoString);
    }
}

bool Dato::operator ==(const Dato& otro) const{        
    if(mismoTipo(otro)){
        if(esNat()){
            return (DatoNat == otro.DatoNat);
        }
        else{
            return (DatoString == otro.DatoString);
        }
    }
    else{
        return false;
    }
}

bool Dato::operator !=(const Dato& otro) const{        
    return !(*this == otro);
}

bool Dato::Tipo() const{   
    return DatoTipo;
}

Nat Dato::ValorN() const{ 
    assert(esNat());
    return DatoNat;
}

String Dato::ValorS() const{
    assert(esString());
    return DatoString;
}

bool Dato::mismoTipo(const Dato& otro) const{
    return DatoTipo == otro.DatoTipo;
}

bool Dato::esString() const{
    return !DatoTipo;
}

bool Dato::esNat() const{
    return DatoTipo;
}