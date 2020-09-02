#include "BaseDeDatos.h"

using namespace modulos;
using namespace aed2;

BaseDeDatos::BaseDeDatos(){ //Constructor
    Conj<nombreTabla> c;
    _nombresTablas = c;
    //DiccStr<datosTabla> d;  //comentado para probar, perdia memo
    //_tablas = d;
    _tablaMaxima = "";
    
}

BaseDeDatos::BaseDeDatos(const BaseDeDatos& otra){ //Constructor por copia
    *this = otra;
}

BaseDeDatos::~BaseDeDatos(){ //Destructor 
     Conj<nombreTabla>::Iterador it = _nombresTablas.CrearIt();
     while(it.HaySiguiente()){
         _tablas.Borrar(it.Siguiente());
         it.EliminarSiguiente();
     }
     _tablaMaxima = "";
 }

BaseDeDatos& BaseDeDatos::operator =(const BaseDeDatos& otra){ //Asignación
    _nombresTablas = otra._nombresTablas;
    _tablas = otra._tablas;
    _tablaMaxima = otra._tablaMaxima;

    return *this;
}

void BaseDeDatos::AgregarTabla( Tabla& t){ //Agrega una nueva tabla sin registros a la base de datos
    assert(t.Registros().EsVacio());
    assert(t.Claves().Cardinal() != 0);
    if (!(_tablas.Definido(t.Nombre()))){
        _nombresTablas.AgregarRapido(t.Nombre());
        datosTabla d(t);
        _tablas.Definir(t.Nombre(), d);
        if(this->_tablaMaxima == ""){
            _tablaMaxima=t.Nombre();
        }
    }
    assert(_tablas.Obtener(t.Nombre())._tabla.Claves().Cardinal() != 0);
}

void BaseDeDatos::ActualizarJoin(bool inserta, const Registro& r, const nombreTabla t){
    itTablas itTbl = _nombresTablas.CrearIt();
    datosTabla& datosT=_tablas.Obtener(t);
    while(itTbl.HaySiguiente()){
        nombreTabla nombreT = itTbl.Siguiente();
        if(HayJoin(t, nombreT)){
            Join& join = (datosT._joins).Obtener(nombreT);
            Modificacion tup(inserta, r, true);
            (join._modificaciones).AgregarAtras(tup);
        }
        itTbl.Avanzar();
    }
    itTbl = this->_nombresTablas.CrearIt();
    while(itTbl.HaySiguiente()){
        nombreTabla nombreT2 = itTbl.Siguiente();
        if(HayJoin(nombreT2, t)){
            datosTabla& datosT2 = _tablas.Obtener(nombreT2);
            Join& join2 = datosT2._joins.Obtener(t);
            Modificacion tup(inserta, r, false);
            (join2._modificaciones).AgregarAtras(tup);
        }
        itTbl.Avanzar();
    }        
}

void BaseDeDatos::InsertarEntrada(const Registro& r, const nombreTabla& t){ //Inserta un nuevo registro en la tabla cuyo nombre es pasado por parámetro
    assert(_nombresTablas.Pertenece(t));
    Tabla& tbl = DameTabla(t);
    assert(tbl.PuedoInsertar(r));
    Tabla& tablaMax = DameTabla(_tablaMaxima);
    tbl.AgregarRegistro(r);
    if(tbl.CantidadDeAccesos() > tablaMax.CantidadDeAccesos()){
         _tablaMaxima=tbl.Nombre();
     }
     ActualizarJoin(true, r, t);
}

void BaseDeDatos::Borrar(const Registro& r, nombreTabla t){ //Borra todos los registros de la tabla, cuyos datos del campo del registro coincidan con el dato del mismo registro
    assert(_nombresTablas.Pertenece(t));
    assert(r.Campos().Cardinal() == 1);
    Tabla& tablaMax = DameTabla(this->_tablaMaxima);
    Tabla& tbl = DameTabla(t);
    assert(tbl.Claves().Cardinal() != 0);
    //Conj<campo>::const_Iterador it = tbl.Claves().CrearIt();
    //ASSERT_EQ("cmp1", it.Siguiente());
    //ASSERT_EQ(tbl.Claves().Pertenece("cmp1"), true);
    tbl.BorrarRegistro(r);
    if(tbl.CantidadDeAccesos() > tablaMax.CantidadDeAccesos()){
        _tablaMaxima=tbl.Nombre();
    }
    ActualizarJoin(false, r, t);    
}

