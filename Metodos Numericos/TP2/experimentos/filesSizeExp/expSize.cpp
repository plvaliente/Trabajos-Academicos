#include "../../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ratio>
using namespace std;

dataIn s_loader(string str, int total){
	char *s = &str[0u];
	ifstream myReadFile;
    myReadFile.open(s);

	string ruta;				
	dataIn load;
	string decision;

	if (myReadFile.is_open()) {
    
    	myReadFile >> ruta;
    	myReadFile >> load._k;
    	myReadFile >> load._alpha;
    	myReadFile >> load._gamma;
    	myReadFile >> load._Kfold;

		vector < imgInfo > imagenes = cargarImagenes(ruta+"train.csv");
		
		for(int i=0; i < load._Kfold ; i++){
			vector<imgInfo> trainK;
			vector<imgInfo> testK;
			load._train.push_back(trainK);
			load._test.push_back(testK);
		}

		for(int i=0; i < load._Kfold ; i++){
			for(int j=0 ; j < total ; j++){
				myReadFile >> decision;

				if(decision == "0"){
					load._test[i].push_back(imagenes[j]);
				}
				else{
					load._train[i].push_back(imagenes[j]);
				}

			}
		}

	}
	cout << "loaded" << endl;
	return load;
}

void PLSKfold5(vector<int> tamanos){

	  
	for(int i=0; i < tamanos.size();i++){
	
		string ruta	= "./K5-S" + to_string(tamanos[i]) + ".in";
		dataIn datos = s_loader(ruta, tamanos[i]*1000);

		string k1Size = "PLSout5FoldsK1Size";
		string k3Size = "PLSout5FoldsK3Size";
		string k5Size = "PLSout5FoldsK5Size";

		vector< vector<duplaInt> > resultadoK1;
		vector< vector<duplaInt> > resultadoK3;
		vector< vector<duplaInt> > resultadoK5;


		for(int K=0; K < datos._Kfold; K++){

			Matriz tPLS = PLSda(datos._train[K], datos._gamma, 700);
			vector<imgInfo> trainTransformada = AplicarTransformacion(datos._train[K], tPLS);

			vector<duplaInt> foldiK1;
			vector<duplaInt> foldiK3;
			vector<duplaInt> foldiK5;
			for(int j=0; j < datos._test[K].size() ; j++){

				vector<double> imagenTest = tPLS.porVector(datos._test[K][j]._imagen);

				/************** KNN = 1 **************/

				int prediccionk1 = kNN(1, imagenTest, trainTransformada);

				duplaInt duplaK1;
				duplaK1._fst = datos._test[K][j]._etiqueta;
				duplaK1._snd = prediccionk1;
				foldiK1.push_back(duplaK1);

				/************** KNN = 3 **************/

				int prediccionk3 = kNN(3, imagenTest, trainTransformada);

				duplaInt duplaK3;
				duplaK3._fst = datos._test[K][j]._etiqueta;
				duplaK3._snd = prediccionk3;
				foldiK3.push_back(duplaK3);

				/************** KNN = 5 **************/

				int prediccionk5 = kNN(5, imagenTest, trainTransformada);

				duplaInt duplaK5;
				duplaK5._fst = datos._test[K][j]._etiqueta;
				duplaK5._snd = prediccionk5;
				foldiK5.push_back(duplaK5);
			}
			resultadoK1.push_back(foldiK1);
			resultadoK3.push_back(foldiK3);
			resultadoK5.push_back(foldiK5);
		}

		string stringK1 = k1Size + to_string(tamanos[i]);
		char *outK1 = &stringK1[0u];
		string stringK3 = k3Size + to_string(tamanos[i]);
		char *outK3 = &stringK3[0u];
		string stringK5 = k5Size + to_string(tamanos[i]);
		char *outK5 = &stringK5[0u];
		guardarResultados(datos, resultadoK1, outK1);
		guardarResultados(datos, resultadoK3, outK3);
		guardarResultados(datos, resultadoK5, outK5);		
	}
}

void PLSKfold10(vector<int> tamanos){

	for(int i=0; i < tamanos.size();i++){

		string ruta	= "./K10-S" + to_string(tamanos[i]) + ".in";
		dataIn datos = s_loader(ruta, tamanos[i]*1000);

		string k1Size = "PLSout10FoldsK1Size";
		string k3Size = "PLSout10FoldsK3Size";
		string k5Size = "PLSout10FoldsK5Size";

		vector< vector<duplaInt> > resultadoK1;
		vector< vector<duplaInt> > resultadoK3;
		vector< vector<duplaInt> > resultadoK5;


		for(int K=0; K < datos._Kfold; K++){

			Matriz tPLS = PLSda(datos._train[K], 10, 700);
			vector<imgInfo> trainTransformada = AplicarTransformacion(datos._train[K], tPLS);

			vector<duplaInt> foldiK1;
			vector<duplaInt> foldiK3;
			vector<duplaInt> foldiK5;
			for(int j=0; j < datos._test[K].size() ; j++){

				vector<double> imagenTest = tPLS.porVector(datos._test[K][j]._imagen);

				/************** KNN = 1 **************/

				int prediccionk1 = kNN(1, imagenTest, trainTransformada);

				duplaInt duplaK1;
				duplaK1._fst = datos._test[K][j]._etiqueta;
				duplaK1._snd = prediccionk1;
				foldiK1.push_back(duplaK1);

				/************** KNN = 3 **************/

				int prediccionk3 = kNN(3, imagenTest, trainTransformada);

				duplaInt duplaK3;
				duplaK3._fst = datos._test[K][j]._etiqueta;
				duplaK3._snd = prediccionk3;
				foldiK3.push_back(duplaK3);

				/************** KNN = 5 **************/

				int prediccionk5 = kNN(5, imagenTest, trainTransformada);

				duplaInt duplaK5;
				duplaK5._fst = datos._test[K][j]._etiqueta;
				duplaK5._snd = prediccionk5;
				foldiK5.push_back(duplaK5);
			}
			resultadoK1.push_back(foldiK1);
			resultadoK3.push_back(foldiK3);
			resultadoK5.push_back(foldiK5);
		}

		string stringK1 = k1Size + to_string(tamanos[i]);
		char *outK1 = &stringK1[0u];
		string stringK3 = k3Size + to_string(tamanos[i]);
		char *outK3 = &stringK3[0u];
		string stringK5 = k5Size + to_string(tamanos[i]);
		char *outK5 = &stringK5[0u];
		guardarResultados(datos, resultadoK1, outK1);
		guardarResultados(datos, resultadoK3, outK3);
		guardarResultados(datos, resultadoK5, outK5);		
	}

}


