/*
 * Author: grupo_14
 *
 * Tabla.
 *
 */



#ifndef MODULOS_TABLA_H_
#define MODULOS_TABLA_H_



#include "aed2.h"
// #include "Basicos.h"
#include "Registro.h"
#include "DiccNat.h"
#include "DiccStr.h"
//#include <ostream>


namespace modulos {
    struct minMax{
        Dato _min, _max;
        
        minMax(const Dato& min, const Dato& max) : _min(min) , _max(max){} ;
    }; 
    
 
    

    struct ContenedorReg{
        DiccNat< Lista< TuplaConjRegistros > > _indiceNat;                  // Hablar con Fischer. Con conjunto no puedo implementar los iteradores cruzados en los
        DiccStr< Lista< TuplaConjRegistros > > _indiceString;               //  "_otroIndice" de las TuplasConjRegistros sin modificar un elemento dentro del mismo.
        Conj< Registro > _registros;

        // ~ContenedorReg(){
        //      Conj< Registro >::Iterador itCReg = _registros.CrearIt();
        //      while(itCReg.HaySiguiente()){
        //          itCReg.EliminarSiguiente();
        //      }
        //      _indiceNat.~DiccNat< Lista< TuplaConjRegistros > >();
        //      _indiceString.~DiccStr < Lista < TuplaConjRegistros > >();  // Hay un problema en este destructor para el caso que no tenga nada.
        // }
    }; 
    

   struct Modificacion{
        bool _inserto;
        bool _origenEsta;
        const Registro _reg;                           //porque &? donde esta guardado ese registro? Ver ejemplos en TestBDD lineas 145/149
        Modificacion(bool inserto, const Registro& r, bool esta) : _inserto(inserto), _reg(r), _origenEsta(esta){} ;//probando

        bool operator !=(const Modificacion& otro) const{
            return ((_inserto != otro._inserto) || (_reg != otro._reg)) ;
        }
    };

    class Tabla {
        public:
            Tabla(nombreTabla, Conj<campo>, const Registro&);               //Constructor
            Tabla(const Tabla&);                                            //Constructor por copia
            ~Tabla();                                                      //Destructor
            Tabla& operator =(const Tabla&);                                //Asignación
            void AgregarRegistro(const Registro&);                          //Agrega un Registro a la tabla
            void BorrarRegistro(const Registro&);                           //Borra un Registro de la tabla segun el criterio
            void Indexar(campo);                                            //Indexa la tabla por el campo
            nombreTabla Nombre() const;                                     //Retorna el nombre de la tabla
            const Conj<campo> Claves() const;                                     //Retorna un conjunto con la sclaves de la tabla
            const Conj<campo> Indices() const;                                    //Retorna un conjunto con los indices de la tabla
            Conj<campo> Campos() const;                                     //Retorna un conjunto con los campos de la tabla
            bool esNat(campo) const;                                        //Devuelve verdadero si el campo es de tipo nat
            const Conj<Registro>& Registros() const;                        //Retorna un conjunto con los registros de la tabla
            Nat CantidadDeAccesos() const;                                  //Retorna los accesos de la tabla
            bool PuedoInsertar(const Registro&) const;                      //Devuelve verdadero si el registro r es insertabla
            bool Compatible(const Registro&) const;                         //Devuelve verdadero si el registro r tiene los mismos campos y tipos que la tabla
            bool HayCoincidencia(const Registro&, const Conj<campo>&, const Conj<Registro>&) const;
                                                                            //Devuelve verdadero si en el registro, y un registro de cr coincide en campo y dato para algun campo de cc
            bool MismosTipos(const Registro&) const;                        //Devuelve verdadero si el registro tiene los mismos campos y tipos para cada uno de ellos
            const Dato& Minimo(campo) const;                                //Devuelve el minimo de los datos correspondientes al campo
            const Dato& Maximo(campo) const;                                //Devuelve el maximo de los datos correspondientes al campo
            bool PuedoIndexar(campo) const;                                 //Devuelve verdadero si se puede indexar la tabla por el campo
            Conj<Registro> Coincidencias(const Registro&, const Conj<Registro>&) const;
                                                                            //Devuelve un conjunto con los registros de cr que coincidan en campo y dato para cada campo del registro
            Conj<Registro> CoincidenciasRap(const Registro&) const;         //Devuelve un conjunto con los registros que coincidan en campo y dato para cada campo del registro
                                                                            //utilizando los campos indexados de t (en caso de existir) para poder encontrar las coincidencias en menor tiempo
            Conj<Registro> CombinarRegistros(campo, const Conj<Registro>&, const Conj<Registro>&) const;
                                                                            //Devuelve un conjunto el cual es el resultado de la UNION de aplicar combinarTodos(c,cr1i
                                                                            //para todo cr1i registro de cr1
            Conj<Registro> CombinarRegistrosRap(campo, const Conj<Registro>&) const;
            Conj<Dato> DameColumna(campo, const Conj<Registro>&) const;     //Devuelve un conjunto con los datos del campo c para cada registro de la tabla
            bool HayIndiceNat() const;          //Devuelve si hay Indice nat. DRIVER
            bool HayIndiceString() const;       //IDEM. DRIVER
            campo IndiceNat() const;            //Devuelve el campo. DRIVER
            campo IndiceString() const;         //IDEM. DRIVER
            

        private:
            nombreTabla _nombre;
            Nat _cantAccesos;
            bool _hayIndiceNat;
            campo _campoIndiceNat;
            bool _hayIndiceString;
            campo _campoIndiceString;
            Registro _columnas;
            Conj<campo> _claves;
            ContenedorReg _registros;
            Dicc<campo, minMax> _propiedades;
            bool PertenecenAIndices(const Registro& r) const;
    };


    struct Join{
    	campo _campo;
    	Lista<Modificacion> _modificaciones;   //Lista de modificaciones?? Si Agrego un registro y despues lo borro,
    	Tabla _conjJoin;
    	Join(campo c, nombreTabla nj, Conj<campo> claves, const Registro& campos) : _campo(c) , _conjJoin(nj, claves, campos) {};
    };

    struct datosTabla{
    	Tabla _tabla;
    	DiccStr<Join> _joins;

    	datosTabla(Tabla& t): _tabla(t){}; // NO HACE FALTA EL CONSTRUCCTOR. ESTA COPIANDO LA TABLA Y EL DICCJOIN

    };


    typedef Conj<nombreTabla>::const_Iterador itTablas; //el iterador itTablas lo definimos sobre el conj de nombres de tablas

    
};

#endif