Conj<Registro>::const_Iterador BaseDeDatos::GenerarVistaJoin(nombreTabla t1, nombreTabla t2, campo c){             //Genera un join entre las tablas cuyos nombres son pasados por parámetro
    assert(_tablas.Definido(t1));
    assert(_tablas.Definido(t2));
    assert(t1 != t2);
    assert(DameTabla(t1).Claves().Pertenece(c));                         // assertion failed???
    assert(DameTabla(t2).Claves().Pertenece(c));
    assert(!HayJoin(t1, t2));
    /*********************GENERAMOS EL JOIN************************/
    datosTabla& datosT = _tablas.Obtener(t1);
    Registro camposCombinados;
    Conj<campo> camposT1 = DameTabla(t1).Campos();
    Conj<campo>::Iterador itCamposT1 = camposT1.CrearIt();
    while(itCamposT1.HaySiguiente()) {
    	if (DameTabla(t1).esNat(itCamposT1.Siguiente())) {
    		camposCombinados.Definir(itCamposT1.Siguiente(), Dato(2));
    	} else {
    		camposCombinados.Definir(itCamposT1.Siguiente(), Dato("s"));
    	}
    	itCamposT1.Avanzar();
    }
    Conj<campo> camposT2 = DameTabla(t2).Campos();
	Conj<campo>::Iterador itCamposT2 = camposT2.CrearIt();
	while(itCamposT2.HaySiguiente()) {
		if(!camposT1.Pertenece(itCamposT2.Siguiente())) {
			if (DameTabla(t2).esNat(itCamposT2.Siguiente())) {
				camposCombinados.Definir(itCamposT2.Siguiente(), Dato(2));
			} else {
				camposCombinados.Definir(itCamposT2.Siguiente(), Dato("s"));
			}
		}
		itCamposT2.Avanzar();
	}

    nombreTabla nombreJoin = "join";
    Conj<campo> claves;
    claves.AgregarRapido(c);
    Join join(c, nombreJoin, claves, camposCombinados);
    Tabla& cont = join._conjJoin;
	cont.Indexar(c);
	DiccStr<Join>& diccJoin = datosT._joins;
	diccJoin.Definir(t2, join);
	/*********************TERMINAMOS DE GENERAR EL JOIN************************/

	/***********AGREMOS LOS REGISTROS COMBINADOS**************************/
	const Conj<Registro>& regsT1 = Registros(t1);
    Tabla& tablat2 = DameTabla(t2);
    Conj<Registro> regsComb = tablat2.CombinarRegistrosRap(c, regsT1);
    Conj<Registro>::Iterador itRegsComb = regsComb.CrearIt();
    if(itRegsComb.HaySiguiente()) {
    	while(itRegsComb.HaySiguiente()){
			Registro regComb = itRegsComb.Siguiente();
			cont.AgregarRegistro(regComb);
			itRegsComb.Avanzar();
		 }
    }
	return cont.Registros().CrearIt();

    /***********AGREMOS LOS REGISTROS COMBINADOS**************************/
}

void BaseDeDatos::BorrarJoin(nombreTabla t1, nombreTabla t2){  //Borra el join entre las tablas cuyos nombres son pasados por parámetro
    assert(HayJoin(t1,t2));
    datosTabla& datosT = this->_tablas.Obtener(t1);
    (datosT._joins).Borrar(t2);
}

itTablas BaseDeDatos::Tablas() const{ //Devuelve un iterador de Tablas con siguiente
    itTablas itTbl = _nombresTablas.CrearIt();
    return itTbl;
}

Tabla& BaseDeDatos::DameTabla(nombreTabla t) const{ //Devuelve la tabla de la base de datos cuyo nombre es pasado por parametro
    return _tablas.Obtener(t)._tabla;
}

bool BaseDeDatos::HayJoin(nombreTabla t1, nombreTabla t2) const{            //Devuelve si hay join entre las dos tablas

    if(_tablas.Definido(t1) && _tablas.Definido(t2)){ 
        datosTabla& datosT =_tablas.Obtener(t1);
        return datosT._joins.Definido(t2);
    }
    else{
        return false;
    }
}

