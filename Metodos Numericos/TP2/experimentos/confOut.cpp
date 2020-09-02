#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

int main(){
	string inData = "filesPLS/out5FoldsK1gamma50";
	vector< vector<duplaInt> > data = diego(inData);
	Matriz conf = MatrizDeConfusionDeDigitos(data[0]);
	for(int i=1 ; i < 5 ; i++){
		Matriz mAdd = MatrizDeConfusionDeDigitos(data[i]);
		conf = conf + mAdd;
	}
	conf * 0.20;
	conf.generarConfusionPy();
}