#include <stdio.h>
extern int suma(int, int);
int main(int argc, char *argv[]){
	int res = suma(2,7);
	printf("Suma: %d\n", res);
	return 0;
}