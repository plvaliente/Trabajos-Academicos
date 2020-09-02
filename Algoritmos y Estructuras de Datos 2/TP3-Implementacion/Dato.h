/*
 * Author: grupo_14
 *
 * Dato.
 * 
 */

#ifndef MODULOS_DATO_H_
#define MODULOS_DATO_H_

#include <ostream>
#include "aed2/TiposBasicos.h"

using namespace aed2;

namespace modulos {
    class Dato {
        public:
            Dato(String);                                   //Constructor string
            Dato(Nat);                                      //Constructor nat
            Dato& operator =(const Dato&);                  //Asignación
            bool operator <(const Dato&) const;             //Operador Menor
            bool operator >(const Dato&) const;             //Operador Mayor
            bool operator <=(const Dato&) const;            //Operador Menor o Igual
            bool operator ==(const Dato&) const;            //Operador Igual
            bool operator !=(const Dato&) const;            //Operador Igual
            bool Tipo() const;                              //Devuelve true si el dato es de tipo nat
            Nat ValorN() const;                             //Devuelve el valor de un dato nat
            String ValorS() const;                          //Devuelve el valor de un dato string
            bool mismoTipo(const Dato&) const;              //Devuelve true si son del mismo tipo
            bool esString() const;                          //Devuelve true si el dato es de tipo string
            bool esNat() const;                             //Devuelve true si el dato es de tipo nat
            
            
        private:
            String DatoString;                        
            Nat DatoNat;
            bool DatoTipo;                                  //Le cambie el nombre respecto al diseño para no confundir 
                                                            //  con función esNat(). Sigue guardando true si es Nat.
    };   
};
#endif 