clean:
	rm problema1
	rm expC

main: problema1.cpp
	g++ -o problema1 $^

testCompleto: expCOMPLETOS.cpp
	g++ -std=c++11 -o  expC $^

testNxK: expIgualNxK.cpp
	g++ -std=c++11 -o  expNxK $^

%.o: %.cpp
	g++ -c $<

all: main testCompleto testNxK