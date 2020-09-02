#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cuatrotree.h"

void printAdd(FILE *pFile, ctTree* myCT, uint32_t i) {
    ct_add(myCT, i);
    fprintf(pFile,"%i - %i\n", i, myCT->size);
}

void testAdd(){
    ctTree* arbolPtr;
    ct_new(&arbolPtr);
    printf("%s \n", "arbol generado");
 	printf("%s \n", "empiezo a agregar");
 	ct_add(arbolPtr, 10);
 	printf("%s \n", "agrego 10");
 	ct_add(arbolPtr, 50);
 	printf("%s \n", "agrego 50");
 	ct_add(arbolPtr, 30);
 	printf("%s \n", "agrego 30");
 	ct_add(arbolPtr, 5);
 	
 	printf("%s \n", "agrego 5");
 	ct_add(arbolPtr, 20);
 	printf("%s \n", "agrego 20");
 	ct_add(arbolPtr, 40);
 	printf("%s \n", "agrego 40");
 	ct_add(arbolPtr, 60);
 	printf("%s \n", "agrego 60");
 	ct_add(arbolPtr, 19);
 	printf("%s \n", "agrego 19");
 	ct_add(arbolPtr, 39);
 	printf("%s \n", "agrego 39");
 	ct_add(arbolPtr, 4);
 	printf("%s \n", "agrego 4");
 	ctIter* iterPtr = ctIter_new(arbolPtr);
	printf("%s \n", "Iterador generado");   
	ctIter_first(iterPtr);
	printf("%s \n", "Itero");
	char* name = "prueba.txt";
    FILE *pFile = fopen( name, "a" );
	ct_print(arbolPtr, pFile);
	
	while(ctIter_valid(iterPtr) == 1){
			printf("%d \n", ctIter_get(iterPtr));
			ctIter_next(iterPtr);
	}
	ctIter_delete(iterPtr);
	ct_delete(&arbolPtr); 
}
void testDebugRandom1(){
	srand(70);
	ctTree* myCT;
    ct_new(&myCT);
    char* name = "dbg.txt";
    FILE *pFile = fopen( name, "a" );
    for(int i=0;i<100;i++)
      printAdd(pFile, myCT, rand()%100);
    ct_print(myCT,pFile);
    //printIterador(pFile,myCT);
    ct_delete(&myCT);
}

int main (void){
	/*
	char* name = "testAdd.txt";
	fprintf(pFile,"-\n");
    fclose( pFile );
    FILE *pFile = fopen( name, "a" );
	*/
	//testAdd();
	testDebugRandom1();
    return 0;    
}