#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
using namespace std;

// para compilar: g++ -O3 -std=c++11 -o expTP expTiemposPotencia.cpp

Matriz expTP(vector<imgInfo>& bdd, int alpha){
	/**********GENERO X**********/

	high_resolution_clock::time_point crearMinit = high_resolution_clock::now();

	vector<double> mu = bdd[0]._imagen;
	int bddSize = bdd.size();
	int imgSize = mu.size();
	for(int i = 1 ; i < bddSize ; i++){
		for(int j = 0 ; j < imgSize ; j++ ){
			mu[j] += bdd[i]._imagen[j];
		}
	}
	for(int k = 0 ; k < imgSize ; k++){
		mu[k] = mu[k] /(double) bddSize;		// mu <- Promedio de las imagenes		
	}
	vector < vector < double > > x;							
	for(int i = 0; i < bddSize ; i++){
		vector<double> fila = bdd[i]._imagen;
		for(int j = 0; j < imgSize ; j++){
			fila[j] = (fila[j] - mu[j]) /(double) sqrt(bddSize - 1);
		}
		x.push_back(fila);
	}
	Matriz X(x);

	/**********GENERO M**********/
	Matriz Xt = X.trasponer();
	Matriz M0 = Xt * X;							// M = X'·X

	high_resolution_clock::time_point crearM1 = high_resolution_clock::now();
    duration<double> time_M = duration_cast<duration<double>>(crearM1 - crearMinit);
	cout << "M creada en: " << time_M.count() << endl;


	/**********INICIALIZO ALGUNAS VARIABLES**********/
	vector < vector < double > > mPCA;	
	vector<double> x0; 

	vector<int> criterios;
	criterios.push_back(200);
	criterios.push_back(300);
	criterios.push_back(400);
	criterios.push_back(500);
	criterios.push_back(700);
	criterios.push_back(1000);
	criterios.push_back(2000);

	for(int c = 0; c < criterios.size(); c++){

		Matriz M = M0;
		int critParada = criterios[c];

		high_resolution_clock::time_point tinit = high_resolution_clock::now();
		
		for(int i = 0; i < alpha ; i++){
			/**********CALCULO AUTOVECTOR**********/
			x0 = vectorAleatorio(784, i);
			double lambda = metodoPotencia(M, x0, critParada);
			//cout << fixed;
			//cout << scientific << lambda << endl;
			mPCA.push_back(x0);
			
			/**********DEFLACION**********/
			Matriz x0x0t(x0, x0);
			x0x0t * lambda;						//x0x0t = x0x0t·lambda
			M = M - x0x0t;
		}

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
	    duration<double> time_pot = duration_cast<duration<double>>(t1 - tinit);

	    cout << fixed;
		cout << "Tiempo potencia+deflacion en PCA, criterio " << criterios[c] << ": " << time_pot.count() << std::endl; 
	
	}
	

	/**********MATRIZ DE LA TRANSFOMACION**********/
	Matriz TCpca = Matriz(mPCA);

	return	TCpca;
}


int main(int argc, char* argv[]){

	string in = argv[1];

	dataIn datos = loader(in);

	expTP(datos._train[0], datos._alpha);
	
	return 0;
}