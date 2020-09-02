#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>

using namespace std;


void GenerarYCargarMatAdy(int** &mAdy, int &n){

    int m;
 
    cin >> n >> m;

    //Creo una matriz de adyacencias
    mAdy= new int*[n];
    for (int i = 0; i < n; ++i){
		mAdy[i] = new int[n];			
	}
    //Inicialmente la lleno con 0
    for(int i = 0; i<n; i++){
    	for(int j=0; j<n; j++){
    		mAdy[i][j]=0;
    	}
    }
    int a;
    int b;

    //Lleno la matriz con el grafo que me pasan
    for(int i = 0; i<m; i++){
        cin >> a;
        cin >> b;

        //Como empieza de 0 tengo que correr el indice, así el indice 0 representa al nodo 1 por ej
        mAdy[a-1][b-1]=1;
        mAdy[b-1][a-1]=1;
    }	
}

void GenerarYCargarMatAdyArchivo(int** &mAdy, int &n, ifstream& grafo){
    int m;
    grafo >> n >> m;

    //Creo una matriz de adyacencias
    mAdy= new int*[n];
    for (int i = 0; i < n; ++i){
        mAdy[i] = new int[n];           
    }
    //Inicialmente la lleno con 0
    for(int i = 0; i<n; i++){
        for(int j=0; j<n; j++){
            mAdy[i][j]=0;
        }
    }
    int a;
    int b;

    //Lleno la matriz con el grafo que me pasan
    for(int i = 0; i<m; i++){
        grafo >> a;
        grafo >> b;

        //Como empieza de 0 tengo que correr el indice, así el indice 0 representa al nodo 1 por ej
        mAdy[a-1][b-1]=1;
        mAdy[b-1][a-1]=1;
    }   
}

void MatrizGrafoCompleto(int** &mat, int tam){
    mat= new int*[tam];
    for (int i = 0; i < tam; ++i){
        mat[i] = new int[tam];           
    }
    for (int i = 0; i < tam; ++i){
        for (int j = 0; j < tam; ++j){
            if(i == j){
                mat[i][j]= 0;
            } else{
                mat[i][j]= 1;
            }

        }
    }
}

void MostrarResultado(vector<int> cliqueMax, int tamMaxFrontera){

	//Devuelvo el resultado
	cout << tamMaxFrontera << " " << cliqueMax.size() << " ";
	for(int i = 0; i < cliqueMax.size(); i++){
		//Imprimo los nodos de la clique
		cout << (cliqueMax[i] + 1) << " ";
	}
	cout << endl;
}

void liberarMatriz(int** mAdy, int n){
	/*Libero matriz de adyacencia*/
	for (int i = 0; i < n; ++i){
		delete [] mAdy[i];			
	}	
	delete [] mAdy;
}


void CopiarClique(vector<int>& origen, vector<int>& destino){
	/*Copia una clique para evitar asignar por referencia*/
	destino.clear();
	for(int i = 0; i<origen.size(); i++){
		destino.push_back(origen[i]);
	}
}

int TamFrontera(vector<int>& clique, int** mAdy, int n){
	
	/*Cuento cuantos vecinos tiene cada nodo de la clique*/
	int fron = 0;
	for(int i = 0; i<clique.size(); i++){
		for(int j = 0; j<n; j++){
			fron += mAdy[clique[i]][j];
		}
	}
	
	/*Le resto la cantidad de vecinos que ya conte pero son de la clique por lo que no son frontera*/
	fron = fron - (clique.size() * (clique.size() - 1 ));
	return fron;
}


// n: tamanio de la clique mayor o igual a 10. densidad: entero entre 1 y 9
int** grafoMaker(int n, int densidad){

	//Creo matriz de adyacencias 
	int** mAdy= new int*[n];

	for (int i = 0; i < n; ++i){
		mAdy[i] = new int[n];			
	}

    //Inicialmente la lleno con 0
    for(int i = 0; i<n; i++){
    	for(int j=0; j<n; j++){
    		mAdy[i][j]=0;
    	}
    }


	//Creo cliques de tamaño aleatorio hasta llenar n*densidad/10 nodos
	int finCliques = n*densidad/10;
	int i = 0;
	int tamSigClique;

	while(i < finCliques){
		srand(time(NULL) + i*n*100 + n);
		tamSigClique = (rand() % (finCliques) )+1	;
		
		if (tamSigClique + i > finCliques){
			tamSigClique = finCliques - i;
		}		
		
		//cout << tamSigClique << ' ';

		for(int j=i ; j<(i + tamSigClique) ; j++){
			for(int k=j+1; k<(i + tamSigClique); k++){
				mAdy[j][k] = 1;
				mAdy[k][j] = 1;
			}
		}
		i = i + tamSigClique;
	}
	//cout << endl;
	
	//Agrego aristas de forma aleatoria entre todos los nodos.
	for(int j=0 ; j<n ; j++){
		for(int k=j+1 ; k<n ; k++){
			srand(time(NULL) + (j*k + k*n));
			int unir = rand() % 10;
			
			if( unir < densidad){
				mAdy[j][k] = 1;
				mAdy[k][j] = 1;
			}
		}
	}

	return mAdy;
}

int Grado(int nodo, int** mAdy, int n){  
	int grado = 0;
	for (int i = 0; i < n; ++i){
		grado += mAdy[nodo][i];
	}
	return grado;
}

bool esClique(vector<int>& clique, int** mAdy){

	// PRECONDICION: Si el tamanio es > 1, sacando el ultimo nodo, clique es clique.
	if (clique.size() == 0)
		return false;

	bool soyVecinoDelUltimoNodo;

	/*Como originalmente era una clique antes de agregar el ultimo nodo*/
	/*Solo tengo que ver */
	for(int i = 0; i < clique.size()-1; i++){
			soyVecinoDelUltimoNodo = (mAdy[clique[i]][clique.back()] == 1);
			if(!soyVecinoDelUltimoNodo){
				return false;
			}
	}

	// Si tiene solo un nodo, el ciclo no hace nada y devuelve true.
	return true; 
}

