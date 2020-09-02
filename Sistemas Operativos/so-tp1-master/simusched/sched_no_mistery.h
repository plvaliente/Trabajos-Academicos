#ifndef __SCHED_NO_MISTERY__
#define __SCHED_NO_MISTERY__

#include <vector>
#include <queue>
#include "basesched.h"

typedef std::pair<int,int> par;

class my_greater  {
public:
  bool operator() (const par& arg1, const par& arg2) const
  {
    return arg1.first > arg2.first;
    return false;
  }
};

class SchedNoMistery : public SchedBase {
	public:
		SchedNoMistery(std::vector<int> argn);
        ~SchedNoMistery();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::priority_queue<par, std::vector<par>, my_greater> q;
};


#endif
