#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
using namespace std;

// para compilar: g++ -O3 -std=c++11 -o expPLS expPLS.cpp

void PLSKfold5(vector<int> gammas){
	string tiempos = "outplsFold5Time.data"; 
	char *timeFile = &tiempos[0u];
	ofstream writeFile;
    writeFile.open(timeFile);
	dataIn datos = loader("kfold5.in");
	string k1gamma = "out5FoldsK1gamma";
	string k3gamma = "out5FoldsK3gamma";
	string k5gamma = "out5FoldsK5gamma";  
	for(int i=0; i < gammas.size();i++){
		vector< vector<duplaInt> > resultadoK1;
		vector< vector<duplaInt> > resultadoK3;
		vector< vector<duplaInt> > resultadoK5;
		/**TIME BEGIN**/
		high_resolution_clock::time_point tinit = high_resolution_clock::now();
		duration<double> time_accG_k1 = duration_cast<duration<double>>(tinit - tinit);
		duration<double> time_accG_k3 = duration_cast<duration<double>>(tinit - tinit);
		duration<double> time_accG_k5 = duration_cast<duration<double>>(tinit - tinit);
		/**TIME END**/
		for(int K=0; K < datos._Kfold; K++){
			/**TIME BEGIN**/
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			/**TIME END**/				
			Matriz tPLS = PLSda(datos._train[K], gammas[i], 700);
			vector<imgInfo> trainTransformada = AplicarTransformacion(datos._train[K], tPLS);
			/**TIME BEGIN**/
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    		time_accG_k1 += time_span;
			time_accG_k3 += time_span;
			time_accG_k5 += time_span;
			/**TIME END**/
			vector<duplaInt> foldiK1;
			vector<duplaInt> foldiK3;
			vector<duplaInt> foldiK5;
			for(int j=0; j < datos._test[K].size() ; j++){
				/**TIME BEGIN**/
				high_resolution_clock::time_point taux1 = high_resolution_clock::now();
				/**TIME END**/
				vector<double> imagenTest = tPLS.porVector(datos._test[K][j]._imagen);
				/**TIME BEGIN**/
				high_resolution_clock::time_point taux2 = high_resolution_clock::now();
				duration<double> time_span_aux = duration_cast<duration<double>>(taux2 - taux1);
				time_accG_k1 += time_span_aux;
				time_accG_k3 += time_span_aux;
				time_accG_k5 += time_span_aux;
				/**TIME END**/

				/************** KNN = 1 **************/
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK11 = high_resolution_clock::now();  
				/**TIME END**/
				int prediccionk1 = kNN(1, imagenTest, trainTransformada);
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK12 = high_resolution_clock::now();
    			duration<double> time_spanK1 = duration_cast<duration<double>>(tK12 - tK11);
    			time_accG_k1 += time_spanK1;
    			/**TIME END**/
				duplaInt duplaK1;
				duplaK1._fst = datos._test[K][j]._etiqueta;
				duplaK1._snd = prediccionk1;
				foldiK1.push_back(duplaK1);

				/************** KNN = 3 **************/
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK31 = high_resolution_clock::now();  
				/**TIME END**/
				int prediccionk3 = kNN(3, imagenTest, trainTransformada);
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK32 = high_resolution_clock::now();
    			duration<double> time_spanK3 = duration_cast<duration<double>>(tK32 - tK31);
    			time_accG_k3 += time_spanK3;
    			/**TIME END**/
				duplaInt duplaK3;
				duplaK3._fst = datos._test[K][j]._etiqueta;
				duplaK3._snd = prediccionk3;
				foldiK3.push_back(duplaK3);

				/************** KNN = 5 **************/
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK51 = high_resolution_clock::now();  
				/**TIME END**/
				int prediccionk5 = kNN(5, imagenTest, trainTransformada);
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK52 = high_resolution_clock::now();
    			duration<double> time_spanK5 = duration_cast<duration<double>>(tK52 - tK51);
    			time_accG_k5 += time_spanK5;
    			/**TIME END**/
				duplaInt duplaK5;
				duplaK5._fst = datos._test[K][j]._etiqueta;
				duplaK5._snd = prediccionk5;
				foldiK5.push_back(duplaK5);
			}
			resultadoK1.push_back(foldiK1);
			resultadoK3.push_back(foldiK3);
			resultadoK5.push_back(foldiK5);
		}
		/** WRITE TIME BEGIN **/
		writeFile << time_accG_k1.count() << " " << time_accG_k3.count() << " " << time_accG_k5.count() << endl;
		/** WRITE TIME END **/
		string stringK1 = k1gamma + to_string(gammas[i]);
		char *outK1 = &stringK1[0u];
		string stringK3 = k3gamma + to_string(gammas[i]);
		char *outK3 = &stringK3[0u];
		string stringK5 = k5gamma + to_string(gammas[i]);
		char *outK5 = &stringK5[0u];
		guardarResultados(datos, resultadoK1, outK1);
		guardarResultados(datos, resultadoK3, outK3);
		guardarResultados(datos, resultadoK5, outK5);		
	}
	writeFile.close();
}

