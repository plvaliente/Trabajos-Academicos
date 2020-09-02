/*
 * Author: grupo_14
 *
 * Registro.
 * 
 */

#ifndef MODULOS_REGISTRO_H_
#define MODULOS_REGISTRO_H_

#include <ostream>
#include "aed2.h"
// #include "Basicos.h"
#include "Dato.h"

typedef String nombreTabla;
typedef String campo;

namespace modulos{
    class Registro : public Dicc<campo, Dato> {
        public:
            Conj<campo> Campos() const;
            bool Borrable(const Registro&) const;                             //Le cambie el nombre porque no puedo usar '?' y asi es mas descriptivo.
            Registro AgregarCampos(const Registro&) const;
            Registro CopiarCampos(const Conj<campo>&, const Registro&) const;
            bool CoincideAlguno(const Conj<campo>&, const Registro&) const;
            bool CoincidenTodos(const Conj<campo>&, const Registro&) const;
            bool CoincidenTodosAux(const Conj<campo>&, const Registro&) const;
            bool enTodos(campo,const Conj<Registro>&) const;
            Conj<Registro> CombinarTodos(campo,const Conj<Registro>&) const;
            bool Sub(const Registro&)const;
            
            bool operator !=(const Registro& otro) const{
                return !(*this == otro) ;
            }
    };
        struct TuplaConjRegistros{
        public:
            Conj<Registro>::Iterador _reg;
            Lista<TuplaConjRegistros>::Iterador _otroIndice;
            
            // void OtroIndice(const Conj<TuplaConjRegistros>::Iterador it) {
            //     _otroIndice = it;
            // }
            // TuplaConjRegistros() : _reg(NULL) , _otroIndice(NULL) {};
            // TuplaConjRegistros(Conj<modulos::Registro>::Iterador r, Conj<TuplaConjRegistros>::Iterador o) : Reg(r), OtroIndice(o){}
            
            bool operator !=(const TuplaConjRegistros& otro) const{
                return (!(_reg == otro._reg) || !(_otroIndice == otro._otroIndice)) ;
            }
            bool operator ==(const TuplaConjRegistros& otro) const{
                return ((_reg == otro._reg) && (_otroIndice == otro._otroIndice)) ;
            }
            TuplaConjRegistros(){
                Conj<Registro> c;
                _reg = c.CrearIt();
                Lista<TuplaConjRegistros> l;
                _otroIndice = l.CrearIt();
            }
            TuplaConjRegistros(Conj<Registro>::Iterador itR, Lista<TuplaConjRegistros>::Iterador otroI) : _reg(itR), _otroIndice(otroI){};
            //  ~TuplaConjRegistros(){
            //      while(_reg.HaySiguiente()){
            //                 _reg.EliminarSiguiente();
                    
            //      }
            //      while(_otroIndice.HaySiguiente()){
            //             _otroIndice.EliminarSiguiente();
            //      }
            //  }
        
    }; 
};
#endif


