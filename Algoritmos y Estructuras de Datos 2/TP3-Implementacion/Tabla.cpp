#include "Tabla.h"

using namespace modulos;
using namespace aed2;

Tabla::Tabla(nombreTabla nombre, Conj<campo> claves, const Registro& reg){       //Constructor
    assert(claves.Cardinal() != 0);
    _nombre = nombre;
    _cantAccesos = 0;
    _hayIndiceNat = false;
    _campoIndiceNat = "";
    _hayIndiceString = false;
    _campoIndiceString = "";
    _columnas = reg;
    _claves = claves;
    //_registros = ContenedorReg();
    //_propiedades = Dicc<campo, minMax>();

}

Tabla::~Tabla(){ //Destructor
    _nombre="";
    _cantAccesos = 0;
    _hayIndiceNat = false;
    _campoIndiceNat = "";
    _hayIndiceString=false;
    _campoIndiceString="";
    Registro::Iterador it = _columnas.CrearIt();
    while(it.HaySiguiente()){
        it.EliminarSiguiente();
    }
    Conj<campo>::Iterador itT = _claves.CrearIt();
    while(itT.HaySiguiente()){
        itT.EliminarSiguiente();
    }
    Dicc<campo, minMax>::Iterador itD = _propiedades.CrearIt();
    while(itD.HaySiguiente()){
        itD.EliminarSiguiente();
    }
    //falta vaciar el contenedor
    //_registros.~ContenedorReg();
    // (_registros._indiceNat).~DiccNat< Lista< TuplaConjRegistros > >();
    // (_registros._indiceString).~DiccStr< Lista< TuplaConjRegistros > >(); //por alguna razon me da seg fault el destructor de DiccStr desde aca, en los test andaba
    // (_registros._registros).~Conj< Registro >();

}

Tabla::Tabla(const Tabla& otra){                                            //Constructor por copia
    *this = otra;

}

Tabla& Tabla::operator =(const Tabla& otra){
    _nombre = otra._nombre;
    _cantAccesos = otra._cantAccesos;
    _hayIndiceNat = otra._hayIndiceNat;
    _hayIndiceString = otra._hayIndiceString;
    _campoIndiceNat = otra._campoIndiceNat;
    _campoIndiceString = otra._campoIndiceString;
    _columnas = Registro(otra._columnas); //aca se crea un registro nuevo?

    //faltaban agregar estas
    _claves = otra._claves;
    _registros = otra._registros;
    _propiedades = otra._propiedades;

    return *this;
}

