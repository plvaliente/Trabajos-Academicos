#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <limits>
#include <vector>
#include <chrono>


using namespace std;
using namespace std::chrono;


#define infinito std::numeric_limits<int>::max()

auto tStart = high_resolution_clock::now();
auto tEnd = high_resolution_clock::now();
auto acumT = high_resolution_clock::now();
auto acTime = chrono::duration_cast<std::chrono::microseconds>(tStart-tStart);

ifstream grafos;

int n, m, k, origen, destino;

int**** adyacencias;

int** dijkstra;

void GenerarMatriz(){
	adyacencias = new int***[n];

	for (int i = 0; i < n; ++i){
		adyacencias[i] = new int**[k+1];

		for (int j = 0; j < k+1; ++j){
			adyacencias[i][j] = new int*[n];

			for (int l = 0; l < n; ++l){
				adyacencias[i][j][l] = new int[k+1];
				for (int s = 0; s < k+1; ++s){
					adyacencias[i][j][l][s] = infinito;
				}			
			}			
		}
	}
}

void LiberarMatriz(){

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < k+1; ++j){
			for (int l = 0; l < n; ++l){
				delete [] adyacencias[i][j][l];			
			}	
			delete [] adyacencias[i][j];		
		}
		delete [] adyacencias[i];
	}
	delete [] adyacencias;

    // libero memoria de dijkstra
	for (int i = 0; i < n; ++i){
		delete [] dijkstra[i];			
	}	
	delete [] dijkstra;
}

bool CargarDatos() {   // O(n*k*n*k)
	grafos >> n >> m;
	if (n == -1) return 0;
	grafos >> origen >> destino >> k;
	int c1, c2, p, dist;
	tStart = high_resolution_clock::now();
	GenerarMatriz(); // O(n*k*n*k)
	tEnd = high_resolution_clock::now();
	auto aux = chrono::duration_cast<std::chrono::microseconds>(tEnd-tStart);
	acTime = acTime + aux;

	for (int i=0; i < m; ++i){     // O(m * k)
		grafos >> c1 >> c2 >> p >> dist;
		if (p){
			for (int j = 0; j < k; ++j){
				adyacencias[c1-1][j][c2-1][j+1] = dist;   /// Si es premium, los caminos se conectan aumentando en uno 
													  		///  el valor de caminos premium utilizados. (c1,j) se conecta con (c2,j+1)
				adyacencias[c2-1][j][c1-1][j+1] = dist;		/// Como son caminos bidireccionales, (c2, j) se conecta con (c1, j+1) también.
			}
		}
		else{
			tStart = high_resolution_clock::now();
			for (int j = 0; j < k+1; ++j){
				adyacencias[c1-1][j][c2-1][j] = dist;     /// Si no es premium, los caminos se conectan manteniendo el valor de 
													  		/// caminos premium utilizados. (c1,j) se conecta con (c2,j)
				adyacencias[c2-1][j][c1-1][j] = dist; 
			}
			tEnd = high_resolution_clock::now();
			aux = chrono::duration_cast<std::chrono::microseconds>(tEnd-tStart);
			acTime = acTime + aux;
		}

	}
	return true;
}
  
void CiudadMasCercanaAlOrigen(int &minIndexN, int &minIndexK, vector <vector<bool> > ciudadesRecorridas){     // O(n*k)

    int min = infinito;
  
    for (int i = 0; i < n; i++){
   		for (int j = 0; j < k+1; j++){
	    	if (!ciudadesRecorridas[i][j] && dijkstra[i][j] <= min)
	        	min = dijkstra[i][j], minIndexN = i, minIndexK = j;
		}
	}
}

void Dijkstra(){                   // O(n*k*n*k)
	dijkstra = new int*[n];                               // O(n*k)
	for (int i = 0; i < n; ++i){
		dijkstra[i] = new int[k+1];			
	}

	vector < vector <bool> > ciudadesRecorridas (n, vector < bool > (k+1,false) );        // O(n*k)
  	
    for (int i = 0; i < n; ++i){                                     // O(n*k)
	    for (int j = 0; j < k+1; ++j){
	        dijkstra[i][j] = infinito;
	    }
    }
  
    dijkstra[origen-1][0] = 0;
  
    for (int count = 0; count < n*(k+1)-1; count++) {               // O(n*k*n*k)  
	 	int u,v;
        CiudadMasCercanaAlOrigen(u,v, ciudadesRecorridas);          // O(n*k)
  	
  	    ciudadesRecorridas[u][v] = true;
  
        for (int i = 0; i < n; i++){                               // O(n)
       		for (int j = v; j <= v+1; j++){   // Por como se construyen las adyacencias, dos nodos pueden ser adyacentes únicamente si
    	        if (!ciudadesRecorridas[i][j] && adyacencias[u][v][i][j] != infinito && dijkstra[u][v] != infinito 
		        												&& dijkstra[u][v]+adyacencias[u][v][i][j] < dijkstra[i][j])
		            dijkstra[i][j] = dijkstra[u][v] + adyacencias[u][v][i][j];
        	}
    	}
    } 
}

int DistanciaMinimaAlDestino(){      // O(k)

	int minimo = infinito;
	for (int j = 0; j < k+1; ++j){   // O(k)

		if (dijkstra[destino-1][j] < minimo)
			minimo = dijkstra[destino-1][j];
	}
	if (minimo != infinito)
		return minimo;
	return -1;
}

int main () {
	vector<int> t;
	grafos.open("InGrafoCOMP");
	//abro archivo donde voy a guardar medicion de tiempos
	fstream medicion;
    medicion.open("medCompleto", ios::out | ios::ate | ios::app);
	while (true){
		acTime = chrono::duration_cast<std::chrono::microseconds>(tStart-tStart);
		bool hayDatos = CargarDatos();                  // O(n*k*n*k) 
		if (!hayDatos) break ;
		tStart = high_resolution_clock::now();
		Dijkstra();                                     // O(n*k*n*k)
		DistanciaMinimaAlDestino();     // O(k)
		tEnd = high_resolution_clock::now();
		auto aux = chrono::duration_cast<std::chrono::microseconds>(tEnd-tStart);
		acTime = acTime + aux;
		t.push_back(chrono::duration_cast<std::chrono::microseconds>(acTime).count());
		LiberarMatriz();
	}
	
	int promt = 0;
	for (int j=0 ; j<t.size(); j++){
  		promt += t[j];
	}
	promt = promt / t.size();
	medicion << promt << endl;
	grafos.close();
	medicion.close();
	return 0;
}