void expPCA(dataIn datos, int alpha, int size){
	
	string k1Size = "PCAout"+ to_string(datos._Kfold)+ "FoldsK1Size";
	string k3Size = "PCAout"+ to_string(datos._Kfold)+ "FoldsK3Size";
	string k5Size = "PCAout"+ to_string(datos._Kfold)+ "FoldsK5Size";

	int Kfolds = datos._Kfold;
	vector<Matriz> Mis;
	
	for(int K=0; K < Kfolds; K++){
		/**********GENERO X**********/ 
		vector<double> mu = datos._train[K][0]._imagen;
		int bddSize = datos._train[K].size();
		int imgSize = mu.size();
		for(int i = 1 ; i < bddSize ; i++){
			for(int j = 0 ; j < imgSize ; j++ ){
				mu[j] += datos._train[K][i]._imagen[j];
			}
		}
		for(int k = 0 ; k < imgSize ; k++){
			mu[k] = mu[k] /(double) bddSize;		// mu <- Promedio de las imagenes		
		}
		vector < vector < double > > x;							
		for(int i = 0; i < bddSize ; i++){
			vector<double> fila = datos._train[K][i]._imagen;
			for(int j = 0; j < imgSize ; j++){
				fila[j] = (fila[j] - mu[j]) /(double) sqrt(bddSize - 1);
			}
			x.push_back(fila);
		}
		Matriz X(x);

		/**********GENERO M**********/
		Matriz Xt = X.trasponer();
		Matriz Mi = Xt * X;							// M = X'·X

		Mis.push_back(Mi);
	}
	
	Matriz M;

	vector< vector<duplaInt> > resultadosA;
	vector< vector<duplaInt> > resultadosB;
	vector< vector<duplaInt> > resultadosC;

	//PARA CADA KFOLD
	for(int i = 0; i < Kfolds ; i++){	
		M = Mis[i];	

		vector<double> x0; 
		vector < vector < double > > mPCAj;	

		for(int l = 0; l < alpha ; l++){
			/**********CALCULO AUTOVECTOR**********/
			x0 = vectorAleatorio(784, l);
			double lambda = metodoPotencia(M, x0, 700);
			mPCAj.push_back(x0);
			
			/**********DEFLACION**********/
			if(l < alpha - 1){
				Matriz x0x0t(x0, x0);
				x0x0t * lambda;						//x0x0t = x0x0t·lambda
				M = M - x0x0t;
			}
		}


		Matriz TCpcaj = Matriz(mPCAj);
		

		vector<imgInfo> trainT = AplicarTransformacion(datos._train[i], TCpcaj);
		vector<imgInfo> testT = AplicarTransformacion(datos._test[i], TCpcaj);

		vector<duplaInt> Kfold1;
		vector<duplaInt> Kfold2;
		vector<duplaInt> Kfold3;

		for(int j=0; j < datos._test[i].size() ; j++){

			vector<double> imagenTest = testT[j]._imagen;
			int etiquetaTest = testT[j]._etiqueta;
			duplaInt realPredicho;
			realPredicho._fst = etiquetaTest;

			int prediccionk1 = kNN(1, imagenTest, trainT);
			realPredicho._snd = prediccionk1;
			Kfold1.push_back(realPredicho);

			int prediccionk3 = kNN(3, imagenTest, trainT);
			realPredicho._snd = prediccionk3;
			Kfold2.push_back(realPredicho);


			int prediccionk5 = kNN(5, imagenTest, trainT);
			realPredicho._snd = prediccionk5;
			Kfold3.push_back(realPredicho);

		}

		resultadosA.push_back(Kfold1);
		resultadosB.push_back(Kfold2);
		resultadosC.push_back(Kfold3);

		
	}

	string stringK1 = k1Size + to_string(size);
	char *outK1 = &stringK1[0u];
	string stringK3 = k3Size + to_string(size);
	char *outK3 = &stringK3[0u];
	string stringK5 = k5Size + to_string(size);
	char *outK5 = &stringK5[0u];
	guardarResultados(datos, resultadosA, outK1);
	guardarResultados(datos, resultadosB, outK3);
	guardarResultados(datos, resultadosC, outK5);

}

int main(){

	vector<int> tamanos;
	tamanos.push_back(5);
	tamanos.push_back(10);
	tamanos.push_back(30);

//	PLSKfold5(tamanos);
//	PLSKfold10(tamanos);

	for (int i = 0; i < 3; ++i)	{
		for (int fold = 5; fold <= 10; fold += 5)	{
		cout << "K: " << fold << "\tS: " << tamanos[i] << endl;
		string ruta = "./K"+ to_string(fold)+ "-S"+ to_string(tamanos[i])+".in";
		dataIn d = s_loader(ruta, tamanos[i]*1000); 
		expPCA(d, d._alpha, tamanos[i]*1000);
		}
	}

	return 0;
}