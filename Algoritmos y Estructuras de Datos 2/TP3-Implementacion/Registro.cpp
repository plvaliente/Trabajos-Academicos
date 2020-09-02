#include "Registro.h"

using namespace modulos;
using namespace aed2;

Conj<campo> Registro::Campos() const{
    const_Iterador it = CrearIt();
    Conj<campo> res;
    while(it.HaySiguiente()){
        res.AgregarRapido(it.SiguienteClave());
        it.Avanzar();
    }
    return res;
    
}

bool Registro::Borrable(const Registro& crit) const{
    assert(crit.Campos().Cardinal() == 1);
    const_Iterador itcrit = crit.CrearIt();
    campo c = itcrit.SiguienteClave();
    if(Definido(c)){                                       //Creo que en el diseño faltaba verificar que
        return (crit.Significado(c) == Significado(c));    //  la clave c este definida en el registro.
    }
    else{
        return false;
    }
}

Registro Registro::AgregarCampos(const Registro& otro) const{
    const_Iterador it2 = otro.CrearIt();
    Registro res = Registro(*this);
    while(it2.HaySiguiente()){
        if(!res.Definido(it2.SiguienteClave())){
            res.DefinirRapido(it2.SiguienteClave(), it2.SiguienteSignificado());
        }
        it2.Avanzar();
    }
    return res;
}

Registro Registro::CopiarCampos(const Conj<campo>& cc, const Registro& otro) const{             //Otra función que estaba mal el algoritmo en el diseño.
    Conj<campo>::const_Iterador itcc = cc.CrearIt();
    bool incluido = true;
    Conj<campo> campos = otro.Campos();
    while(itcc.HaySiguiente()){
        if(!campos.Pertenece(itcc.Siguiente())){
            incluido = false;
        }
        itcc.Avanzar();
    }
    assert(incluido);
    Conj<campo>::const_Iterador itc = cc.CrearIt();
    Registro res = Registro(*this);
    while(itc.HaySiguiente()){
        if(!res.Definido(itc.Siguiente())){
            res.DefinirRapido(itc.Siguiente(), otro.Significado(itc.Siguiente()));
        }
        itc.Avanzar();
    }
    return res;
}

bool Registro::CoincideAlguno(const Conj<campo>& cc, const Registro& otro) const{
    Conj<campo>::const_Iterador itcc = cc.CrearIt();
    bool incluido = true;
    Conj<campo> campos1 = otro.Campos();
    Conj<campo> campos2 = Campos();
    while(itcc.HaySiguiente()){
        if(!campos1.Pertenece(itcc.Siguiente()) || !campos2.Pertenece(itcc.Siguiente())){
            incluido = false;
        }
        itcc.Avanzar();
    }
    assert(incluido);
    
    Conj<campo>::const_Iterador itc = cc.CrearIt();
    bool res = false;
    while(itc.HaySiguiente() && !res){
        res = (Significado(itc.Siguiente()) == otro.Significado(itc.Siguiente()));
        itc.Avanzar();
    }
    return res;
}

bool Registro::CoincidenTodos(const Conj<campo>& cc, const Registro& otro) const{
    Conj<campo>::const_Iterador itcc = cc.CrearIt();
    bool incluido = true;
    Conj<campo> campos1 = otro.Campos();
    Conj<campo> campos2 = Campos();
    while(itcc.HaySiguiente()){
        if(!campos1.Pertenece(itcc.Siguiente()) || !campos2.Pertenece(itcc.Siguiente())){
            incluido = false;
        }
        itcc.Avanzar();
    }
    assert(incluido);
    
    Conj<campo>::const_Iterador itc = cc.CrearIt();
    bool res = true;
    while(itc.HaySiguiente() && res){
        res = (Significado(itc.Siguiente()) == otro.Significado(itc.Siguiente()));
        itc.Avanzar();
    }
    return res;
}

bool Registro::CoincidenTodosAux(const Conj<campo>& cc, const Registro& otro) const{
    Conj<campo>::const_Iterador itcc = cc.CrearIt();
    bool incluido = true;
    Conj<campo> campos = Campos();
    while(itcc.HaySiguiente()){
        if(!campos.Pertenece(itcc.Siguiente())){
            incluido = false;
        }
        itcc.Avanzar();
    }
    assert(incluido);
    
    Conj<campo>::const_Iterador itc = cc.CrearIt();
    bool res = true;
    while(itc.HaySiguiente() && res){
        if( otro.Definido(itc.Siguiente())){
            res = (Significado(itc.Siguiente()) == otro.Significado(itc.Siguiente()));
        }
        else{
            res = false;
        }
        itc.Avanzar();
    }
    return res;
}

bool Registro::enTodos(campo c, const Conj<Registro>& cr) const{
    Conj<Registro>::const_Iterador itcr = cr.CrearIt();
    bool res = true;
    while(itcr.HaySiguiente() && res){
        res = itcr.Siguiente().Definido(c);
        itcr.Avanzar();
    }
    return res;
}

Conj<Registro> Registro::CombinarTodos(campo c, const Conj<Registro>& cr) const{
    assert(Campos().Pertenece(c));
    assert(enTodos(c,cr));
    Conj<Registro>::const_Iterador itcr = cr.CrearIt();
    Conj<Registro> res;
    const Dato& sc = Significado(c);
    while(itcr.HaySiguiente()){
        const Registro& reg = itcr.Siguiente();
        if(sc == reg.Significado(c)){
            res.Agregar(AgregarCampos(reg));
        }
        itcr.Avanzar();
    }
    return res;
}

bool Registro::Sub(const Registro& otro) const{
    //assert(Registro(*this) == otro);
    const_Iterador itd = CrearIt();
    bool res = true;
    while(itd.HaySiguiente() && res){
        if(otro.Definido(itd.SiguienteClave())){
            //assert(itd.SiguienteSignificado() == otro.Significado(itd.SiguienteClave()));
            res = (itd.SiguienteSignificado() == otro.Significado(itd.SiguienteClave()));
        }
        else{
            res = false;
        }
        itd.Avanzar();
    }
    return res; //jodeme que nos olvidamos de devolver res
}