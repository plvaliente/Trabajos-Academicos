#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
  
using namespace std;

void testPCA(vector<imgInfo>& bdd, int seed, int alpha, int parada, int k){
	vector<double> imagenPrueba = bdd[seed]._fst;

	Matriz TCpca = PCA(bdd, alpha, parada);
	
	cout << "Etiqueta REAL: " << bdd[seed]._snd << endl;

	//Transformo la base de datos con la transformacion caracteristica
	for(int i = 1 ; i < bdd.size() ; i++){
		bdd[i]._fst = TCpca.porVector(bdd[i]._fst);
	}

	imagenPrueba = TCpca.porVector(imagenPrueba);
	
	vector<int> prueba = kNN(k, imagenPrueba, bdd);
	cout << "Resultados: ";
	coutVector(prueba);
}

void testPLS(vector<imgInfo>& bdd, int seed, int gamma, int parada, int k){

	vector<double> imagenPrueba = bdd[seed]._fst;

	Matriz TCpls = PLSda(bdd, gamma, parada);

	cout << "Etiqueta REAL: " << bdd[seed]._snd << endl;

	//Transformo la base de datos con la transformacion caracteristica
	for(int i = 1 ; i < bdd.size() ; i++){
		bdd[i]._fst = TCpls.porVector(bdd[i]._fst);
	}

	imagenPrueba = TCpls.porVector(imagenPrueba);

	vector<int> prueba = kNN(k, imagenPrueba, bdd );
	cout << "Resultados: ";
	coutVector(prueba);
}

int main(int argc, char* argv[]){

	string in = argv[1];
	//const char * out = argv[2];
	string met = argv[2];

	vector < imgInfo > bdd = cargarImagenes(in);
	
	if(met == "0"){
		testPCA(bdd, 6, 5, 50, 100);	
	}

	else if( met == "1"){
		testPLS(bdd, 6, 5, 50, 100);
	}
	

	return 0;
}