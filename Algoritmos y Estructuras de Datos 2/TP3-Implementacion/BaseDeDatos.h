/*
 * Author: grupo_14
 *
 * Base de Datos.
 * 
 */
 


#ifndef MODULOS_BASE_DE_DATOS_H_
#define MODULOS_BASE_DE_DATOS_H_



#include "aed2.h"
#include "Tabla.h"





namespace modulos {
    
    class BaseDeDatos {
        public:
            BaseDeDatos();                                                              //Constructor
            BaseDeDatos(const BaseDeDatos& otra);                                       //Constructor por copia
            ~BaseDeDatos();                                                             //Destructor 
            BaseDeDatos& operator =(const BaseDeDatos& otra);                           //Asignación
            void AgregarTabla( Tabla& t);                                          //Agrega una nueva tabla sin registros a la base de datos
            void InsertarEntrada(const Registro& r, const nombreTabla& t);                     //Inserta un nuevo registro en la tabla cuyo nombre es pasado por parámetro
            void Borrar(const Registro& r, nombreTabla t);                              //Borra todos los registros de la tabla, cuyos datos del campo del registro coincidan con el dato del mismo registro
            Conj<Registro>::const_Iterador GenerarVistaJoin(nombreTabla t1, nombreTabla t2, campo c);             //Genera un join entre las tablas cuyos nombres son pasados por parámetro
            void BorrarJoin(nombreTabla t1, nombreTabla t2);                            //Borra el join entre las tablas cuyos nombres son pasados por parámetro
            itTablas Tablas() const;                                                    //Devuelve un iterador de Tablas con siguiente
            Tabla& DameTabla(nombreTabla t) const;                                      //Devuelve la tabla de la base de datos cuyo nombre es pasado por parametro
            bool HayJoin(nombreTabla t1, nombreTabla t2) const;                         //Devuelve si hay join entre las dos tablas
            campo CampoJoin(nombreTabla t1, nombreTabla t2) const;                      //Devuelve el campo por el cual hay join en las tablas
            const Conj<Registro>& Registros(nombreTabla t) const;                       //Devuelve el conjunto de registros de la tabla
            Conj<Registro>::const_Iterador VistaJoin(nombreTabla t1, nombreTabla t2);            //Actualiza y devuelve el join entre las dos tablas
            Nat CantidadDeAccesos(nombreTabla t) const;                                 //Devuelve la cantidad de accesos de la tabla
            nombreTabla TablaMaxima() const;                                            //Devuelve el nombre de la tabla máxima de la base de datos
            nombreTabla EncontrarMaximo(nombreTabla t, Conj<nombreTabla>& ct) const;    //Devuelve el nombre de la tabla máxima de entre una tabla y conjunto de tablas
            const Conj<Registro> Buscar(const Registro& r, nombreTabla t) const;        //Devuelve un conjunto con los registros de la tabla que coincidan en campo y dato para cada campo del registro.
            Conj<nombreTabla> TablasxNombre() const;

        private:
            Conj<nombreTabla> _nombresTablas;
            DiccStr<datosTabla> _tablas;
            nombreTabla _tablaMaxima;
            void ActualizarJoin(bool inserta, const Registro& r, const nombreTabla t);
            void AuxActContenedor(ContenedorReg& cont, Registro& r,const Modificacion& m, campo c, bool esnat);
            void AuxBorrarDelJoin(Lista< TuplaConjRegistros >& its, campo c, Dato dat, bool esnat);
    };
   
};

#endif 