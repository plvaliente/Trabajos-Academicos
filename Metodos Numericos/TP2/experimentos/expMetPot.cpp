#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <ratio>
#include <chrono>
  
using namespace std::chrono;  
using namespace std;


vector<double> cargarControl(string str, int cant){
	ifstream in;
	char *data = &str[0u];
  	in.open(data);
  	vector<double> control;
  	double lambda;
  	for(int i=0 ; i < cant ; i++){
  		in >> lambda;
  		control.push_back(lambda);
  	}
  	return control;	
}

void testMetPotA(Matriz& A, int cantAuto, int critParada, string inAValor, string out){
	ofstream myfile;
	char *outFile = &out[0u];
  	myfile.open (outFile);
  	//myfile << "Writing this to a file.\n";

	cout.precision(9);

	double errorRelativoAcumulado;
	double errorRelativo;
	vector<double> autoValoresControl = cargarControl(inAValor, 10);
	vector<double> initMP;
	Matriz mat; 
	for(int k=10; k <= critParada ; k = k+10){
		mat = A;
		errorRelativoAcumulado = 0;

		/*************SETEO TIME*************/
		high_resolution_clock::time_point tinit = high_resolution_clock::now();
		duration<double> time_acc = duration_cast<duration<double>>(tinit - tinit);
		/************************************/
		for(int j=0; j < cantAuto ; j++){
			/**************************************/
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			/**********CALCULO AUTOVECTOR**********/
			initMP = vectorAleatorio(mat.columnas(), j);
			double lambda = metodoPotencia(mat, initMP, k);
			/**************************************/
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
		    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		    time_acc += time_span;
			/**************************************/

			errorRelativo = lambda - autoValoresControl[j];
			errorRelativo = abs(errorRelativo / (double) autoValoresControl[j]);
			errorRelativoAcumulado += errorRelativo;
			
			/**********DEFLACION**********/
			Matriz iit(initMP, initMP);
			iit * lambda;						//iit = iit·lambda
			mat = mat - iit;
		}
		myfile << fixed << k << " " << errorRelativoAcumulado << " " << time_acc.count() << endl;
		time_acc = duration_cast<duration<double>>(tinit - tinit);
	}
	myfile.close();	
}

int main(){
	cout.precision(9);
	Matriz A(100,100);
	double value = 100;
	for(int i=1 ; i < 100 + 1 ; i++){	
		cout << fixed << value << endl;		
		A(i-1,i-1) = value;
		value = value * (double) 0.99;
	}
	string out = "filesMPot/expMetPot.data";
	string inAValor = "filesMPot/Avalor.in";
	testMetPotA(A, 10, 1000, inAValor, out);

	return 0;
}
