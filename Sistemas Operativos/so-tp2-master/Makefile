.POSIX:
.SUFFIXES:
.SUFFIXES: .o .cpp

CXX = g++
#CXXFLAGS = -std=c++11 -fdiagnostics-color=always -g
CXXFLAGS = -std=c++11 -g
#Originalmente decia solo -lpthread
LDLIBS = -lpthread -pthread 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

BIN = test-2 test-3 test-5 test-5-concurrente testHashMap tiempos
OBJ = ConcurrentHashMap.o

all: $(BIN)

ConcurrentHashMap.o: ConcurrentHashMap.cpp ConcurrentHashMap.hpp ListaAtomica.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

test-2: $(OBJ) test-2.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ test-2.cpp $(OBJ) $(LDLIBS)

test-2-run: test-2
	awk -f corpus.awk corpus | sort >corpus-post
	./test-2 | sort | diff -u - corpus-post
	rm -f corpus-post

test-3: $(OBJ) test-3.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ test-3.cpp $(OBJ) $(LDLIBS)

test-3-run: test-3
	awk -f corpus.awk corpus | sort >corpus-post
	for i in 0 1 2 3 4; do sed -n "$$((i * 500 + 1)),$$(((i + 1) * 500))p" corpus >corpus-"$$i"; done
	for i in 0 1 2 3 4; do ./test-3 $$((i + 1)) | sort | diff -u - corpus-post; done
	rm -f corpus-post corpus-[0-4]

test-5: $(OBJ) test-5.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ test-5.cpp $(OBJ) $(LDLIBS)

test-5-run: test-5
	awk -f corpus.awk corpus | sort -nk 2 | tail -n 1 >corpus-max
	cat corpus-max
	for i in 0 1 2 3 4; do sed -n "$$((i * 500 + 1)),$$(((i + 1) * 500))p" corpus >corpus-"$$i"; done
	for i in 0 1 2 3 4; do for j in 0 1 2 3 4; do \
		./test-5 $$((i + 1)) $$((j + 1)) | diff -u - corpus-max; \
	done; done
	rm -f corpus-max corpus-[0-4]

test-5-concurrente: $(OBJ) test-5-concurrente.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ test-5-concurrente.cpp $(OBJ) $(LDLIBS)

test-5-concurrente-run: test-5-concurrente
	awk -f corpus.awk corpus | sort -nk 2 | tail -n 1 >corpus-max
	cat corpus-max
	for i in 0 1 2 3 4; do sed -n "$$((i * 500 + 1)),$$(((i + 1) * 500))p" corpus >corpus-"$$i"; done
	for i in 0 1 2 3 4; do for j in 0 1 2 3 4; do \
		./test-5-concurrente $$((i + 1)) $$((j + 1)) | diff -u - corpus-max; \
	done; done
	rm -f corpus-max corpus-[0-4]
	
testHashMap: $(OBJ) testHashMap.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ testHashMap.cpp $(OBJ) $(LDLIBS)

testHashMap-run: testHashMap
	./testHashMap

tiempos: $(OBJ) tiempos.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ tiempos.cpp $(OBJ) $(LDLIBS)

tiempos-run: tiempos
	./tiempos

clean:
	rm -f $(BIN) $(OBJ)
	rm -f corpus-*
