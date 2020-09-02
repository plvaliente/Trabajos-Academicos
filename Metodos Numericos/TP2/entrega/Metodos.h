#ifndef MODULO_METODOS_H_
#define MODULO_METODOS_H_

#include "Matriz.h"
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <queue>


struct imgInfo {
    vector<double> _imagen;
    int _etiqueta;
};

struct medicion {
    double _minimo;
    double _promedio;
};

struct imgInfoDist {
    vector <double> _imagen;
    int _etiqueta;
    double _distancia;

    bool operator < (const imgInfoDist& otra) const{
    	return _distancia < otra._distancia;
    }
};

struct duplaInt {
    int _fst;
    int _snd;
};

struct dataIn {
    int _k;
    int _alpha;
    int _gamma;
    int _Kfold;
    vector < vector< imgInfo > > _train;
    vector < vector< imgInfo > > _test;
};

double distancia(vector<double>& x, vector<double>& y){
	double acum = 0;									 
	for(int i=0; i < x.size(); i++){
		acum += pow((x[i] - y[i]), 2);
	}
	return sqrt(acum);
}

vector<double> vectorAleatorio(int size, int seed){
	vector<double> resultado;
	srand(seed);
	for(int i=0 ; i < size ; i++ ){
		resultado.push_back(rand() % 255);
	}
	return resultado;	
}

int moda(vector<int>& etiquetas){
	sort(etiquetas.begin(), etiquetas.end());
	vector<duplaInt> cuentas;
	int etiqueta = etiquetas[0];
	int contador = 0;
	for(int i=0; i < etiquetas.size(); i++ ){
		if(etiquetas[i] == etiqueta){
			contador++;
		}
		else{
			duplaInt dupla;
			dupla._fst = etiqueta;
			dupla._snd = contador;
			cuentas.push_back(dupla);
			//cout << "etiqueta: " << etiqueta << ". Contador: " << contador << endl;
			contador = 1;
			etiqueta = etiquetas[i];
		}
	}
	duplaInt dupla;
	dupla._fst = etiqueta;
	dupla._snd = contador;

	//cout << "etiqueta: " << etiqueta << ". Contador: " << contador << endl;
	cuentas.push_back(dupla);

	int masrepetido;
	int repeticiones = 0;
	for(int j=0; j < cuentas.size(); j++){
		if(cuentas[j]._snd > repeticiones){
			masrepetido = cuentas[j]._fst;
		}
	}
	return masrepetido;
}

int kNN(int k, vector<double>& img, vector< imgInfo >& bdd ){
	/**********CREO COLA DE PRIORIDAD**********/
	priority_queue < imgInfoDist > colaDePrioridad;

	/**********INSERTO LOS K DE MENOR DISTANCIA**********/
	for(int j=0 ; j < bdd.size(); j++){					
		double dist = distancia(bdd[j]._imagen, img);
		imgInfoDist infoImagen;
		infoImagen._imagen = bdd[j]._imagen;
		infoImagen._etiqueta = bdd[j]._etiqueta;
		infoImagen._distancia = dist;
		colaDePrioridad.push(infoImagen);
		if(j > k-1 ){
			colaDePrioridad.pop();					// Mantengo k elementos dentro de cola
		}
	}

	/**********GENERO VECTOR DE ETIQUETAS**********/
	vector <int> etiquetas;
	for(int l = 0; l < k; l++){
		etiquetas.push_back(colaDePrioridad.top()._etiqueta);
		colaDePrioridad.pop();
	}

	/**********APLICO MODA**********/
	int resultado = moda(etiquetas);
	return resultado;
}


