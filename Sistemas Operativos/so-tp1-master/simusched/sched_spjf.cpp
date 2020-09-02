#include "sched_spjf.h"
#include <iostream>

SchedSPJF::SchedSPJF(vector<int> argn) {
	for(int i = 0; i < CANT_PRIORIDADES; i++){
		cola_prio* p_nueva_cola = new cola_prio;
		queues[i] = p_nueva_cola;
	}
}

SchedSPJF::~SchedSPJF() {
	for(int i = 0; i < CANT_PRIORIDADES; i++){
		delete queues[i];
	}
}

void SchedSPJF::load(int pid) {
    int prio = (*tsk_params(pid))[0];
    int dur = (*tsk_params(pid))[1];
	queues[prio - 1]->push(tsk_info(prio, dur, pid));
}

void SchedSPJF::unblock(int pid) {
}

int SchedSPJF::tick(int cpu, const enum Motivo m) {
	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		return next();
	} else {
		//Vuelvo a cargar el pid en la cola correspondiente.
		int actual = current_pid(cpu);
		if(actual != IDLE_TASK){
			load(actual);
		}
		return next();
	}
}

int SchedSPJF::next(){
	for(int i = 0; i < CANT_PRIORIDADES; i++){
		//Busco alguna cola no vacia, empezando por la 0 (prioridad 1).
		if( !(queues[i]->empty()) ){
			int sig = (queues[i]->top()).pid; queues[i]->pop();
			return sig;
		} 
	}
	//Si estan todas vacias
	return IDLE_TASK;
}