void PLSKfold10(vector<int> gammas){
	string tiempos = "outplsFold10Time.data"; 
	char *timeFile = &tiempos[0u];
	ofstream writeFile;
    writeFile.open(timeFile);
	dataIn datos = loader("kfold10.in");
	string k1gamma = "out10FoldsK1gamma";
	string k3gamma = "out10FoldsK3gamma";
	string k5gamma = "out10FoldsK5gamma";  
	for(int i=0; i < gammas.size();i++){
		vector< vector<duplaInt> > resultadoK1;
		vector< vector<duplaInt> > resultadoK3;
		vector< vector<duplaInt> > resultadoK5;
		/**TIME BEGIN**/
		high_resolution_clock::time_point tinit = high_resolution_clock::now();
		duration<double> time_accG_k1 = duration_cast<duration<double>>(tinit - tinit);
		duration<double> time_accG_k3 = duration_cast<duration<double>>(tinit - tinit);
		duration<double> time_accG_k5 = duration_cast<duration<double>>(tinit - tinit);
		/**TIME END**/
		for(int K=0; K < datos._Kfold; K++){
			/**TIME BEGIN**/
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			/**TIME END**/				
			Matriz tPLS = PLSda(datos._train[K], gammas[i], 700);
			vector<imgInfo> trainTransformada = AplicarTransformacion(datos._train[K], tPLS);
			/**TIME BEGIN**/
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    		time_accG_k1 += time_span;
			time_accG_k3 += time_span;
			time_accG_k5 += time_span;
			/**TIME END**/
			vector<duplaInt> foldiK1;
			vector<duplaInt> foldiK3;
			vector<duplaInt> foldiK5;
			for(int j=0; j < datos._test[K].size() ; j++){
				/**TIME BEGIN**/
				high_resolution_clock::time_point taux1 = high_resolution_clock::now();
				/**TIME END**/
				vector<double> imagenTest = tPLS.porVector(datos._test[K][j]._imagen);
				/**TIME BEGIN**/
				high_resolution_clock::time_point taux2 = high_resolution_clock::now();
				duration<double> time_span_aux = duration_cast<duration<double>>(taux2 - taux1);
				time_accG_k1 += time_span_aux;
				time_accG_k3 += time_span_aux;
				time_accG_k5 += time_span_aux;
				/**TIME END**/

				/************** KNN = 1 **************/
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK11 = high_resolution_clock::now();  
				/**TIME END**/
				int prediccionk1 = kNN(1, imagenTest, trainTransformada);
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK12 = high_resolution_clock::now();
    			duration<double> time_spanK1 = duration_cast<duration<double>>(tK12 - tK11);
    			time_accG_k1 += time_spanK1;
    			/**TIME END**/
				duplaInt duplaK1;
				duplaK1._fst = datos._test[K][j]._etiqueta;
				duplaK1._snd = prediccionk1;
				foldiK1.push_back(duplaK1);

				/************** KNN = 3 **************/
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK31 = high_resolution_clock::now();  
				/**TIME END**/
				int prediccionk3 = kNN(3, imagenTest, trainTransformada);
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK32 = high_resolution_clock::now();
    			duration<double> time_spanK3 = duration_cast<duration<double>>(tK32 - tK31);
    			time_accG_k3 += time_spanK3;
    			/**TIME END**/
				duplaInt duplaK3;
				duplaK3._fst = datos._test[K][j]._etiqueta;
				duplaK3._snd = prediccionk3;
				foldiK3.push_back(duplaK3);

				/************** KNN = 5 **************/
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK51 = high_resolution_clock::now();  
				/**TIME END**/
				int prediccionk5 = kNN(5, imagenTest, trainTransformada);
				/**TIME BEGIN**/
				high_resolution_clock::time_point tK52 = high_resolution_clock::now();
    			duration<double> time_spanK5 = duration_cast<duration<double>>(tK52 - tK51);
    			time_accG_k5 += time_spanK5;
    			/**TIME END**/
				duplaInt duplaK5;
				duplaK5._fst = datos._test[K][j]._etiqueta;
				duplaK5._snd = prediccionk5;
				foldiK5.push_back(duplaK5);
			}
			resultadoK1.push_back(foldiK1);
			resultadoK3.push_back(foldiK3);
			resultadoK5.push_back(foldiK5);
		}
		/** WRITE TIME BEGIN **/
		writeFile << time_accG_k1.count() << " " << time_accG_k3.count() << " " << time_accG_k5.count() << endl;
		/** WRITE TIME END **/
		string stringK1 = k1gamma + to_string(gammas[i]);
		char *outK1 = &stringK1[0u];
		string stringK3 = k3gamma + to_string(gammas[i]);
		char *outK3 = &stringK3[0u];
		string stringK5 = k5gamma + to_string(gammas[i]);
		char *outK5 = &stringK5[0u];
		guardarResultados(datos, resultadoK1, outK1);
		guardarResultados(datos, resultadoK3, outK3);
		guardarResultados(datos, resultadoK5, outK5);		
	}
	writeFile.close();
}

int main(){

	vector<int> gammas;
	// gammas.push_back(1);
	// gammas.push_back(5);
	// gammas.push_back(10);
	// gammas.push_back(20);
	// gammas.push_back(30);
	// gammas.push_back(40);
	// gammas.push_back(50);
	gammas.push_back(75);
	gammas.push_back(100);
	gammas.push_back(150);


	//PLSKfold5(gammas);
	//PLSKfold10(gammas);
	
	for(int a = 0; a < gammas.size(); a++){
			string gammastr1 = std::to_string(gammas[a]);
			string out1 = "out10FoldsK1gamma" + gammastr1 ;
			ObtenerData("dataFile10FoldK1", out1);
			string gammastr2 = std::to_string(gammas[a]);
			string out2 = "out10FoldsK3gamma" + gammastr2 ;
			ObtenerData("dataFile10FoldK3", out2);
			string gammastr3 = std::to_string(gammas[a]);
			string out3 = "out10FoldsK5gamma" + gammastr3 ;
			ObtenerData("dataFile10FoldK5", out3);
	}
	return 0;
}