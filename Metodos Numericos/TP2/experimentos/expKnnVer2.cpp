#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <ratio>
#include <chrono>

// para compilar: g++ -O3 -std=c++11 -o exp expKNN.cpp

using namespace std::chrono;
using namespace std;

void expKNN(dataIn& datos, const char * out){
	high_resolution_clock::time_point tinit = high_resolution_clock::now();
	duration<double> time_acc = duration_cast<duration<double>>(tinit - tinit);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	vector< vector<duplaInt> > resultados;
	
	for(int i=0; i < datos._Kfold ; i++){

		vector<duplaInt> Kfoldi;

		cout << i+1 << "/" << datos._Kfold << endl;

		for(int j=0; j < datos._test[i].size() ; j++){

			vector<double> imagenTest = datos._test[i][j]._imagen;
			int etiquetaTest = datos._test[i][j]._etiqueta;

			int prediccion = kNNVersion2(datos._k, imagenTest, datos._train[i]);

			duplaInt realPredicho;
			realPredicho._fst = etiquetaTest;
			realPredicho._snd = prediccion;

			Kfoldi.push_back(realPredicho);

		}

		resultados.push_back(Kfoldi);
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    time_acc += time_span;

    guardarResultados(datos, resultados, out);
	
	cout << fixed;
	cout << "tiempo kNN. k=" << datos._k << " Kfold=" << datos._Kfold << " : " << time_acc.count() << std::endl;   
}

int main(int argc, char* argv[]){

	string in = argv[1];
	const char * out;

	dataIn datos = loader(in);

	out = "outKNNV2-k1";
	datos._k = 1;
	expKNN(datos, out);

	out = "outKNNV2-k3";
	datos._k = 3;
	expKNN(datos, out);

	out = "outKNNV2-k5";
	datos._k = 5;
	expKNN(datos, out);

	out = "outKNNV2-k7";
	datos._k = 7;
	expKNN(datos, out);

	out = "outKNNV2-k10";
	datos._k = 10;
	expKNN(datos, out);

	out = "outKNNV2-k15";
	datos._k = 15;
	expKNN(datos, out);

	out = "outKNNV2-k20";
	datos._k = 20;
	expKNN(datos, out);

	out = "outKNNV2-k30";
	datos._k = 30;
	expKNN(datos, out);

	out = "outKNNV2-k50";
	datos._k = 50;
	expKNN(datos, out);

		//vector< vector<duplaInt> > resultados = cargarResultados(in);


	return 0;
}