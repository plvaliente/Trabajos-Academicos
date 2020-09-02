#include <stdio.h>
extern double sumD(double, double);
int main(int argc, char *argv[]){
	double res = sumD(1.1,1.1);
	printf("Suma: %lf\n", res);
	return 0;
}