void Tabla::AgregarRegistro(const Registro& reg){
    assert(reg.Campos() == Campos());
    assert(PuedoInsertar(reg));

    Conj<Registro>::Iterador itReg = _registros._registros.AgregarRapido(reg);
    Lista<TuplaConjRegistros>::Iterador itTupNat;
    Lista<TuplaConjRegistros>::Iterador itTupStr;

    if(_hayIndiceNat){
        TuplaConjRegistros tup;
        tup._reg = itReg;

        if( _registros._indiceNat.Definido(reg.Significado(_campoIndiceNat).ValorN()) ){
            Lista<TuplaConjRegistros>::Iterador itTupNat = _registros._indiceNat.Obtener(reg.Significado(_campoIndiceNat).ValorN()).AgregarAdelante(tup);
        }
        else{
            Lista<TuplaConjRegistros> nuevaListaN;
            Lista<TuplaConjRegistros>::Iterador itTupNat = nuevaListaN.AgregarAdelante(tup);
            _registros._indiceNat.Definir(reg.Significado(_campoIndiceNat).ValorN(), nuevaListaN);
        }
    }
    if(_hayIndiceString){
        TuplaConjRegistros tup;
        tup._reg = itReg;
        if( _registros._indiceString.Definido(reg.Significado(_campoIndiceString).ValorS()) ){
            Lista<TuplaConjRegistros>::Iterador itTupStr = _registros._indiceString.Obtener(reg.Significado(_campoIndiceString).ValorS()).AgregarAdelante(tup);
        }
        else{
            Lista<TuplaConjRegistros> nuevaListaS;
            Lista<TuplaConjRegistros>::Iterador itTupStr = nuevaListaS.AgregarAdelante(tup);
            _registros._indiceString.Definir(reg.Significado(_campoIndiceString).ValorS(), nuevaListaS);
        }
    }
    if( _hayIndiceNat && _hayIndiceString ){
        itTupNat.Siguiente()._otroIndice = itTupStr;
        itTupStr.Siguiente()._otroIndice = itTupNat;
    }
    if(_hayIndiceNat){
        if(_propiedades.Definido(_campoIndiceNat)){
            if( reg.Significado(_campoIndiceNat) < _propiedades.Significado(_campoIndiceNat)._min ) {
                Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceNat);
                itmm.SiguienteSignificado()._min = reg.Significado(_campoIndiceNat);
            }
            if( reg.Significado(_campoIndiceNat) > _propiedades.Significado(_campoIndiceNat)._max ) {
                Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceNat);
                itmm.SiguienteSignificado()._max = reg.Significado(_campoIndiceNat);
            }
        }
        else{
            minMax mm(reg.Significado(_campoIndiceNat), reg.Significado(_campoIndiceNat));      //Se rompia en el caso que sea el primer registro. Tener en cuenta
            _propiedades.DefinirRapido(_campoIndiceNat, mm);                                    //   tambien en Indexar() en el caso de indexar una tabla sin registros.
        }
    }
    if(_hayIndiceString){
        if(_propiedades.Definido(_campoIndiceString)){
            if( reg.Significado(_campoIndiceString) < _propiedades.Significado(_campoIndiceString)._min ) {
                Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceString);
                itmm.SiguienteSignificado()._min = reg.Significado(_campoIndiceString);
            }
            if( reg.Significado(_campoIndiceString) > _propiedades.Significado(_campoIndiceString)._max ) {
                Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceString);
                itmm.SiguienteSignificado()._max = reg.Significado(_campoIndiceString);
            }
        }
        else{
            minMax mm(reg.Significado(_campoIndiceString), reg.Significado(_campoIndiceString));
            _propiedades.DefinirRapido(_campoIndiceString, mm);
        }        }
    _cantAccesos++;
}

