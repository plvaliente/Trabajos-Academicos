#include "Driver.h"


bool aed2::operator == (const aed2::Columna& c1, const aed2::Columna& c2)
{
  return c1.nombre == c2.nombre and c1.tipo == c2.tipo;
}

using namespace aed2;
using namespace modulos;
////////////////////////////////////////////////////////////////////////////////
// Dato
////////////////////////////////////////////////////////////////////////////////

Driver::Dato::Dato(const aed2::Nat& x)
  : tipo_( NAT ), nat_( x )
{}

Driver::Dato::Dato(const aed2::String& x)
  : tipo_( STR ), str_( x )
{}

bool Driver::Dato::esNat() const
{
  return tipo_ == NAT;
}

bool Driver::Dato::esString() const
{
  return tipo_ == STR;
}

TipoCampo Driver::Dato::tipo() const
{
  return tipo_;
}

const aed2::Nat& Driver::Dato::dameNat() const
{
  assert( esNat() );
  return nat_;
}

const aed2::String& Driver::Dato::dameString() const
{
  assert( esString() );
  return str_;
}

bool Driver::Dato::operator == (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ == otro.nat_ ) or
    ( tipo_ == STR and str_ == otro.str_ )
  );
}

bool Driver::Dato::operator != (const Dato& otro) const
{
  return not (*this == otro);
}

////////////////////////////////////////////////////////////////////////////////
// Base de datos
////////////////////////////////////////////////////////////////////////////////

Driver::Driver()
{
  //_base.BaseDeDatos();
}

Driver::~Driver()
{
  //_base.~BaseDeDatos();
}

// Tablas

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
{
  Conj<Columna>::const_Iterador itColumnas = columnas.CrearIt();
  modulos::Registro campos;
  while(itColumnas.HaySiguiente()) {
    Columna c = itColumnas.Siguiente();
   // std::cout << c.nombre << std::endl; 
    if(c.tipo == NAT) {
      campos.Definir(campo(c.nombre), modulos::Dato(2));
    } else {
      campos.Definir(campo(c.nombre), modulos::Dato("S"));
    }
    itColumnas.Avanzar();
  }
  //std::cout << campos << std::endl; 
  Tabla t(nombre, claves, campos);
  _base.AgregarTabla(t);
  //std::cout << t.PuedoInsertar(campos) << std::endl;
  //  _base.
}

void Driver::insertarRegistro(const NombreTabla& tabla, const Registro& registro)
{
  // TODO ...
  modulos::Registro r;
  aed2::Driver::Registro::const_Iterador itClaves = registro.CrearIt();
  while(itClaves.HaySiguiente()) {
    if (itClaves.SiguienteSignificado().esNat()) {
      r.Definir(itClaves.SiguienteClave(), modulos::Dato(itClaves.SiguienteSignificado().dameNat()));  
    } else {
      r.Definir(itClaves.SiguienteClave(), modulos::Dato(itClaves.SiguienteSignificado().dameString()));  
    }
    
    itClaves.Avanzar();
  }
  //std::cout << _base.DameTabla(tabla).Campos() << std::endl;
  //std::cout << r << std::endl; 
  //std::cout << _base.DameTabla(tabla).PuedoInsertar(r) << std::endl;
  _base.InsertarEntrada(r, tabla);
  //assert(false);
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor)
{
  modulos::Registro r;
  if(valor.esNat()) {
      r.Definir(campo(columna), modulos::Dato(valor.dameNat()));
    } else {
      r.Definir(campo(columna), modulos::Dato(valor.dameString()));
    }
    _base.Borrar(r,tabla);
}

aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabla) const
{
  Conj<campo> Cps = _base.DameTabla(tabla).Campos();
  Conj<campo>::Iterador itCps =  Cps.CrearIt();
  aed2::Conj<Columna> ccna;
  while(itCps.HaySiguiente()){
    Columna c;
    c.nombre = itCps.Siguiente();
    if(_base.DameTabla(tabla).esNat(itCps.Siguiente())) {
      c.tipo = NAT;
    } else {
      c.tipo = STR;
    }
    ccna.AgregarRapido(c);
    itCps.Avanzar();
  }
  return ccna;
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabla) const
{
  return _base.DameTabla(tabla).Claves();
}

aed2::Conj<Driver::Registro> Driver::registrosDeTabla(const NombreTabla& tabla) const
{
  Conj<modulos::Registro> regs = _base.DameTabla(tabla).Registros(); //aca le da los registros de la tabla
  //apartir de aca los convierte
  aed2::Conj<Driver::Registro> res;
  Conj<modulos::Registro>::const_Iterador itRegs = regs.CrearIt();
  while(itRegs.HaySiguiente()) {
    modulos::Registro reg = itRegs.Siguiente();
    modulos::Registro::Iterador itReg = reg.CrearIt();
    Driver::Registro regD;
    //convierte un registro
    while(itReg.HaySiguiente()) { 
      if (itReg.SiguienteSignificado().esNat()) { 
        regD.Definir(itReg.SiguienteClave(),Driver::Dato(itReg.SiguienteSignificado().ValorN()));
      } else {
        regD.Definir(itReg.SiguienteClave(),Driver::Dato(itReg.SiguienteSignificado().ValorS()));
      }
      itReg.Avanzar();
    }
    res.AgregarRapido(regD);
    itRegs.Avanzar();
  }
  return res;
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const
{
  return _base.DameTabla(tabla).CantidadDeAccesos();
}

Driver::Dato Driver::minimo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  modulos::Dato dato = _base.DameTabla(tabla).Minimo(columna);
  if(dato.esNat()){
    return Driver::Dato(dato.ValorN());
  }
  else{
    return Driver::Dato(dato.ValorS());
  }
}

Driver::Dato Driver::maximo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  modulos::Dato dato = _base.DameTabla(tabla).Maximo(columna);
  if(dato.esNat()){
    return Driver::Dato(dato.ValorN());
  }
  else{
    return Driver::Dato(dato.ValorS());
  }
}

aed2::Conj<Driver::Registro> Driver::buscar(const NombreTabla& tabla, const Registro& criterio) const
{
  modulos::Registro r;
  aed2::Driver::Registro::const_Iterador itClaves = criterio.CrearIt();
  while(itClaves.HaySiguiente()) {
    if (itClaves.SiguienteSignificado().esNat()) {
      r.Definir(itClaves.SiguienteClave(), modulos::Dato(itClaves.SiguienteSignificado().dameNat()));  
    } else {
      r.Definir(itClaves.SiguienteClave(), modulos::Dato(itClaves.SiguienteSignificado().dameString()));  
    }
    
    itClaves.Avanzar();
  }
  Conj<modulos::Registro> regs = _base.Buscar(r, tabla);
  aed2::Conj<Driver::Registro> res;
  Conj<modulos::Registro>::const_Iterador itRegs = regs.CrearIt();
  while(itRegs.HaySiguiente()) {
    modulos::Registro reg = itRegs.Siguiente();
    modulos::Registro::Iterador itReg = reg.CrearIt();
    Driver::Registro regD;
    while(itReg.HaySiguiente()) { 
      if (itReg.SiguienteSignificado().esNat()) { 
        regD.Definir(itReg.SiguienteClave(),Driver::Dato(itReg.SiguienteSignificado().ValorN()));
      } else {
        regD.Definir(itReg.SiguienteClave(),Driver::Dato(itReg.SiguienteSignificado().ValorS()));
      }
      itReg.Avanzar();
      
    }
    res.AgregarRapido(regD);
    itRegs.Avanzar();
  }
  return res;
}

aed2::Conj<NombreTabla> Driver::tablas() const
{
return _base.TablasxNombre();
}

