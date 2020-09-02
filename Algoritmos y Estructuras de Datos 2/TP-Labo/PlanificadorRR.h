#ifndef PLANIFICADOR_RR_H_
#define PLANIFICADOR_RR_H_

#include <iostream>
#include <cassert>
using namespace std;

/**
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class PlanificadorRR {

  public:

	PlanificadorRR();
	PlanificadorRR(const PlanificadorRR<T>&);
	~PlanificadorRR();
	void agregarProceso(const T&);
	void eliminarProceso(const T&);
	const T& procesoEjecutado() const;
	void ejecutarSiguienteProceso();
	void pausarProceso(const T&);
	void reanudarProceso(const T&);
	void detener();
	void reanudar();
	bool detenido() const;
	bool esPlanificado(const T&) const;
	bool estaActivo(const T&) const;
	bool hayProcesos() const;
	bool hayProcesosActivos() const;
	int cantidadDeProcesos() const;
	int cantidadDeProcesosActivos() const;
	bool operator==(const PlanificadorRR<T>&) const;
	ostream& mostrarPlanificadorRR(ostream&) const;

  private:
  
	/**
	 * No se puede modificar esta funcion.
	 */
	
	PlanificadorRR<T>& operator=(const PlanificadorRR<T>& otra) {
		assert(false);
		return *this;
	}
	/**
	* Auxiliares
	**/

	/**
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		bool activo;
		T proc;
		Nodo* sig;
		Nodo* ant;
	
		Nodo(const T& t) : proc(t), activo(true), sig(NULL), ant(NULL) { //invoca al constructor por copia	
        }
	};
	Nodo* primeroActivo();
	
	Nodo* _actual;
	int _len;
	int _lenAct;
	bool _stop;
};

template<class T>
ostream& operator<<(ostream& out, const PlanificadorRR<T>& a) {
	return a.mostrarPlanificadorRR(out);
}

/**
 * Crea un nuevo planificador de tipo Round Robin.
 */	
template<typename T>
PlanificadorRR<T>::PlanificadorRR(){
	_actual = NULL;
	_len = 0;
	_lenAct = 0;
	_stop = false; 
}

/**
 * Una vez copiado, ambos planificadores deben ser independientes, 
 * es decir, por ejemplo, que cuando se borra un proceso en uno
 * no debe borrarse en el otro.
 */	
template<typename T>
PlanificadorRR<T>::PlanificadorRR(const PlanificadorRR<T>& otroP){
	int i = 0;
	_actual = NULL;
	_len = 0;
	_lenAct = 0;
	_stop = false; 
	Nodo* apuntador = otroP._actual;
	while(i < otroP.cantidadDeProcesos()){
		agregarProceso(apuntador->proc);
		_actual->ant->activo = apuntador->activo;
		apuntador = apuntador->sig;
		i++;	
	}
	_lenAct = otroP._lenAct;
	_stop = otroP._stop;
}

/**
 * DESTRUCTOR, Acordarse de liberar toda la memoria!
 */
template<typename T>	
PlanificadorRR<T>::~PlanificadorRR(){
	while(_actual != NULL){
		eliminarProceso(_actual->proc);
	}
}

/**
 * Agrega un proceso al planificador. El mismo debe ubicarse,
 * dentro del orden de ejecución, inmediatamente antes del que está
 * siendo ejecutado actualmente. Si no hubiese ningún proceso en ejecución,
 * la posición es arbitraria y el proceso pasa a ser ejecutado automáticamente.
 * PRE: El proceso no está siendo planificado por el planificador.
 */
template<typename T>
void PlanificadorRR<T>::agregarProceso(const T& t){
	assert(("Ya esta Planificado", not esPlanificado(t) ));
	Nodo* newProc = new Nodo(t);
	if(cantidadDeProcesos() == 0){
		newProc->sig = newProc;
		newProc->ant = newProc; 
		_actual = newProc;
	}
	else{
		Nodo* punt = _actual->ant;
		newProc->ant = _actual->ant;
		newProc->sig = _actual;
		punt->sig = newProc;
		_actual->ant = newProc;
	}
	if(cantidadDeProcesosActivos() == 0){
		_actual = newProc;
	}
	_len++;
	_lenAct++;
}

/**
 * Elimina un proceso del planificador. Si el proceso eliminado
 * está actualmente en ejecución, automáticamente pasa a ejecutarse
 * el siguiente (si es que existe).
 * PRE: El proceso está siendo planificado por el planificador.
 */
