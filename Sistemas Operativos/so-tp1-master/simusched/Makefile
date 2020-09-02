export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_fcfs.o sched_rr.o sched_no_mistery.o sched_spjf.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN) ejercicios

$(MAIN): $(OBJS) sched_mistery.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h sched_rr.h sched_no_mistery.h sched_spjf.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h


ejercicios: ejercicio1 ejercicio2 ejercicio3 ejercicio5 ejercicio6 ejercicio7

ejercicio1:
	+$(MAKE) -C ej1

ejercicio2:
	+$(MAKE) -C ej2

ejercicio3:
	+$(MAKE) -C ej3

ejercicio5:
	+$(MAKE) -C ej5

ejercicio6:
	+$(MAKE) -C ej6

ejercicio7:
	+$(MAKE) -C ej7

clean: cleanejercicios
	-rm $(OBJS) $(MAIN)
	-rm *.pyc

cleanejercicios:
	+$(MAKE) -C ej1 clean
	+$(MAKE) -C ej2 clean
	+$(MAKE) -C ej3 clean
	+$(MAKE) -C ej5 clean
	+$(MAKE) -C ej6 clean
	+$(MAKE) -C ej7 clean

new: clean all
