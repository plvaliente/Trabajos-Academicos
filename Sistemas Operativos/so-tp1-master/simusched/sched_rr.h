#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include "basesched.h"
#include <algorithm>

class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		//Cola global
		std::queue<int> proc_queue;
		//Contiene los procesos que estan bloqueados por uso_IO
		std::vector<int> blocked;
		//Cantidad de cores
		int cores;
		//Contiene los quantums de cada core
		std::vector<int> quantums;
		//Cantidad de ticks que lleva la tarea actual en cada core
		std::vector<int> core_ticks;

		//Retorna el proximo proceso de la cola global, lo remueve de la misma y resetea los ticks para cpu
		//Si no hay mas procesos en la cola, devuelve el actual para ese cpu
		virtual int next(int cpu);
};

#endif
