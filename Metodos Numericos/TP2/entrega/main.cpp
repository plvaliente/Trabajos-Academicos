#include "Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
  
using namespace std;



int main(int argc, char* argv[]){

	string in = argv[1];
	const char * out = argv[2];
	string met = argv[3];
	ofstream writeFile;
    writeFile.open(out);

	dataIn datos = loader(in);
	
	for(int i=0 ; i < datos._Kfold ; i++){
		
		vector<double> pcaL = lambdasPCA(datos._train[i], datos._alpha, 700);
		for(int j=0 ; j < pcaL.size() ; j++){
			writeFile << pcaL[j] << endl;
		}

		vector<double> plsL = lambdasPLSda(datos._train[i], datos._gamma, 700);
		for(int k=0 ; k < plsL.size() ; k++){
			writeFile << plsL[k] << endl;
		}
	}
	writeFile.close();
	string outK = out + ".csv"; 
	char *fileK = &outK[0u];
	ofstream kaggle;
    kaggle.open(fileK);
	vector < imgInfo > bdd = cargarImagenes("../data/train.csv");
	vector < vector< double > > test = cargarTest("../data/test.csv");
	kaggle << "ImageId,Label" << endl;
	if(met == "0"){
		for(int i=0 ; i < test.size() ; i++ ){
			int prediccion = kNN(1, test[i], bdd);
			//prediccion = kNNVersion2(1, test[i], trainTransformada);
			kaggle << i+1 << "," << prediccion << endl;
		}
	}
	else if( met == "1"){
		Matriz tPCA = PCA(bdd, 50, 700);
		vector<imgInfo> trainTransformada = AplicarTransformacion(bdd, tPCA);
		for(int i=0 ; i < test.size() ; i++ ){
			vector<double> imagenTest = tPCA.porVector(test[i]);
			int prediccion = kNN(1, imagenTest, trainTransformada);
			//prediccion = kNNVersion2(1, test[i], trainTransformada);
			kaggle << i+1 << "," << prediccion << endl;
		}
	}
	else{
		Matriz tPLS = PLSda(bdd, 50, 700);
		vector<imgInfo> trainTransformada = AplicarTransformacion(bdd, tPLS);
		for(int i=0 ; i < test.size() ; i++ ){
			vector<double> imagenTest = tPLS.porVector(test[i]);
			int prediccion = kNN(1, imagenTest, trainTransformada);
			//prediccion = kNNVersion2(1, test[i], trainTransformada);
			kaggle << i+1 << "," << prediccion << endl;
		}
	}
	return 0;
}