campo BaseDeDatos::CampoJoin(nombreTabla t1, nombreTabla t2) const{ //Devuelve el campo por el cual hay join en las tablas
    datosTabla& datosT = this->_tablas.Obtener(t1);
    campo res = ((datosT._joins).Obtener(t2))._campo;
    return res;
}

const Conj<Registro>& BaseDeDatos::Registros(nombreTabla t) const{  //Devuelve el conjunto de registros de la tabla
    assert(_tablas.Definido(t));
    datosTabla& datosT = _tablas.Obtener(t);
    
    /*Tabla& t1 = datosT._tabla;
    return t1.Registros();*/
    return datosT._tabla.Registros();
}

Conj<Registro>::const_Iterador BaseDeDatos::VistaJoin(nombreTabla t1, nombreTabla t2){  //Actualiza y devuelve el join entre las dos tablas
    assert(HayJoin(t1,t2));
    datosTabla& datosT = _tablas.Obtener(t1);
    Join& join = (datosT._joins).Obtener(t2);
    Lista<Modificacion>::Iterador itMod = (join._modificaciones).CrearIt();
    /***********iteramos sobre las modificaciones del join de t1 a t2******/
    /**Hay que agregar un if para actualizar solo las modificacioens de borrar cuento sea estaTabla***/
    while(itMod.HaySiguiente()){
        const Modificacion& mod = itMod.Siguiente();
        if(mod._inserto && mod._origenEsta) {
        	Registro busqueda;
        	busqueda.Definir(CampoJoin(t1,t2), mod._reg.Significado(CampoJoin(t1,t2)));
        	const Conj<Registro> conjOtra = Buscar(busqueda, t2);
        	Conj<Registro> conjReg1;
			conjReg1.AgregarRapido(mod._reg);
			Tabla& t = DameTabla(t1);
			Conj<Registro> regsComb = t.CombinarRegistros((join._campo), conjReg1, conjOtra);
			Conj<Registro>::Iterador itRegsComb = regsComb.CrearIt();
			while(itRegsComb.HaySiguiente()){
				Registro regComb = itRegsComb.Siguiente();
				if(join._conjJoin.PuedoInsertar(regComb)){
                    join._conjJoin.AgregarRegistro(regComb);
                }
				itRegsComb.Avanzar();
			}
        } else if (mod._inserto && !mod._origenEsta) {
        	Registro busqueda;
        	busqueda.Definir(CampoJoin(t1,t2), mod._reg.Significado(CampoJoin(t1,t2)));
        	const Conj<Registro> conjOtra = Buscar(busqueda, t1);
        	Conj<Registro> conjReg1;
			conjReg1.AgregarRapido(mod._reg);
			Tabla& t = DameTabla(t1);
			Conj<Registro> regsComb = t.CombinarRegistros((join._campo), conjOtra, conjReg1);
			Conj<Registro>::Iterador itRegsComb = regsComb.CrearIt();
			while(itRegsComb.HaySiguiente()){
				Registro regComb = itRegsComb.Siguiente();
                if(join._conjJoin.PuedoInsertar(regComb)){
				    join._conjJoin.AgregarRegistro(regComb);
                }
				itRegsComb.Avanzar();
			}
        } else if (!mod._inserto) {
			//LA MODIFICACIONE FUE BORRAR. NO IMPORTA EN QUE TABLA FUE. BORRAMOS EN EL JOIN EL CRITERIO QUE USO PARA BORRAR EN ALGUNA DE LAS DOS TABLAS.
			join._conjJoin.BorrarRegistro(mod._reg);
		}

        itMod.EliminarSiguiente();
    }
    return join._conjJoin.Registros().CrearIt();
}

