#include "sched_no_mistery.h"
#include "iostream"

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
}

SchedNoMistery::~SchedNoMistery() {
}

void SchedNoMistery::load(int pid) {
    int size = (*tsk_params(pid))[0];
	q.push(par(size, pid));
}

void SchedNoMistery::unblock(int pid) {
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (q.empty()) return IDLE_TASK;
		else {
			int sig = q.top().second; q.pop();
			return sig;
		}
	} else {
		// Siempre sigue el pid actual mientras no termine.
		if (current_pid(cpu) == IDLE_TASK && !q.empty()) {
			int sig = q.top().second; q.pop();
			return sig;
		} else {
			return current_pid(cpu);
		}
	}
}