template<typename T>
void PlanificadorRR<T>::eliminarProceso(const T& t){
	assert(("No esta Planificado", esPlanificado(t) ));
	Nodo* apuntador = _actual;
	while (not (apuntador->proc == t)){
		apuntador = apuntador->sig;				// Busco el Elemento a ELIMINAR
	}											
	Nodo* puntAprev = apuntador->ant;
	apuntador->sig->ant = puntAprev;			// Arreglo Punteros
	puntAprev->sig = apuntador->sig;			

	_lenAct -= (apuntador->activo ? 1 : 0);		
	_len--;										// Actualizo #P y #PA
	if(apuntador == _actual){
		_actual = apuntador->sig;				// Si estoy eliminando el primer elemento, actualizo 
	}											// _actual al segundo elemento
	delete apuntador;							// LIBERO MEMORIA
	if(cantidadDeProcesos() == 0){				// Si esta VACIA => apunto _actual a NULL
		_actual = NULL;
	}
	else{										// CASO #P > 0
		if(_actual->activo != true && hayProcesosActivos()){	// Si _actual no estuviera Activo y #PA > 0
			_actual = primeroActivo();							// => apunto _actual al Primer Activo
		}	// Aca considero que pueden quedar todos los 		
	}		// procesos PAUSADOS y el planificador en estado ACTIVO
}

/**
 * Devuelve el proceso que está actualmente en ejecución.
 * PRE: Hay al menos un proceso activo en el planificador.
 */
template<typename T>
const T& PlanificadorRR<T>::procesoEjecutado() const{
	assert(("No hay Procesos Activos", hayProcesosActivos() ));
	return _actual->proc;
}

/**
 * Procede a ejecutar el siguiente proceso activo,
 * respetando el orden de planificación.
 * PRE: Hay al menos un proceso activo en el planificador.
 */
template<typename T>
void PlanificadorRR<T>::ejecutarSiguienteProceso(){
	assert(("No hay Procesos Activos", hayProcesosActivos() ));
	Nodo* apuntador = _actual;
	_actual->activo = false;
	_lenAct--;
	if(hayProcesosActivos()){
		_actual = primeroActivo();
		apuntador->activo = true;
	}
	else{
		_actual->activo = true;
	}
	_lenAct++;
}

/**
 * Pausa un proceso por tiempo indefinido. Este proceso pasa
 * a estar inactivo y no debe ser ejecutado por el planificador.
 * Si el proceso pausado está actualmente en ejecución, automáticamente
 * pasa a ejecutarse el siguiente (si es que existe).
 * PRE: El proceso está siendo planificado por el planificador.
 * PRE: El proceso está activo.
 */
template<typename T>
void PlanificadorRR<T>::pausarProceso(const T& t){
	assert(("No esta Planificado o Ya esta Pausado", esPlanificado(t) && estaActivo(t) ));
	Nodo* apuntador = _actual;
	while(not (apuntador->proc == t)){
		apuntador = apuntador->sig;
	}
	_lenAct--;
	apuntador->activo = false;
	if(hayProcesosActivos()){
		_actual = primeroActivo();
	}
}

/**
 * Reanuda un proceso previamente pausado. Este proceso pasa a estar
 * nuevamente activo dentro del planificador. Si no había ningún proceso
 * en ejecución, el proceso pasa a ser ejecutado automáticamente.
 * PRE: El proceso está siendo planificado por el planificador.
 * PRE: El proceso está inactivo.
 */
template<typename T>
void PlanificadorRR<T>::reanudarProceso(const T& t){
	assert(("No esta Planificado o Ya esta Activo", esPlanificado(t) && not estaActivo(t) ));
	Nodo* apuntador = _actual;
	while(not (apuntador->proc == t)){
		apuntador = apuntador->sig;
	}
	if(not hayProcesosActivos()){
		_actual = apuntador;
	}
	_lenAct++;
	apuntador->activo = true;
}

/**
 * Detiene la ejecución de todos los procesos en el planificador
 * para atender una interrupción del sistema.
 * PRE: El planificador no está detenido.
 */
template<typename T>
void PlanificadorRR<T>::detener(){
	assert(("Ya esta Detenido", not detenido() ));
	_stop = true;	
}

