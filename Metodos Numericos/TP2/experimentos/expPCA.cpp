#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
using namespace std;

// para compilar: g++ -O3 -std=c++11 -o expPCA expPCA.cpp


void expPCA5(dataIn& datos, vector<int>& alphas, int critParada, vector<int> ks){
	
	int Kfolds = datos._Kfold;
	vector<Matriz> Mis;
	high_resolution_clock::time_point crearM0 = high_resolution_clock::now();

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

		cout << "M" << K + 1 << " creada" << endl;
	}
	
	high_resolution_clock::time_point crearM1 = high_resolution_clock::now();
    duration<double> time_M = duration_cast<duration<double>>(crearM1 - crearM0);

    cout << fixed;
	cout << Kfolds << " matrices M creadas: " << time_M.count() << endl;

	
	// PARA CADA VALOR DE k 
	for(int b = 0; b < ks.size(); b++){

		int k = ks[b];

		// PARA CADA VALOR DE ALPHA
		for(int a = 0; a < alphas.size() ; a++){   				
					
			int alpha = alphas[a];
			Matriz M;

			vector< vector<duplaInt> > resultadosA;

			high_resolution_clock::time_point tAlpha0 = high_resolution_clock::now();

			//PARA CADA KFOLD
			for(int i = 0; i < Kfolds ; i++){	
				M = Mis[i];	

				vector<double> x0; 
				vector < vector < double > > mPCAj;	

				high_resolution_clock::time_point tKfoldi = high_resolution_clock::now();


				for(int l = 0; l < alpha ; l++){
					/**********CALCULO AUTOVECTOR**********/
					x0 = vectorAleatorio(784, l);
					double lambda = metodoPotencia(M, x0, critParada);
					mPCAj.push_back(x0);
					
					/**********DEFLACION**********/
					if(l < alpha - 1){
						Matriz x0x0t(x0, x0);
						x0x0t * lambda;						//x0x0t = x0x0t·lambda
						M = M - x0x0t;
					}
				}


				Matriz TCpcaj = Matriz(mPCAj);
				
				high_resolution_clock::time_point tTC = high_resolution_clock::now();
				duration<double> time_TC = duration_cast<duration<double>>(tTC - tKfoldi);

				cout << "alpha=" << alpha << ", Kfold " << i + 1 << ": " << time_TC.count() << "(Cálculo TC)" << endl; 
				
				vector<imgInfo> trainT = AplicarTransformacion(datos._train[i], TCpcaj);
				vector<imgInfo> testT = AplicarTransformacion(datos._test[i], TCpcaj);

				high_resolution_clock::time_point tTrans = high_resolution_clock::now();
				duration<double> time_Trans = duration_cast<duration<double>>(tTrans - tTC);

				cout << "alpha=" << alpha << ", Kfold " << i + 1 << ": " << time_Trans.count() << "(Transformación de train y test)" << endl;
				

				vector<duplaInt> Kfoldi;

				for(int j=0; j < datos._test[i].size() ; j++){

					vector<double> imagenTest = testT[j]._imagen;
					int etiquetaTest = testT[j]._etiqueta;

					int prediccion = kNN(k, imagenTest, trainT);

					duplaInt realPredicho;
					realPredicho._fst = etiquetaTest;
					realPredicho._snd = prediccion;

					Kfoldi.push_back(realPredicho);
				}

				resultadosA.push_back(Kfoldi);

				high_resolution_clock::time_point tKNN = high_resolution_clock::now();
				duration<double> time_KNN = duration_cast<duration<double>>(tKNN - tTrans);

				cout << "alpha=" << alpha << ", Kfold " << i + 1 << ": " << time_KNN.count() << "(KNN) k=" << k << endl;

			}

			string alphastr = std::to_string(alpha);
			string kstr = std::to_string(k);
			string outt = "ExpPCA-Kfold5-k" + kstr + "-alpha" + alphastr + ".out";
			const char * out = outt.c_str();

			guardarResultados(datos, resultadosA, out);

			high_resolution_clock::time_point tAlpha1 = high_resolution_clock::now();
		    duration<double> time_alphai = duration_cast<duration<double>>(tAlpha1 - tAlpha0);

		    
			cout << "Tiempo PCA total (sin cálculo de M) alpha=" << alpha << ": " << time_alphai.count() << endl; 

		}
	}

}


