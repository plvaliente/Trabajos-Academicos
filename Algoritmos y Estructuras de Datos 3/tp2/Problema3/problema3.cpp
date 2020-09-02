#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "problema3.h"

using namespace std;

int main(){

	int instancias = 0;
	int n;

	cin >> n;

	while(n != -1){
		vector<arista> V;

		for(int i = 0 ; i < n*(n-1)/2 ; i++){
			arista a;
			cin >> a.c1 >> a.c2;
			bool e;
			int costo;
			cin >> e >> costo;

			// si la ruta ya existe, el costo es negativo
			if( e ){
				a.costo = -costo;
			}
			// si la ruta no existe, el costo es positivo
			else{
				a.costo = costo;
			}
			V.push_back(a);
		}

		vector<arista> solucion;

		coutAristas(V);

		int gasto = problema3(V, n, solucion);

		coutAristas(solucion);

		cout << n << ' ' << gasto << ' ';
		for(int j=0 ; j < solucion.size() ; j++){
			cout << solucion[j].c1 << ' ' << solucion[j].c2 << ' ' ;
		}
		cout << endl;

		cin >> n;
		instancias++;
	}

	return 0;
}
