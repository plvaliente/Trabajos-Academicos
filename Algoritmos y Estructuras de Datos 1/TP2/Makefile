
all: fatFood

clean:
	rm *.o
	rm fatFood

fatFood: fatFood.cpp interfaz.cpp local.o pedido.o combo.o
	g++ -o fatFood $^

%.o: %.cpp
	g++ -c $<