void expPCA10(dataIn& datos, vector<int>& alphas, int critParada, vector<int> ks){
	
	int Kfolds = datos._Kfold;
	vector<Matriz> Mis;
	high_resolution_clock::time_point crearM0 = high_resolution_clock::now();

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

		cout << "M" << K + 1 << " creada" << endl;
	}
	
	high_resolution_clock::time_point crearM1 = high_resolution_clock::now();
    duration<double> time_M = duration_cast<duration<double>>(crearM1 - crearM0);

    cout << fixed;
	cout << Kfolds << " matrices M creadas: " << time_M.count() << endl;

	
	// PARA CADA VALOR DE k 
	for(int b = 0; b < ks.size(); b++){

		int k = ks[b];

		// PARA CADA VALOR DE ALPHA
		for(int a = 0; a < alphas.size() ; a++){   				
					
			int alpha = alphas[a];
			Matriz M;

			vector< vector<duplaInt> > resultadosA;

			high_resolution_clock::time_point tAlpha0 = high_resolution_clock::now();

			//PARA CADA KFOLD
			for(int i = 0; i < Kfolds ; i++){	
				M = Mis[i];	

				vector<double> x0; 
				vector < vector < double > > mPCAj;	

				high_resolution_clock::time_point tKfoldi = high_resolution_clock::now();


				for(int l = 0; l < alpha ; l++){
					/**********CALCULO AUTOVECTOR**********/
					x0 = vectorAleatorio(784, l);
					double lambda = metodoPotencia(M, x0, critParada);
					mPCAj.push_back(x0);
					
					/**********DEFLACION**********/
					if(l < alpha - 1){
						Matriz x0x0t(x0, x0);
						x0x0t * lambda;						//x0x0t = x0x0t·lambda
						M = M - x0x0t;
					}
				}


				Matriz TCpcaj = Matriz(mPCAj);
				
				high_resolution_clock::time_point tTC = high_resolution_clock::now();
				duration<double> time_TC = duration_cast<duration<double>>(tTC - tKfoldi);

				cout << "alpha=" << alpha << ", Kfold " << i + 1 << ": " << time_TC.count() << "(Cálculo TC)" << endl; 
				
				vector<imgInfo> trainT = AplicarTransformacion(datos._train[i], TCpcaj);
				vector<imgInfo> testT = AplicarTransformacion(datos._test[i], TCpcaj);

				high_resolution_clock::time_point tTrans = high_resolution_clock::now();
				duration<double> time_Trans = duration_cast<duration<double>>(tTrans - tTC);

				cout << "alpha=" << alpha << ", Kfold " << i + 1 << ": " << time_Trans.count() << "(Transformación de train y test)" << endl;
				

				vector<duplaInt> Kfoldi;

				for(int j=0; j < datos._test[i].size() ; j++){

					vector<double> imagenTest = testT[j]._imagen;
					int etiquetaTest = testT[j]._etiqueta;

					int prediccion = kNN(k, imagenTest, trainT);

					duplaInt realPredicho;
					realPredicho._fst = etiquetaTest;
					realPredicho._snd = prediccion;

					Kfoldi.push_back(realPredicho);
				}

				resultadosA.push_back(Kfoldi);

				high_resolution_clock::time_point tKNN = high_resolution_clock::now();
				duration<double> time_KNN = duration_cast<duration<double>>(tKNN - tTrans);

				cout << "alpha=" << alpha << ", Kfold " << i + 1 << ": " << time_KNN.count() << "(KNN) k=" << k << endl;

			}

			string alphastr = std::to_string(alpha);
			string kstr = std::to_string(k);
			string outt = "ExpPCA-Kfold10-k" + kstr + "-alpha" + alphastr + ".out";
			const char * out = outt.c_str();

			guardarResultados(datos, resultadosA, out);

			high_resolution_clock::time_point tAlpha1 = high_resolution_clock::now();
		    duration<double> time_alphai = duration_cast<duration<double>>(tAlpha1 - tAlpha0);

		    
			cout << "Tiempo PCA total (sin cálculo de M) alpha=" << alpha << ": " << time_alphai.count() << endl; 

		}
	}

}


int main(int argc, char* argv[]){

	string in1 = argv[1];
	string in2 = argv[2];

	//dataIn datos1 = loader(in1);
	

	vector<int> alphas;
	// alphas.push_back(1);
	// alphas.push_back(5);
	// alphas.push_back(10);
	// alphas.push_back(20);
	// alphas.push_back(30);
	// alphas.push_back(40);
	// alphas.push_back(50);
	alphas.push_back(75);
	alphas.push_back(100);
	alphas.push_back(150);

	vector<int> ks;
	ks.push_back(1);
	ks.push_back(3);
	ks.push_back(5);

	//expPCA5(datos1, alphas, 700, ks);


	// for(int a = 0; a < alphas.size(); a++){
	// 	for(int k = 0; k < ks.size(); k++){
	// 		string alphastr = std::to_string(alphas[a]);
	// 		string kstr = std::to_string(ks[k]);
	// 		string out = "ExpPCA-Kfold5-k" + kstr + "-alpha" + alphastr + ".out";

	// 		ObtenerData("dataFile5Fold", out);
	// 	}

	// }	



	dataIn datos2 = loader(in2);
	expPCA10(datos2, alphas, 700, ks);


	for(int a = 0; a < alphas.size(); a++){
		for(int k = 0; k < ks.size(); k++){
			string alphastr = std::to_string(alphas[a]);
			string kstr = std::to_string(ks[k]);
			string out = "ExpPCA-Kfold10-k" + kstr + "-alpha" + alphastr + ".out";

			ObtenerData("dataFile10Fold", out);
		}

	}

	return 0;
}