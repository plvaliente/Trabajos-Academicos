clean:
	rm problema2
	rm Test

main: main.cpp ejercicio2.cpp
	g++ -o problema2 $^

test: test.cpp ejercicio2.cpp
	g++ -std=c++11 -o  Test $^ 

%.o: %.cpp
	g++ -c $<

all: main test