void BaseDeDatos::AuxActContenedor(ContenedorReg& cont, Registro& r, const Modificacion& m, campo c, bool esnat){
    if (esnat) {
        Nat DatoNat = (r.Significado(c)).ValorN();
        if ((cont._indiceNat).Definido(DatoNat)){
            Lista< TuplaConjRegistros > ConjIts = (cont._indiceNat).Obtener(DatoNat);
            if (m._inserto){
                Conj<Registro>::Iterador itRegComb = (cont._registros).AgregarRapido(r);
                Lista<TuplaConjRegistros> l;
                Lista<TuplaConjRegistros>::Iterador it = l.CrearIt();
                TuplaConjRegistros tup(itRegComb, it);
                ConjIts.AgregarAdelante(tup);
            }else{
                AuxBorrarDelJoin(ConjIts, c, DatoNat, esnat);
            } 
        }else{
            Lista< TuplaConjRegistros > ConjIts;
            (cont._indiceNat).Definir(DatoNat, ConjIts);
            if (m._inserto){
                Conj<Registro>::Iterador itRegComb = (cont._registros).AgregarRapido(r);
                Lista<TuplaConjRegistros> l;
                Lista<TuplaConjRegistros>::Iterador it = l.CrearIt();                    
                TuplaConjRegistros tup(itRegComb, it);
                ConjIts.AgregarAdelante(tup);
            }
        }
    }else{
        String DatoString = (r.Significado(c)).ValorS();
        if ((cont._indiceString).Definido(DatoString)){
            Lista< TuplaConjRegistros > ConjIts = (cont._indiceString).Obtener(DatoString);
            if (m._inserto){
                Conj<Registro>::Iterador itRegComb = (cont._registros).AgregarRapido(r);
                Lista<TuplaConjRegistros> l;
                Lista<TuplaConjRegistros>::Iterador it = l.CrearIt();                    
                TuplaConjRegistros tup(itRegComb, it);
                ConjIts.AgregarAdelante(tup);
            }else{
                AuxBorrarDelJoin(ConjIts, c, DatoString, esnat);
            } 
        }else{
            Lista< TuplaConjRegistros > ConjIts;
            (cont._indiceString).Definir(DatoString, ConjIts);
            if (m._inserto){
                Conj<Registro>::Iterador itRegComb = (cont._registros).AgregarRapido(r);
                Lista<TuplaConjRegistros> l;
                Lista<TuplaConjRegistros>::Iterador it = l.CrearIt();                    
                TuplaConjRegistros tup(itRegComb, it);
                ConjIts.AgregarAdelante(tup);
            }
        }       
    }
}

void BaseDeDatos::AuxBorrarDelJoin(Lista< TuplaConjRegistros >& its, campo c, Dato dat, bool esnat){
    Lista<TuplaConjRegistros>::Iterador itConjIts = its.CrearIt();
    while(itConjIts.HaySiguiente()){
        Conj<Registro>::Iterador itReg = (itConjIts.Siguiente())._reg;
        Registro regB = itReg.Siguiente();
        Dato datoR = regB.Significado(c);
        if (datoR == dat) { //cambie la guarda porque comparaba nat/strings con datos
            itReg.EliminarSiguiente();
            itConjIts.EliminarSiguiente();
        }else{
            itConjIts.Avanzar();
        }
    }
}

Nat BaseDeDatos::CantidadDeAccesos(nombreTabla t) const{ //Devuelve la cantidad de accesos de la tabla
    datosTabla& datosT = this->_tablas.Obtener(t);
    return (datosT._tabla).CantidadDeAccesos();
}

nombreTabla BaseDeDatos::TablaMaxima() const{ //Devuelve el nombre de la tabla máxima de la base de datos
    return _tablaMaxima;
}

nombreTabla BaseDeDatos::EncontrarMaximo(nombreTabla t, Conj<nombreTabla>& ct) const{ //Devuelve el nombre de la tabla máxima de entre una tabla y conjunto de tablas
    itTablas itTbl = ct.CrearIt();
    nombreTabla res = t;
    while(itTbl.HaySiguiente()){
        nombreTabla nombreT = itTbl.Siguiente();
        if(DameTabla(res).CantidadDeAccesos() <= DameTabla(nombreT).CantidadDeAccesos()){
            res = nombreT;
        }
        itTbl.Avanzar();
    }
    return res;
}

const Conj<Registro> BaseDeDatos::Buscar(const Registro& r, nombreTabla t) const{ //Devuelve un conjunto con los registros de la tabla que coincidan en campo y dato para cada campo del registro.
    Tabla& tbl = DameTabla(t);
    return tbl.CoincidenciasRap(r);
}

Conj<nombreTabla> BaseDeDatos::TablasxNombre() const{
    return _nombresTablas;
}