/**
 * Reanuda la ejecución de los procesos (activos) en el planificador
 * luego de atender una interrupción del sistema.
 * PRE: El planificador está detenido.
 */
template<typename T>
void PlanificadorRR<T>::reanudar(){
	assert(("No esta Detenido", detenido() ));
	_stop = false;		
}

/**
 * Informa si el planificador está detenido por el sistema operativo.
 */
template<typename T>
bool PlanificadorRR<T>::detenido() const{
	return _stop;
}


/**
 * Informa si un cierto proceso está siendo planificado por el planificador.
 */
template<typename T>
bool PlanificadorRR<T>::esPlanificado(const T& t) const{
	int i = 0;
	bool value = false; 
	Nodo* apuntador = _actual;
	while (i < cantidadDeProcesos() && value != true){
		if(apuntador->proc == t){
			value = true;
		}
		apuntador = apuntador->sig;
		i++;
	}
	return value;
}

/**
 * Informa si un cierto proceso está activo en el planificador.
 * PRE: El proceso está siendo planificado por el planificador.
 */
template<typename T>
bool PlanificadorRR<T>::estaActivo(const T& t) const{
	assert(("No esta Planificado", esPlanificado(t) ));
	Nodo* apuntador = _actual;
	while(not (apuntador->proc == t)){
		apuntador = apuntador->sig;
	}
	return apuntador->activo;
}

/**
 * Informa si existen procesos planificados.
 */
template<typename T>
bool PlanificadorRR<T>::hayProcesos() const{
	return (cantidadDeProcesos() > 0);
}	

/**
 * Informa si existen procesos activos.
 */
template<typename T>
bool PlanificadorRR<T>::hayProcesosActivos() const{
	return (cantidadDeProcesosActivos() > 0);
}
/**
 * Devuelve la cantidad de procesos planificados.
 */
template<typename T>
int PlanificadorRR<T>::cantidadDeProcesos() const{
	return _len;
}

/**
 * Devuelve la cantidad de procesos planificados y activos.
 */
template<typename T>
int PlanificadorRR<T>::cantidadDeProcesosActivos() const{
	return _lenAct;
}
/**
 * Devuelve true si ambos planificadores son iguales.
 */
template<typename T>
bool PlanificadorRR<T>::operator==(const PlanificadorRR<T>& otroP) const{
	bool value = true;
	if(cantidadDeProcesos() != otroP.cantidadDeProcesos() || cantidadDeProcesosActivos() != otroP.cantidadDeProcesosActivos() || detenido() != otroP.detenido()){
		value = false;
	}	
	else{
		int i = 0;
		Nodo* apuntador1 = _actual;
		Nodo* apuntador2 = otroP._actual;
		while(i < cantidadDeProcesos() && value != false){
			if(not (apuntador1->proc == apuntador2->proc) || apuntador1->activo != apuntador2->activo){
				value = false;
			}
			apuntador1 = apuntador1->sig;
			apuntador2 = apuntador2->sig;
			i++;
		}
	} 
	return value;
}

/**
 * Debe mostrar los procesos planificados por el ostream
 * PlanificadorRR vacio: []
 * PlanificadorRR con 1 elemento activo: [p0*]
 * PlanificadorRR con 2 elementos inactivos: [p0 (i), p1 (i)]
 * PlanificadorRR con 3 elementos (p0 inactivo, p2 siendo ejecutado: [p2*, p0 (i), p1]
 */
template<typename T>
ostream& PlanificadorRR<T>::mostrarPlanificadorRR(ostream& out) const{
	int i = 0;
	Nodo* apuntador = _actual;
	out << "[";
	if(hayProcesosActivos()){
		out << apuntador->proc << '*';
		apuntador = apuntador->sig;
		if(apuntador != _actual){
			out << ", ";		
		}
		i = 1;
	}
	while(i < cantidadDeProcesos()){		
		out << apuntador->proc;
		if(not apuntador->activo){
			out << " (i)";
		}
		apuntador = apuntador->sig;
		i++;
		if(apuntador != _actual){
			out << ", ";		
		}
	}
	out << "]";	
	return out;
}	
/**
* Auxiliares
**/
template<typename T>
typename PlanificadorRR<T>::Nodo* PlanificadorRR<T>::primeroActivo(){
	Nodo* apuntador = _actual;
	while(not apuntador->activo){
		apuntador = apuntador->sig;
	}
	return apuntador;
}
#endif // PLANIFICADOR_RR_H_