void Tabla::BorrarRegistro(const Registro& crit){
    assert(crit.Campos().Cardinal() == 1);
    Registro::const_Iterador itCrit = crit.CrearIt();
    campo campoBorr = itCrit.SiguienteClave();
    assert(Claves().Pertenece(campoBorr));
    Dato valorBorr = itCrit.SiguienteSignificado();
    Dato valorIndiceNat = Dato(0);                                                      //Lo tengo que inicializar antes de entrar a los if.
    Dato valorIndiceString = Dato('a');                         
    //Lo tengo que inicializar antes de entrar a los if.
    if( _hayIndiceString && (campoBorr == _campoIndiceString) ){
        valorIndiceString = valorBorr;
        Lista<TuplaConjRegistros>::Iterador itRegBS = _registros._indiceString.Obtener(valorBorr.ValorS()).CrearIt();
        _cantAccesos++;
        if(_hayIndiceNat){
            valorIndiceNat = itRegBS.Siguiente()._reg.Siguiente().Significado(_campoIndiceNat);
            itRegBS.Siguiente()._otroIndice.EliminarSiguiente();
            if( _registros._indiceNat.Obtener(valorIndiceNat.ValorN()).Longitud() == 0){
                _registros._indiceNat.Borrar(valorIndiceNat.ValorN());
            }
        }
        itRegBS.Siguiente()._reg.EliminarSiguiente();
        _registros._indiceString.Borrar(valorBorr.ValorS());
    }

    if( _hayIndiceNat && (campoBorr == _campoIndiceNat) ){
        valorIndiceNat = valorBorr;
        Lista<TuplaConjRegistros>::Iterador itRegBN = _registros._indiceNat.Obtener(valorBorr.ValorN()).CrearIt();
        _cantAccesos++;
        if(_hayIndiceString){
            valorIndiceString = itRegBN.Siguiente()._reg.Siguiente().Significado(_campoIndiceString);
            itRegBN.Siguiente()._otroIndice.EliminarSiguiente();
            if( _registros._indiceString.Obtener(valorIndiceString.ValorS()).Longitud() == 0){
                _registros._indiceString.Borrar(valorIndiceString.ValorS());
            }
        }
        itRegBN.Siguiente()._reg.EliminarSiguiente();
        _registros._indiceNat.Borrar(valorBorr.ValorN());
    }
    bool noHayIndices = !(_hayIndiceString || _hayIndiceNat);
    bool cmpBorrNOEsIndStr = (_hayIndiceString && !(campoBorr == _campoIndiceString));
    bool cmpBorrNOEsIndNat = (_hayIndiceNat && !(campoBorr == _campoIndiceNat));

    if( noHayIndices || cmpBorrNOEsIndStr || cmpBorrNOEsIndNat){                                // Estaba mal la guarda en el diseño.
        Conj<Registro>::Iterador itReg = _registros._registros.CrearIt();
        while(itReg.HaySiguiente()){
            if(valorBorr == itReg.Siguiente().Significado(campoBorr)){
                if(_hayIndiceNat){
                    valorIndiceNat = itReg.Siguiente().Significado(_campoIndiceNat);
                    Lista<TuplaConjRegistros>::Iterador itBorr = _registros._indiceNat.Obtener(valorIndiceNat.ValorN()).CrearIt();
                    while(itBorr.HaySiguiente()){
                        if(itBorr.Siguiente()._reg.Siguiente() == itReg.Siguiente()){
                            if(_hayIndiceString){
                                valorIndiceString = itBorr.Siguiente()._reg.Siguiente().Significado(_campoIndiceString);
                                itBorr.Siguiente()._otroIndice.EliminarSiguiente();
                                if( _registros._indiceString.Obtener(valorIndiceString.ValorS()).Longitud() == 0 ){
                                    _registros._indiceString.Borrar(valorIndiceString.ValorS());
                                }
                            }
                            itBorr.EliminarSiguiente();
                        }
                        else{
                            itBorr.Avanzar();
                        }
                    }
                }
                if(_hayIndiceString){
                    valorIndiceString = itReg.Siguiente().Significado(_campoIndiceString);
                    Lista<TuplaConjRegistros>::Iterador itBorr = _registros._indiceString.Obtener(valorIndiceString.ValorS()).CrearIt();
                    while(itBorr.HaySiguiente()){
                        if(itBorr.Siguiente()._reg.Siguiente() == itReg.Siguiente()){
                            if(_hayIndiceNat){
                                valorIndiceNat = itBorr.Siguiente()._reg.Siguiente().Significado(_campoIndiceNat);
                                itBorr.Siguiente()._otroIndice.EliminarSiguiente();
                                if( _registros._indiceNat.Obtener(valorIndiceNat.ValorN()).Longitud() == 0 ){
                                    _registros._indiceNat.Borrar(valorIndiceNat.ValorN());
                                }
                            }
                            itBorr.EliminarSiguiente();
                        }
                        else{
                            itBorr.Avanzar();
                        }
                    }
                }
                itReg.EliminarSiguiente();
                _cantAccesos++;
            }
            else{
                itReg.Avanzar();
            }
        }
    }
    if(_hayIndiceNat){
        if(_propiedades.Definido(_campoIndiceNat)){                                     //Para el caso que se quiera borrar en tabla sin registros, y no este definido los indices en minMax
            if(_registros._registros.Cardinal() > 0){
                if(valorIndiceNat == _propiedades.Significado(_campoIndiceNat)._min ){
                    Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceNat);
                    itmm.SiguienteSignificado()._min = Dato(_registros._indiceNat.MinimaClave());
                }
                if(valorIndiceNat == _propiedades.Significado(_campoIndiceNat)._max ){
                    Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceNat);
                    itmm.SiguienteSignificado()._max = Dato(_registros._indiceNat.MaximaClave());
                }
            }
            else{                                                                       //Caso borre unico registro.
                _propiedades.Borrar(_campoIndiceNat);
            }
        }
    }
    if(_hayIndiceString){
        if(_propiedades.Definido(_campoIndiceString)){                                  //Para el caso que se quiera borrar en tabla sin registros, y no este definido los indices en minMax
            if(_registros._registros.Cardinal() > 0){
                if(valorIndiceString == _propiedades.Significado(_campoIndiceString)._min ){
                    Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceString);
                    itmm.SiguienteSignificado()._min = Dato(_registros._indiceString.MinimaClave());
                }
                if(valorIndiceString == _propiedades.Significado(_campoIndiceString)._max ){
                    Dicc<campo, minMax>::Iterador itmm = _propiedades.Buscar(_campoIndiceString);
                    itmm.SiguienteSignificado()._max = Dato(_registros._indiceString.MaximaClave());
                }
            }
            else{                                                                       //Caso borre unico registro.
                _propiedades.Borrar(_campoIndiceString);
            }
        }
    }
}

