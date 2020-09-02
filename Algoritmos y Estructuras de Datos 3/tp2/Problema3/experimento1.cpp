#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "problema3.h"

#define ya chrono::high_resolution_clock::now

using namespace std;

int main(){

	int testeos =  1;

  	int n = 6;
  	while(n <= 1000){

		

    	vector<int> t;

    	for(int i=0 ; i < testeos ; i++){

   //  		vector<arista> V;
   //  		for(int j = 0 ; j < n ; j++){
			// 	for(int k=j+1 ; k < n ; k++){
			// 		//cout << i << j << k << endl;
			// 		arista a;
			// 		a.c1 = j;
			// 		a.c2 = k;
			// 		bool e = rand() % 2;
			// 		int costo = rand() % 100 + 1;

			// 		// si la ruta ya existe, el costo es negativo
			// 		if( e ){
			// 			a.costo = -costo;
			// 		}
			// 		// si la ruta no existe, el costo es positivo
			// 		else{
			// 			a.costo = costo;
			// 		}
			// 		V.push_back(a);
			// 	}
			// }

			// vector<arista> solucion;
			
			// auto start = ya();
		 //    int gasto = problema3(V, n, solucion);
		 //    auto end = ya();

		 //    t.push_back(chrono::duration_cast<std::chrono::microseconds>(end-start).count());
		}

	    // int promt = 0;
	    // for (int j=0 ; j<testeos ; j++){
     //  		promt += t[j];
    	// }
    	// promt = promt / testeos;

		cout << n <<',';

	    if(n < 20){
	      n++;
	    }
	    else if(n < 50){
	      n = n + 2;
	    }
	    else if(n < 100){
	      n = n + 5;
	    }
	    else if(n < 500){
	      n = n + 10;
	    }
	    else{
	      n = n + 20;
	    }

	}
	cout << endl;
	return 0;
}