vector< imgInfo > cargarImagenes(string str){		//tarda +- 2.6 segundos en cargar train.csv
	char *s = &str[0u];
	ifstream myReadFile;
    myReadFile.open(s);
	vector < imgInfo > imagenes ;

    if (myReadFile.is_open()) {

    	string t;				
    	myReadFile >> t;								//Leo la primera linea y no la guardo

    	while(!myReadFile.eof()){
    		string et;
    		string el;
    		int etiqueta;
    		int elem;
    		vector< double > pixels;

			getline(myReadFile, et, ','); 				//leo la etiqueta como string
			const char * et2 = et.c_str();	
			etiqueta = atoi(et2); 						//convierto la etiqueta a int
    		for(int i=0; i < 783 ; i++){

				getline(myReadFile, el, ',');			//leo el pixel como string
				const char * el2 = el.c_str();
				elem = atoi(el2); 						//convierto el pixel a int
				pixels.push_back(elem);
    		}
    		getline(myReadFile, el, '\n');			//leo el ultimo pixel como string
			const char * el2 = el.c_str();
			elem = atoi(el2); 						//convierto el pixel a int
			pixels.push_back(elem);

    		imgInfo img;
    		img._imagen = pixels;
    		img._etiqueta = etiqueta;
    		imagenes.push_back(img);
    	}

	}
	myReadFile.close();

	cout << "cargado" << endl;

	return imagenes;
}


