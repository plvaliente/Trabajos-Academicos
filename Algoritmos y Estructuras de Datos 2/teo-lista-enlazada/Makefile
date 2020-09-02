
CPP=g++
CPPFLAGS=-g -O0 -Wno-deprecated-declarations
ifeq ($(PRINTSTACK), 1)
	CPPFLAGS := $(CPPFLAGS) -DSTACKTRACE
endif
C03FLAGS=$(CPPFLAGS) --std=c++03
C11FLAGS=$(CPPFLAGS) --std=c++11

TESTNUMS03 := $(shell seq -s ' ' 1 7)
TESTS03 := $(addprefix test,${TESTNUMS03})
TESTSOBJ03 := $(addsuffix .o,${TESTS03})

TESTS11 := test8 test9
TESTSOBJ11 := $(addsuffix .o,${TESTS11})

TESTSEXTRA := test7-extra test4-extra test8-extra
TESTSOBJEXTRA := $(addsuffix .o,${TESTSEXTRA})


TESTS := $(TESTS03) $(TESTS11) $(TESTSEXTRA)


.PHONY: all clean

all: ${TESTS}

${TESTS}: test%: test%.o print.o
	$(CPP) $^ -o $@  #&&\
#	valgrind --leak-check=yes ./$@

${TESTSOBJ11}: test%.o: test.cpp lista-%.h
	$(CPP) -c $(C11FLAGS) -DTEST$* $< -o $@ 

${TESTSOBJ03}: test%.o: test.cpp lista-%.h
	$(CPP) -c $(C03FLAGS) -DTEST$* $< -o $@

#OPCIONES QUE NO COMPILAN, O QUE CONLLEVAN ERRORES DE PROGRAMACION
test3-extra: test.cpp
	$(CPP) -c $(C03FLAGS) -DTEST3 -DTEST_SIN_CONSTRUCTOR $^ -o $@ 

test4-extra.o: test.cpp lista-4.h
	$(CPP) -c $(C03FLAGS) -DTEST4 -DTEST_EFICIENCIA_DE_COPIAS $< -o $@ 

test5-full: test.cpp
	$(CPP) -c $(C03FLAGS) -DTEST5full $^ -o $@ 

test6-extra: test.cpp
	$(CPP) -c $(C03FLAGS) -DTEST6 -DTEST_CONSTNESS $^ -o $@ 

test7-extra.o: test.cpp lista-7.h
	$(CPP) -c $(C03FLAGS) -DTEST7 -DTEST_EFICIENCIA_MOVIMIENTO $< -o $@ 

test8-extra.o: test.cpp lista-7.h
	$(CPP) -c $(C11FLAGS) -DTEST8 -DTEST_RECORRIDO $< -o $@ 
	
print.o: print.cpp print.h
	$(CPP) -c $(CPPFLAGS) -std=c++14 $< -o $@

clean:
	$(RM) *.o $(TESTS) 
	