NombreTabla Driver::tablaMaxima() const
{
return _base.TablaMaxima();
}

// Indices

bool Driver::tieneIndiceNat(const NombreTabla& tabla) const
{
  return _base.DameTabla(tabla).HayIndiceNat();
}

bool Driver::tieneIndiceString(const NombreTabla& tabla) const
{
  return _base.DameTabla(tabla).HayIndiceString();
}

NombreCampo Driver::campoIndiceNat(const NombreTabla& tabla) const
{
  return _base.DameTabla(tabla).IndiceNat();
}

NombreCampo Driver::campoIndiceString(const NombreTabla& tabla) const
{
    return _base.DameTabla(tabla).IndiceString();
}

void Driver::crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo)
{
    _base.DameTabla(tabla).Indexar(campo);
}

void Driver::crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo)
{
    _base.DameTabla(tabla).Indexar(campo);
}

// Joins

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
    return _base.HayJoin(tabla1, tabla2);
}

NombreCampo Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
    return _base.CampoJoin(tabla1, tabla2);
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo)
{
    _base.GenerarVistaJoin(tabla1, tabla2, campo);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
    _base.BorrarJoin(tabla1, tabla2);
}

aed2::Conj<Driver::Registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)/* const*/
{
  //obtiene el iterador al join
  Conj<modulos::Registro>::const_Iterador itRegs = _base.VistaJoin(tabla1, tabla2);
  //apartir de aca los convierte
  aed2::Conj<Driver::Registro> res;
  while(itRegs.HaySiguiente()) {
    modulos::Registro reg = itRegs.Siguiente();
    modulos::Registro::Iterador itReg = reg.CrearIt();
    Driver::Registro regD;
    //convierte un registro
    while(itReg.HaySiguiente()) {
      if (itReg.SiguienteSignificado().esNat()) { 
        regD.Definir(itReg.SiguienteClave(),Driver::Dato(itReg.SiguienteSignificado().ValorN()));
      } else {
        regD.Definir(itReg.SiguienteClave(),Driver::Dato(itReg.SiguienteSignificado().ValorS()));
      }
      itReg.Avanzar();
    }
    res.AgregarRapido(regD);
    itRegs.Avanzar();
  }
  return res;

}

/*
int main() {
  Driver c;
  
  Conj<Columna> cols;
  Columna c1;
  c1.nombre ="id";
  c1.tipo=NAT;
  cols.AgregarRapido(c1);
  Columna c2;
  c2.nombre ="edad";
  c2.tipo=NAT;
  cols.AgregarRapido(c2);
  Columna c3;
  c3.nombre ="nombre";
  c3.tipo=STR;
  cols.AgregarRapido(c3);
  
  Conj<NombreCampo> claves;
  claves.AgregarRapido("id");
  
  c.crearTabla("test", cols, claves);
  
  aed2::Driver::Registro r;
  r.Definir("id", aed2::Driver::Dato(1));
  r.Definir("edad", aed2::Driver::Dato(22));
  r.Definir("nombre", aed2::Driver::Dato("tuvieja"));
  
  c.insertarRegistro("test", r);
  
  aed2::Driver::Registro r2;
  r2.Definir("id", aed2::Driver::Dato(2));
  r2.Definir("edad", aed2::Driver::Dato(23));
  r2.Definir("nombre", aed2::Driver::Dato("tuvieja2"));
  
  c.insertarRegistro("test", r2);
  
  aed2::Driver::Registro r3;
  r3.Definir("id", aed2::Driver::Dato(3));
  r3.Definir("edad", aed2::Driver::Dato(24));
  r3.Definir("nombre", aed2::Driver::Dato("tuvieja4"));
  
  c.insertarRegistro("test", r3);
  
  aed2::Driver::Registro criterio;
  criterio.Definir("edad", aed2::Driver::Dato(24));
  c.buscar("test", criterio);
}*/