dataIn loader(string str){
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
			for(int j=0 ; j < 42000 ; j++){
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


void coutVector(vector<double> v){
    cout << '[' ;
    for(int i = 0; i < v.size() ; i++){
        cout << v[i] ;
        if(i != v.size() -1 ){
            cout << ", ";
        }
    }
    cout << ']' << endl;
}

void coutVector(vector<int> v){
    cout << '[' ;
    for(int i = 0; i < v.size() ; i++){
        cout << v[i] ;
        if(i != v.size() -1 ){
            cout << ", ";
        }
    }
    cout << ']' << endl;
}

void normalizar(vector<double>& v){
	double acum = 0;
	int n = v.size();

	for(int i = 0; i < n; i++){
		acum += v[i] * v[i];
	}
	acum = sqrt(acum);

	for (int i = 0; i < n; i++){
		v[i] /= acum;
	}
}

double productoInterno(vector<double>& v, vector<double>& w){
	double res = 0;
	int n = v.size();

	for (int i = 0; i < n; i++){
		res += v[i] * w[i];
	}
	return res;
}

double metodoPotencia(Matriz& B, vector<double>& x, int parada){
	/**********APLICO ALGORITMO**********/
	for (int i = 0; i < parada; i++){
		x = B.porVector(x);
		normalizar(x);							// x = B·x, ||x|| = 1
	}											// x es autovector

	/**********CALCULO AUTOVALOR**********/
	vector<double> Bx = B.porVector(x);
	double lambda = productoInterno(Bx, x);	// lambda = (Bx)'·x = (lambda·x')·x = lambda·||x||^2 = lambda·1 
	return lambda;
}

Matriz PCA(vector<imgInfo>& bdd, int alpha, int critParada){
	/**********GENERO X**********/
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
	Matriz M = Xt * X;							// M = X'·X

	/**********INICIALIZO ALGUNAS VARIABLES**********/
	vector < vector < double > > mPCA;	
	vector<double> x0; 

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


	/**********MATRIZ DE LA TRANSFOMACION**********/
	Matriz TCpca = Matriz(mPCA);

	return	TCpca;
}

Matriz PLSda(vector<imgInfo>& bdd, int gamma, int critParada){
	/**********GENERO X**********/
	vector<double> mu = bdd[0]._imagen;
	int bddSize = bdd.size();
	int imgSize = mu.size();
	for(int i = 1 ; i < bddSize ; i++){
		for(int j = 0 ; j < imgSize ; j++ ){
			mu[j] += bdd[i]._imagen[j];
		}
	}

	for(int k = 0 ; k < imgSize ; k++){
		mu[k] = mu[k] /(double) bddSize;		//mu <- Promedio de las imagenes		
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

	/**********GENERO Y**********/
	vector< vector <double> > preY;
	double sumaPreYi = -8; 						//suma de una fila de preY
	for(int i=0 ; i < bddSize; i++){
		vector<double> filaY;
		for(int j = 0; j < 10 ; j++ ){
			if(bdd[i]._etiqueta == j){
				filaY.push_back(1);
			}
			else{
				filaY.push_back(-1);
			}
		}
		for(int k = 0 ; k < 10 ; k++){
			filaY[k] = (filaY[k] - sumaPreYi) /(double) sqrt(bddSize - 1);
		}
		preY.push_back(filaY);
	}
	Matriz Y(preY);

	/**********INICIALIZO ALGUNAS VARIABLES**********/
	vector < vector < double > > mPLS;	
	vector<double> wi;
	vector<double> ti;
	Matriz Yt;
	Matriz Z;
	Matriz Zt;
	Matriz Mi;
	Matriz deflaX;
	Matriz deflaY;
	
	for(int j = 0; j < gamma ; j++){
		/**********GENERO Mi**********/
		Yt = Y.trasponer();
		Z = Yt * X;							// Z = Y'·X
		Zt = Z.trasponer();					// Z' = X'·Y
		Mi = Zt * Z;						// Mi = Z'·Z = X'·Y·Y'·X  
		
		/**********CALCULO AUTOVECTOR**********/
		wi = vectorAleatorio(784, j);
		double lambdaj = metodoPotencia(Mi, wi, critParada);
		//cout << fixed;
		//cout << scientific << lambdaj << endl;
		mPLS.push_back(wi);

		/**********GENERO ti**********/	
		ti = X.porVector(wi);
		normalizar(ti);

		/**********DEFLACION X**********/
		vector <double> titX = X.vectorTraspuestoPor(ti);  // titX = ti'·X
		deflaX = Matriz(ti,titX);
		X = X - deflaX;						// X = X - (ti·ti'·X)

		/**********DEFLACION Y**********/
		vector <double> titY = Y.vectorTraspuestoPor(ti); 	// titY = ti'·Y
		deflaY = Matriz(ti,titY);
		Y = Y - deflaY;						// Y = Y - (ti·ti'·Y)		
	}

	/**********MATRIZ DE LA TRANSFOMACION**********/
	Matriz TCpls = Matriz(mPLS);
	return TCpls;
}

void guardarResultados(dataIn& datos, vector< vector<duplaInt> >& resultados, const char * out){
    ofstream myfile;
    myfile.open (out);
    int ninst = resultados.size();
	int tamTest = resultados[0].size();

	/********* Escribo primera linea **********/
	/***** k alpha gamma Kfold tamañoTest *****/

    myfile << datos._k << " " << datos._alpha << " " << datos._gamma << " " << datos._Kfold << " " << tamTest << endl;

    /********* Cada linea es un Kfold **********/
    /********* (etiquetaReal prediccion) (etiquetaReal prediccion) (etiquetaReal prediccion) **********/

    if (myfile.is_open()){
        for(int i = 0; i < ninst ; i++){
            for(int j = 0; j < tamTest; j++){
                myfile << resultados[i][j]._fst << " " << resultados[i][j]._snd << " ";
            }
            myfile << endl;
        }
    }   
}

vector< vector<duplaInt> > diego(string str){
	char *s = &str[0u];
	ifstream myReadFile;
    myReadFile.open(s);

	vector< vector<duplaInt> > resultados;
	int k;
	int alpha;
	int gamma;
	int Kfold;
	int tamTest;
	int etiquetaReal;
	int prediccion;

	if (myReadFile.is_open()) {
    
    	myReadFile >> k;
    	myReadFile >> alpha;
    	myReadFile >> gamma;
    	myReadFile >> Kfold;
    	myReadFile >> tamTest;

		for(int i=0; i < Kfold ; i++){

			vector<duplaInt> Kfoldi;

			for(int j=0 ; j < tamTest ; j++){
				duplaInt dupla;
				myReadFile >> dupla._fst;
				myReadFile >> dupla._snd;

				Kfoldi.push_back(dupla);
			}
			resultados.push_back(Kfoldi);
		}

	}
	return resultados;
}

Matriz MatrizDeConfusionDeDigitos(vector<duplaInt>& medidas){
	Matriz resultado = Matriz(10,10);
	for(int i=0; i < medidas.size() ; i++){
		resultado(medidas[i]._fst, medidas[i]._snd) += 1;
	}
	return resultado;
}

vector<double> RecallDigitos(Matriz& mConfusion){
	vector<double> recalls(10);
	int truePositive;
	int reales;
	for(int i=0; i < 10 ; i++){
		reales = 0;
		truePositive = mConfusion(i,i);
	    
	    for(int j=0; j < mConfusion.columnas() ; j++){
	    	reales += mConfusion(i,j);
		}

		recalls[i] = truePositive / (double) reales;
	}
	return recalls;
}

vector<double> PresitionDigitos(Matriz& mConfusion){
	vector<double> presition(10);
	int truePositive;
	int predichos;
	for(int i=0; i < 10 ; i++){
		predichos = 0;
		truePositive = mConfusion(i,i);
	    
	    for(int j=0; j < mConfusion.filas() ; j++){
	    	predichos += mConfusion(j,i);
		}

		presition[i] = truePositive / (double) predichos;
	}
	return presition;
}

medicion RecallMinYProm(Matriz& mConfusion){
	int truePositive;
	int reales;
	medicion res;
	res._minimo = 1;
	double actual = 0;
	double accProm = 0;
	for(int i=0; i < 10 ; i++){
		reales = 0;
		truePositive = mConfusion(i,i);
	    for(int j=0; j < mConfusion.columnas() ; j++){
	    	reales += mConfusion(i,j);
		}
		actual = truePositive / (double) reales;
		accProm += actual;
		if(res._minimo > actual){
			res._minimo = actual;
		}
	}
	res._promedio = accProm / (double) 10;
	return res;
}

medicion PresitionMinYProm(Matriz& mConfusion){
	medicion res;
	res._minimo = 1;
	double actual = 0;
	double accProm = 0;
	int truePositive;
	int predichos;
	for(int i=0; i < 10 ; i++){
		predichos = 0;
		truePositive = mConfusion(i,i);
	    
	    for(int j=0; j < mConfusion.filas() ; j++){
	    	predichos += mConfusion(j,i);
		}
		actual = truePositive / (double) predichos;
		accProm += actual;
		if(res._minimo > actual){
			res._minimo = actual;
		}
	}
	res._promedio = accProm / (double) 10;
	return res;
}

void ObtenerData(string outName, string inData){
	char *charName = &outName[0u];
	ofstream writeFile;
    writeFile.open(charName,ios::app); // HACE QUE IMPRIMA AL FINAL DE LINEA

    medicion presition; // PRESITION: Promedio y minimo de todos los folds
    medicion recall;	// RECALL: Promedio y minimo de todos los folds
	double hitRate = 0; // HITRATE: Promedio de todos los folds
	double presMIN = 0;
    double presPROM = 0;
    double recMIN = 0;
    double recPROM = 0;
    double hitI;
    
    vector< vector<duplaInt> > data = diego(inData);

    int acertados;
    int total;
    for(int i=0; i < data.size() ; i++){
    	acertados = 0;
    	total = 0;
	    for(int j=0; j < data[i].size() ; j++){
			if(data[i][j]._fst == data[i][j]._snd){
				acertados++; 
			}
			total++;	
		}
		hitI = acertados / (double) total;
		hitRate += hitI;
	
		Matriz conf = MatrizDeConfusionDeDigitos(data[i]);
		medicion auxRecall = RecallMinYProm(conf);
		medicion auxPres = PresitionMinYProm(conf);
		
		presMIN += auxPres._minimo;
		presPROM += auxPres._promedio;
		recMIN += auxRecall._minimo;
		recPROM += auxRecall._promedio;
	}
	presition._minimo = presMIN / (double) data.size();
    presition._promedio = presPROM / (double) data.size();
    recall._minimo = recMIN / (double) data.size();
    recall._promedio = recPROM / (double) data.size();
    hitRate = hitRate / (double) data.size();

 	// OUTPUT: "HitRate RecallMINIMO RecallPROMEDIO PresitionMINIMO PresitionPROMEDIO"
    writeFile << fixed << hitRate << " " << recall._minimo << " " << recall._promedio << " " << presition._minimo << " " << presition._promedio << endl;
    writeFile.close();
}

vector<imgInfo> AplicarTransformacion(vector<imgInfo>& base, Matriz& tLineal){
	vector<imgInfo> resultado;
	for(int i=0; i < base.size() ; i++){
		imgInfo img;
		img._imagen = tLineal.porVector(base[i]._imagen);
		img._etiqueta = base[i]._etiqueta;
		resultado.push_back(img);				
	}
	return resultado;
}

double normaDos(vector<double>& x){
	double acum;
		for(int i=0; i < x.size(); i++){
		acum = pow((x[i]), 2);
	}
	return sqrt(acum);
}

int modaPosicional(vector <imgInfoDist>& imgs, vector<double>& original){
	double normOrig = normaDos(original);
	double zeroFive = normOrig * 0.05;
	double oneFive = normOrig * 0.15;
	double twoFive = normOrig * 0.25;
	double fourZero = normOrig * 0.40;
	vector<int> posiciones(10);
	for(int k=0; k < 10 ; k++){
		posiciones[k] = 0;
	}
	for(int i=0; i < imgs.size() ; i++){
		if(imgs[i]._distancia <= zeroFive){
			posiciones[imgs[i]._etiqueta] += 12;
		}
		else if(imgs[i]._distancia <= oneFive){
			posiciones[imgs[i]._etiqueta] += 7;	
		}
		else if(imgs[i]._distancia <= twoFive){
			posiciones[imgs[i]._etiqueta] += 4;	
		}
		else if(imgs[i]._distancia <= fourZero){
			posiciones[imgs[i]._etiqueta] += 2;	
		}
		else{
			posiciones[imgs[i]._etiqueta] += 1;	
		}
	}
	int actual = 0;
	int moda = 0;
	for(int j=0; j < 10 ; j++){
		if(actual < posiciones[j]){
			actual = posiciones[j];
			moda = j;
		}	
	}
	return moda;
}

int kNNVersion2(int k, vector<double>& img, vector< imgInfo >& bdd ){
	/**********CREO COLA DE PRIORIDAD**********/
	priority_queue < imgInfoDist > colaDePrioridad;

	/**********INSERTO LOS K DE MENOR DISTANCIA**********/
	for(int j=0 ; j < bdd.size(); j++){					
		double dist = distancia(bdd[j]._imagen, img);
		imgInfoDist infoImagen;
		infoImagen._imagen = bdd[j]._imagen;
		infoImagen._etiqueta = bdd[j]._etiqueta;
		infoImagen._distancia = dist;
		colaDePrioridad.push(infoImagen);
		if(j > k-1 ){
			colaDePrioridad.pop();					// Mantengo k elementos dentro de cola
		}
	}

	/**********GENERO VECTOR DE ETIQUETAS**********/
	vector <imgInfoDist> etiquetas;
	for(int l = 0; l < k; l++){
		etiquetas.push_back(colaDePrioridad.top());
		colaDePrioridad.pop();
	}

	/**********APLICO MODA**********/
	int resultado = modaPosicional(etiquetas, img);
	return resultado;
}


vector<double> lambdasPCA(vector<imgInfo>& bdd, int alpha, int critParada){
	vector<double> res;
	vector<double> mu = bdd[0]._imagen;
	int bddSize = bdd.size();
	int imgSize = mu.size();
	for(int i = 1 ; i < bddSize ; i++){
		for(int j = 0 ; j < imgSize ; j++ ){
			mu[j] += bdd[i]._imagen[j];
		}
	}
	for(int k = 0 ; k < imgSize ; k++){
		mu[k] = mu[k] /(double) bddSize;
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
	Matriz Xt = X.trasponer();
	Matriz M = Xt * X;							// M = X'·X
	vector < vector < double > > mPCA;	
	vector<double> x0; 
	for(int i = 0; i < alpha ; i++){
		x0 = vectorAleatorio(784, i);
		double lambda = metodoPotencia(M, x0, critParada);
		
		res.push_back(lambda);
		
		mPCA.push_back(x0);
		Matriz x0x0t(x0, x0);
		x0x0t * lambda;						//x0x0t = x0x0t·lambda
		M = M - x0x0t;
	}
	return	res;
}

vector<double> lambdasPLSda(vector<imgInfo>& bdd, int gamma, int critParada){
	vector<double> res;
	vector<double> mu = bdd[0]._imagen;
	int bddSize = bdd.size();
	int imgSize = mu.size();
	for(int i = 1 ; i < bddSize ; i++){
		for(int j = 0 ; j < imgSize ; j++ ){
			mu[j] += bdd[i]._imagen[j];
		}
	}
	for(int k = 0 ; k < imgSize ; k++){
		mu[k] = mu[k] /(double) bddSize;		//mu <- Promedio de las imagenes		
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
	vector< vector <double> > preY;
	double sumaPreYi = -8; 						//suma de una fila de preY
	for(int i=0 ; i < bddSize; i++){
		vector<double> filaY;
		for(int j = 0; j < 10 ; j++ ){
			if(bdd[i]._etiqueta == j){
				filaY.push_back(1);
			}
			else{
				filaY.push_back(-1);
			}
		}
		for(int k = 0 ; k < 10 ; k++){
			filaY[k] = (filaY[k] - sumaPreYi) /(double) sqrt(bddSize - 1);
		}
		preY.push_back(filaY);
	}
	Matriz Y(preY);
	vector < vector < double > > mPLS;	
	vector<double> wi;
	vector<double> ti;
	Matriz Yt;
	Matriz Z;
	Matriz Zt;
	Matriz Mi;
	Matriz deflaX;
	Matriz deflaY;
	for(int j = 0; j < gamma ; j++){
		Yt = Y.trasponer();
		Z = Yt * X;							// Z = Y'·X
		Zt = Z.trasponer();					// Z' = X'·Y
		Mi = Zt * Z;						// Mi = Z'·Z = X'·Y·Y'·X  
		wi = vectorAleatorio(784, j);
		double lambdaj = metodoPotencia(Mi, wi, critParada);
		
		res.push_back(lambdaj);

		mPLS.push_back(wi);
		ti = X.porVector(wi);
		normalizar(ti);
		vector <double> titX = X.vectorTraspuestoPor(ti);  // titX = ti'·X
		deflaX = Matriz(ti,titX);
		X = X - deflaX;						// X = X - (ti·ti'·X)
		vector <double> titY = Y.vectorTraspuestoPor(ti); 	// titY = ti'·Y
		deflaY = Matriz(ti,titY);
		Y = Y - deflaY;						// Y = Y - (ti·ti'·Y)		
	}
	return res;
}

vector < vector< double > > cargarTest(string str){
	char *s = &str[0u];
	ifstream myReadFile;
    myReadFile.open(s);
	vector < vector< double > > imagenes ;

    if (myReadFile.is_open()) {

    	string t;				
    	myReadFile >> t;								//Leo la primera linea y no la guardo

    	while(!myReadFile.eof()){
    		string el;
    		int elem;
    		vector< double > pixels;

    		for(int i=0; i < 783 ; i++){

				getline(myReadFile, el, ',');			//leo el pixel como string
				const char * el2 = el.c_str();
				elem = atoi(el2); 						//convierto el pixel a int
				pixels.push_back(elem);
    		}
    		getline(myReadFile, el, '\n');			//leo el ultimo pixel como string
			const char * el2 = el.c_str();
			elem = atoi(el2); 						//convierto el pixel a int
			pixels.push_back(elem);

    		imagenes.push_back(pixels);
		}
	}
	myReadFile.close();
	
	return imagenes;
}
  
#endif