#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

SchedRR::SchedRR(std::vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	cores = argn[0];
	if(argn.size() - 1 != cores){
		std::cerr << "Error en los parametros" << std::endl;
	}

	for(int i = 1; i < argn.size(); i++){
		quantums.push_back(argn[i]);
		core_ticks.push_back(1);
	}

}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	proc_queue.push(pid);
}

void SchedRR::unblock(int pid) {
	//Borra el pid del vector de bloqueados y lo pone en la cola de procesos
	blocked.erase(remove(blocked.begin(), blocked.end(), pid), blocked.end());
	load(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	int actual = current_pid(cpu);
	if(m == EXIT){
		if(proc_queue.empty()){
			return IDLE_TASK;
		} else {
			return next(cpu);
		}
	} else if (m == BLOCK){
		blocked.push_back(actual);
		return next(cpu);
	} else {
		if( (core_ticks[cpu] == quantums[cpu]) || (actual == IDLE_TASK) ){
			//Alcanzo su quantum, lo cambio por otro proceso (o el mismo, si no hay mas en la cola)
			
			if(actual != IDLE_TASK){
				load(current_pid(cpu));
			}
			return next(cpu);
		} else {
			//Todavia no termino su quantum, debe continuar el mismo
			core_ticks[cpu]++;
			return current_pid(cpu);
		}
	}
}

//Private

int SchedRR::next(int cpu) {
	
	if(!proc_queue.empty()){
		int next = proc_queue.front();
		proc_queue.pop();
		core_ticks[cpu] = 1;
		return next;
	} else {
		return current_pid(cpu);
	}
}