void Tabla::Indexar(campo indice) {
    assert ( PuedoIndexar(indice) );

    Conj<Registro>::Iterador itRegistros = _registros._registros.CrearIt();
    if (_columnas.Significado(indice).esNat()) {
        _campoIndiceNat = indice;
        _hayIndiceNat = true;
        while(itRegistros.HaySiguiente()) {
            Lista<TuplaConjRegistros>::Iterador itTupStr;
            if (_hayIndiceString) {
                Lista<TuplaConjRegistros>::Iterador itOtroIndice = _registros._indiceString.Obtener(itRegistros.Siguiente().Significado(_campoIndiceString).ValorS()).CrearIt();
                while(itOtroIndice.HaySiguiente() && !(itOtroIndice.Siguiente()._reg == itRegistros)) {
                    itTupStr = itOtroIndice.Siguiente()._otroIndice;
                    itOtroIndice.Avanzar();
                }
            }
            if (_registros._indiceNat.Definido(itRegistros.Siguiente().Significado(indice).ValorN())) {
                TuplaConjRegistros tup;
                tup._reg = itRegistros;
                tup._otroIndice = itTupStr;
                _registros._indiceNat.Obtener(itRegistros.Siguiente().Significado(indice).ValorN()).AgregarAdelante(tup);
            } else {
                Lista<TuplaConjRegistros> conjAux;
                TuplaConjRegistros tup;
                tup._reg = itRegistros;
                tup._otroIndice = itTupStr;
                conjAux.AgregarAdelante(tup);
                _registros._indiceNat.Definir(itRegistros.Siguiente().Significado(indice).ValorN(), conjAux);
            }
            if(_propiedades.Definido(_campoIndiceNat)) {
                if (itRegistros.Siguiente().Significado(indice) < _propiedades.Significado(_campoIndiceNat)._min) {
                    Dato maxAct = _propiedades.Significado(_campoIndiceNat)._max;
                    Dato nuevoMin = itRegistros.Siguiente().Significado(indice);
                    minMax m = minMax(nuevoMin, maxAct);
                    _propiedades.Borrar(_campoIndiceNat);
                    _propiedades.Definir(_campoIndiceNat, m);
                }
                if (itRegistros.Siguiente().Significado(indice) > _propiedades.Significado(_campoIndiceNat)._max) {
                    Dato minAct = _propiedades.Significado(_campoIndiceNat)._min;
                    Dato nuevoMax = itRegistros.Siguiente().Significado(indice);
                    minMax m = minMax(minAct, nuevoMax);
                    _propiedades.Borrar(_campoIndiceNat);
                    _propiedades.Definir(_campoIndiceNat, m);
                }
            } else {
                minMax m(itRegistros.Siguiente().Significado(indice), itRegistros.Siguiente().Significado(indice));
                _propiedades.Definir(_campoIndiceNat, m);
            }
            itRegistros.Avanzar();
        }
    }
    else {
        _campoIndiceString = indice;
        _hayIndiceString = true;
        while(itRegistros.HaySiguiente()) {
            Lista<TuplaConjRegistros>::Iterador itTupNat;
            if (_hayIndiceNat) {
                Lista<TuplaConjRegistros>::Iterador itOtroIndice = _registros._indiceNat.Obtener(itRegistros.Siguiente().Significado(_campoIndiceNat).ValorN()).CrearIt();
                while(itOtroIndice.HaySiguiente() && !(itOtroIndice.Siguiente()._reg == itRegistros)) {
                    itTupNat = itOtroIndice.Siguiente()._otroIndice;
                    itOtroIndice.Avanzar();
                }
            }

            if (_registros._indiceString.Definido(itRegistros.Siguiente().Significado(indice).ValorS())) {
                    TuplaConjRegistros tup;
                    tup._reg = itRegistros;
                    tup._otroIndice = itTupNat;
                    _registros._indiceString.Obtener(itRegistros.Siguiente().Significado(indice).ValorS()).AgregarAdelante(tup);
            } else {
                Lista<TuplaConjRegistros> conjAux;
                TuplaConjRegistros tup;
                tup._reg = itRegistros;
                tup._otroIndice = itTupNat;
                conjAux.AgregarAdelante(tup);
                _registros._indiceString.Definir(itRegistros.Siguiente().Significado(indice).ValorS(), conjAux);
            }
            if(_propiedades.Definido(_campoIndiceString)) {
                if (itRegistros.Siguiente().Significado(indice) < _propiedades.Significado(_campoIndiceString)._min) {
                        Dato maxAct = _propiedades.Significado(_campoIndiceString)._max;
                        Dato nuevoMin = itRegistros.Siguiente().Significado(indice);
                        minMax m(nuevoMin, maxAct);
                        _propiedades.Borrar(_campoIndiceString);
                        _propiedades.Definir(_campoIndiceString, m);
                }
                if (itRegistros.Siguiente().Significado(indice) > _propiedades.Significado(_campoIndiceString)._max) {
                    Dato minAct = _propiedades.Significado(_campoIndiceString)._min;
                    Dato nuevoMax = itRegistros.Siguiente().Significado(indice);
                    minMax m(minAct, nuevoMax);
                    _propiedades.Borrar(_campoIndiceString);
                    _propiedades.Definir(_campoIndiceString, m);
                }
            } else {
                minMax m(itRegistros.Siguiente().Significado(indice), itRegistros.Siguiente().Significado(indice));
                _propiedades.Definir(_campoIndiceString, m);
            }
            itRegistros.Avanzar();
        }
    }
}

