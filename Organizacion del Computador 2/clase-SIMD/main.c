#include <stdio.h>



extern float dist(float* v, float* w, unsigned short n);

extern float* normalizarVector(float* v, int n);

int main() {
	float v[8];
	for( int i = 0 ; i < 8 ; i++ ){
		v[i] = i;	
	}
	float w[8];
	for( int i = 0 ; i < 8 ; i++ ){
		w[i] = 8 - i;	
	}    
	float* result = normalizarVector(&v[0], 8);
     printf("the value of my_pointer is %p\n", result);
     for( int i = 0 ; i < 8 ; i++ ){
     	printf("the value of *my_pointer is %f\n", *(result + i));
     }
    return 0;
}
