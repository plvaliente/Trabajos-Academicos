CC = g++

CFLAGS  = -g -std=c++11 

all: GLF bestChoice BCMultiple

GLF: GLF.cpp
	$(CC) $(CFLAGS) -o GLF GLF.cpp 

bestChoice: bestChoice.cpp

	$(CC) $(CFLAGS) -o bestChoice bestChoice.cpp

BCMultiple: BCMultiple.cpp
	$(CC) $(CFLAGS) -o BCMultiple BCMultiple.cpp

clean:
	$(RM) GLF
	$(RM) bestChoice
	$(RM) BCMultiple