nombreTabla Tabla::Nombre() const{
    return _nombre;
}

const Conj<campo> Tabla::Claves() const{
    //assert(_claves.Cardinal() != 0);
    return _claves;
}

const Conj<campo> Tabla::Indices() const{
    Conj<campo> ccampo;
    if( _hayIndiceNat ){
        ccampo.AgregarRapido(_campoIndiceNat);
    }
    if( _hayIndiceString ){
        ccampo.AgregarRapido(_campoIndiceString);
    }
    return ccampo;
}

Conj<campo> Tabla::Campos() const{
    return _columnas.Campos();
}

bool Tabla::esNat(campo c) const{
    return _columnas.Significado(c).esNat();
}

const Conj<Registro>& Tabla::Registros() const{
     return _registros._registros;
}


Nat Tabla::CantidadDeAccesos() const{
    return _cantAccesos;
}

bool Tabla::PuedoInsertar(const Registro& reg) const{
    return ( Compatible(reg)  && !HayCoincidencia(reg, Claves(), Registros()));
}

bool Tabla::Compatible(const Registro& reg) const{
    if(reg.Campos() == Campos()){
        return MismosTipos(reg);
    }
    else{
        return false;
    }
}

bool Tabla::HayCoincidencia(const Registro& r, const Conj<campo>& cc, const Conj<Registro>& cr) const{
    Conj<Registro>::const_Iterador itReg = cr.CrearIt();
    bool encCoinc = false;
    while(itReg.HaySiguiente() && !encCoinc){
        encCoinc = r.CoincideAlguno(cc, itReg.Siguiente());
        itReg.Avanzar();
    }
    return encCoinc;
}

bool Tabla::MismosTipos(const Registro& r) const{               //Assertion `Definido(clave)' failed.
    assert(r.Campos() == Campos());
    Conj<campo> cr = r.Campos();
    Conj<campo>::const_Iterador itRc = cr.CrearIt();
    bool res = true;
    while(itRc.HaySiguiente() && res){
        const campo& c = itRc.Siguiente();
        assert(r.Definido(c));
        const Dato& f = r.Significado(c);
        res = f.esNat() == esNat(c);
        itRc.Avanzar();
    }
    return res;
}

const Dato& Tabla::Minimo(campo c) const{
    return _propiedades.Significado(c)._min;
}

const Dato& Tabla::Maximo(campo c) const{
    return _propiedades.Significado(c)._max;
}

bool Tabla::PuedoIndexar(campo c) const{
    bool r = Campos().Pertenece(c);
    bool e = !Indices().Pertenece(c);
    // bool s = false;
    if( esNat(c) ){
        bool s = !_hayIndiceNat;
        return r && e && s;
    }
    else{
        bool s = !_hayIndiceString;
        return r && e && s;
    }

}

