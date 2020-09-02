#include "../../../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

int main(){

	vector<int> tamanos;
	tamanos.push_back(5);
	tamanos.push_back(10);
	tamanos.push_back(30);
	
	string pls_out10 = "DataFilePLS10fold.out";
	string pls_out5  = "DataFilePLS5fold.out";
	string pca_out10 = "DataFilePCA10fold.out";
	string pca_out5  = "DataFilePCA5fold.out";

	string in;

	for (int k = 1; k <= 5; k += 2){
		for (int i = 0; i < tamanos.size(); ++i){

			in = "./PCA/PCAout5FoldsK"+ to_string(k) +"Size"+ to_string(tamanos[i]*1000);
			ObtenerData(pca_out5, in);

			in = "./PCA/PCAout10FoldsK"+ to_string(k) +"Size"+ to_string(tamanos[i]*1000);
			ObtenerData(pca_out10, in);

			in = "./PLS/PLSout5FoldsK"+ to_string(k) +"Size"+ to_string(tamanos[i]);
			ObtenerData(pls_out5, in);


			in = "./PLS/PLSout10FoldsK"+ to_string(k) +"Size"+ to_string(tamanos[i]);
			ObtenerData(pls_out10, in);

		}
	}
		
	return 0;
}
