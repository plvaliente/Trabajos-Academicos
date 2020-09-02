#include "tasks.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

//Ej 1
void TaskConsola(int pid, vector<int> params) {
	int n = params[0];
	int bmin = params[1];
	int bmax = params[2];

	for (int i = 0; i < n; i++) {
		int r = rand();
		uso_IO(pid, bmin + (r % (bmax - bmin + 1)));
	}
}

//Ej 3
void TaskPajarillo(int pid, vector<int> params){
	int rep = params[0];
	int t_cpu = params[1];
	int t_io = params[2];

	for(int i = 0; i < rep; i++){
		uso_CPU(pid, t_cpu);
		uso_IO(pid, t_io);
	}
}

void TaskPriorizada(int pid, vector<int> params){
	int prio = params[0];
	if(prio < 1 || prio > 5){
		cout << "La prioridad debe ser un numero entre 1 y 5 incluidos" << endl;
	}

	int t_cpu = params[1];

	uso_CPU(pid, t_cpu);
}


void tasks_init(void) {

	// Le fijo una seed al rand para que siempre tenga el mismo resultado
	srand(4);

	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskPajarillo, 3);
	register_task(TaskPriorizada, 2);
}