Conj<Registro> Tabla::Coincidencias(const Registro& r, const Conj<Registro>& cr) const{
    Conj<Registro>::const_Iterador itR = cr.CrearIt();
    Conj<Registro> res;
    while(itR.HaySiguiente()){
        if(r.CoincidenTodosAux(r.Campos(), itR.Siguiente())){
            res.AgregarRapido(itR.Siguiente());
        }
        itR.Avanzar();
    }
    return res;
}

Conj<Registro> Tabla::CoincidenciasRap(const Registro& r) const{
    Conj<Registro> res;
    if(!(PertenecenAIndices(r))){
        res = Coincidencias(r, Registros());
    }else{
        Registro::const_Iterador itR = r.CrearIt();
        //Conj<Registro> res; //si lo declaro aca se va a ir de scope antes del return
        bool continuar = true;
        bool matchS = false;
        bool matchN = false;
        bool keyN = false;
        bool keyS = false;
        String s;
        int v;
        //assert(itR.HaySiguiente());
        while( itR.HaySiguiente() && continuar){
            if( (_hayIndiceNat && (itR.SiguienteClave() == _campoIndiceNat && itR.SiguienteSignificado().esNat()))){
                if( Claves().Pertenece(itR.SiguienteClave()) ){
                    continuar = false;
                    matchN = true;
                    keyN = true;
                }
                else{
                    matchN = true;
                    v = itR.SiguienteSignificado().ValorN();
                }
            }
            if( _hayIndiceString && (itR.SiguienteClave() == _campoIndiceString && itR.SiguienteSignificado().esString())){
                if( Claves().Pertenece(itR.SiguienteClave()) ){
                    continuar = false;
                    matchS = true;
                    keyS = true;
                }
                else{
                    matchS = true;
                    s = itR.SiguienteSignificado().ValorS();
                }
            }
            if(continuar){
                itR.Avanzar();
            }
        }
        //assert(keyN);
        if(keyN){
            v = itR.SiguienteSignificado().ValorN();
            Lista<TuplaConjRegistros>& c = _registros._indiceNat.Obtener(v);
            //Lista<TuplaConjRegistros>::const_Iterador itC = _registros._indiceNat.Obtener(v).CrearIt();
            Lista<TuplaConjRegistros>::const_Iterador itC = c.CrearIt();
            //assert(itC.HaySiguiente());
            if(itC.HaySiguiente()){
                //assert((itC.Siguiente()._reg.Siguiente()) == r);
                //assert(r.Sub(itC.Siguiente()._reg.Siguiente()));
                if(r.Sub(itC.Siguiente()._reg.Siguiente())){
                    res.AgregarRapido(itC.Siguiente()._reg.Siguiente());
                }
            }
        }
        if(keyS){
            s = itR.SiguienteSignificado().ValorS();
            Lista<TuplaConjRegistros>& c = _registros._indiceString.Obtener(s);
            //Lista<TuplaConjRegistros>::const_Iterador itC = _registros._indiceString.Obtener(s).CrearIt();
            Lista<TuplaConjRegistros>::const_Iterador itC = c.CrearIt();
            if(itC.HaySiguiente()){
                if(r.Sub(itC.Siguiente()._reg.Siguiente())){
                    res.AgregarRapido(itC.Siguiente()._reg.Siguiente());
                }
            }
        }
        if(matchN && !(keyS ||
        keyN)){
            Lista<TuplaConjRegistros>& c = _registros._indiceNat.Obtener(v);
            //Lista<TuplaConjRegistros>::const_Iterador itC = _registros._indiceNat.Obtener(v).CrearIt();
            Lista<TuplaConjRegistros>::const_Iterador itC = c.CrearIt();
            while(itC.HaySiguiente()){
                if(r.Sub(itC.Siguiente()._reg.Siguiente())){
                    res.AgregarRapido(itC.Siguiente()._reg.Siguiente());
                }
                itC.Avanzar();
            }
        }
        if(matchS && !(keyS || keyN)){
            Lista<TuplaConjRegistros>& c = _registros._indiceString.Obtener(s);
            //Lista<TuplaConjRegistros>::const_Iterador itC = _registros._indiceString.Obtener(s).CrearIt();
            Lista<TuplaConjRegistros>::const_Iterador itC = c.CrearIt();

            while(itC.HaySiguiente()){
                if(r.Sub(itC.Siguiente()._reg.Siguiente())){
                    res.AgregarRapido(itC.Siguiente()._reg.Siguiente());
                }
                itC.Avanzar();
            }
        }
                //res.AgregarRapido(r);
    }

    return res;
}

