#ifndef __SCHED_SPJF__
#define __SCHED_SPJF__

#include <vector>
#include <queue>
#include "basesched.h"

using namespace std;

#define CANT_PRIORIDADES 5

typedef struct tsk_info{
  tsk_info(int p, int d, int id): prio(p), dur(d), pid(id) {};

  int prio;
  int dur;
  int pid;
} tsk_info;

class cmp_SPJF  {
public:
  bool operator() (const tsk_info& arg1, const tsk_info& arg2) const
  {
    int prio1 = arg1.prio;
    int prio2 = arg2.prio;
    int dur1 = arg1.dur;
    int dur2 = arg2.dur;

    if (prio1 > prio2){
    	return true;
    } else if(prio1 == prio2 && dur1 >= dur2){
    	return true;
    }

    return false;
  }
};

typedef priority_queue<tsk_info, vector<tsk_info>, cmp_SPJF> cola_prio;

class SchedSPJF : public SchedBase {
	public:
		SchedSPJF(vector<int> argn);
        ~SchedSPJF();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		cola_prio* queues [CANT_PRIORIDADES];

		int next();
};


#endif