Conj<Registro> Tabla::CombinarRegistros(campo c, const Conj<Registro>& cr1, const Conj<Registro>& cr2) const{
    Conj<Registro>::const_Iterador itRegs = cr1.CrearIt();
    Conj<Registro> regRes;
    while( itRegs.HaySiguiente()){
        const Registro& reg1 = itRegs.Siguiente();
        Conj<Registro> regsComb = reg1.CombinarTodos(c, cr2);
        Conj<Registro>::const_Iterador itRegsComb = regsComb.CrearIt();
        while(itRegsComb.HaySiguiente()){
            Registro regComb = itRegsComb.Siguiente();
            regRes.Agregar(regComb);
            itRegsComb.Avanzar();
        }
        itRegs.Avanzar();
    }
    return regRes;
}

Conj<Registro> Tabla::CombinarRegistrosRap(campo c, const Conj<Registro>& cr) const{

    if(Indices().Pertenece(c)){
        Conj<Registro>::const_Iterador itRegs = cr.CrearIt();
        Conj<Registro> regsComb;
        while(itRegs.HaySiguiente()){
            Registro reg1 = itRegs.Siguiente();
            if(esNat(c)){
                if(_registros._indiceNat.Definido(reg1.Significado(c).ValorN())){
                    Lista<TuplaConjRegistros> regs2 = _registros._indiceNat.Obtener(reg1.Significado(c).ValorN());
                    Lista<TuplaConjRegistros>::const_Iterador itRegs2 = regs2.CrearIt();
                    while(itRegs2.HaySiguiente()){
                        Registro reg2 = itRegs2.Siguiente()._reg.Siguiente();
                        Registro regComb = reg1.AgregarCampos(reg2);
                        regsComb.Agregar(regComb);
                        itRegs2.Avanzar();
                    }
                }
            }
            else{
                if(_registros._indiceString.Definido(reg1.Significado(c).ValorS())){
                    Lista<TuplaConjRegistros> regs2 = _registros._indiceString.Obtener(reg1.Significado(c).ValorS());
                    Lista<TuplaConjRegistros>::const_Iterador itRegs2 = regs2.CrearIt();
                    while(itRegs2.HaySiguiente()){
                        Registro reg2 = itRegs2.Siguiente()._reg.Siguiente();
                        Registro regComb = reg1.AgregarCampos(reg2);
                        regsComb.Agregar(regComb);
                        itRegs2.Avanzar();
                    }
                }
            }
            itRegs.Avanzar();
        }
        return regsComb;
    }
    else{
        return CombinarRegistros(c, cr, Registros());
    }
}

Conj<Dato> Tabla::DameColumna(campo c, const Conj<Registro>& cr) const{
    Conj<Registro>::const_Iterador itRegs = cr.CrearIt();
    Conj<Dato> columna;
    while(itRegs.HaySiguiente()){
        Dato dato = itRegs.Siguiente().Significado(c);
        columna.AgregarRapido(dato);
        itRegs.Avanzar();
    }
    return columna;
}
bool Tabla::PertenecenAIndices(const Registro& r) const{
    Registro::const_Iterador itR = r.CrearIt();
    bool res = false;
    while(itR.HaySiguiente() && !res){
        if((_hayIndiceNat && (itR.SiguienteClave() == _campoIndiceNat && itR.SiguienteSignificado().esNat())) || (_hayIndiceString && (itR.SiguienteClave() == _campoIndiceString && itR.SiguienteSignificado().esString())) ){
            res = true;
        }
        itR.Avanzar();
    }
    return res;
}

bool Tabla::HayIndiceNat() const{
    return _hayIndiceNat;
}
bool Tabla::HayIndiceString() const{
    return _hayIndiceString;
}

campo Tabla::IndiceNat() const{
    assert(HayIndiceNat());
    return _campoIndiceNat;
}

campo Tabla::IndiceString() const{
    assert(HayIndiceString());
    return _campoIndiceString;
}