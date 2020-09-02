#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <chrono>


using namespace std;

#define infinito std::numeric_limits<int>::max()

#define ya chrono::high_resolution_clock::now

int n, m, k, origen, destino;

int**** adyacencias;

int** dijkstra;

/// Adyacencias: Matriz de 4 dimensiones que determina las adyacencias entre ciudades. Cada ciudad se convierte en k+1 pares
///             (ciudad, cantidad de caminos premium utilizados). Si el camino entre dos ciudades c1 y c2 es premium y ya se había
///             pasado por j caminos premium antes, la adyacencia que conecta esas ciudades es la de los nodos (c1, j) -> (c2, j+1)
///             para 0 <= j <= k-1. La distancia de este camino se guarda en la posición [c1][j][c2][j+1] de la matriz.
///
///             Si el camino entre dos ciudades c1 y c2 NO es premium y ya se había pasado por j caminos premium
///             antes, la adyacencia que conecta esas ciudades es la de los nodos (c1, j) -> (c2, j)
///             para 0 <= j <= k. La distancia de este camino se guarda en la posición [c1][j][c2][j] de la matriz.

void GenerarMatriz(){

	// Se genera la matriz de adyacencias y se la rellena con infinito. Costo: O(n*k*n*k).

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

	cin >> n >> m;

	if (n == -1) return 0;
	cin >> origen >> destino >> k;

	/*vector< vector<int> > datos (m,vector<int> (4,0));

	for (int i = 0; i < m; ++i){
		for (int j = 0; j < 4; ++j){
			cin >> datos[i][j];
		}
	}*/

	int c1, c2, p, dist;

	GenerarMatriz(); // O(n*k*n*k)

	for (int i=0; i < m; ++i){     // O(m * k)
		//c1 = datos[i][0]; c2 = datos[i][1]; p = datos[i][2]; dist = datos[i][3];
		cin >> c1 >> c2 >> p >> dist;
		if (p){
			for (int j = 0; j < k; ++j){
				adyacencias[c1-1][j][c2-1][j+1] = dist;   /// Si es premium, los caminos se conectan aumentando en uno 
													  		///  el valor de caminos premium utilizados. (c1,j) se conecta con (c2,j+1)
				adyacencias[c2-1][j][c1-1][j+1] = dist;		/// Como son caminos bidireccionales, (c2, j) se conecta con (c1, j+1) también.
			}
		}
		else{
			for (int j = 0; j < k+1; ++j){
				adyacencias[c1-1][j][c2-1][j] = dist;     /// Si no es premium, los caminos se conectan manteniendo el valor de 
													  		/// caminos premium utilizados. (c1,j) se conecta con (c2,j)
				adyacencias[c2-1][j][c1-1][j] = dist; 
			}
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
	// se Genera la matriz de dijkstra.
	dijkstra = new int*[n];                               // O(n*k)
	for (int i = 0; i < n; ++i){
		dijkstra[i] = new int[k+1];			
	}
	
	
	// Se genera la matriz de nx(k+1) de ciudades ya recorridas y se inicializa con false.
	vector < vector <bool> > ciudadesRecorridas (n, vector < bool > (k+1,false) );        // O(n*k)
  	
     // Se inicializa la matriz de Dijkstra con infinito.
    for (int i = 0; i < n; ++i){                                     // O(n*k)
	    for (int j = 0; j < k+1; ++j){
	        dijkstra[i][j] = infinito;
	    }
    }
  
    // La distancia a la ciudad de origen es siempre cero.
    dijkstra[origen-1][0] = 0;
  
    // Se busca la distancia más corta a todos los vértices.
    for (int count = 0; count < n*(k+1)-1; count++) {               // O(n*k*n*k)  


        // Se busca el nodo (u,v) de menor distancia al origen ya calculada.
        // En la primera iteraciòn, este nodo es siempre la ciudad de origen con 0 caminos premium recorridos.
    	int u,v;
        CiudadMasCercanaAlOrigen(u,v, ciudadesRecorridas);          // O(n*k)
  
        // Se marca la ciudad como ya recorrida para esa cantidad de caminos premium.
        ciudadesRecorridas[u][v] = true;
  
        // Se recorren los vecinos del par (u,v), es decir, de la ciudad en cuestión con v cantidad de caminos premium utilizados.
        for (int i = 0; i < n; i++){                               // O(n)
       		for (int j = v; j <= v+1; j++){   // Por como se construyen las adyacencias, dos nodos pueden ser adyacentes únicamente si
       										  // tienen el mismo valor de j (caminos premium utilizados) o la ciudad de llegada tiene j+1.
  
		        // Se actualiza la matriz de Dijkstra para la ciudad si no fue recorrida todavia, si existe camino desde (u,v) a ella, 
		        // y si el costo de llegar a esa ciudad a través de (u,v) es menor al costo que ya se tenía calculado. 

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

	while (true){

		bool hayDatos = CargarDatos();                  // O(n*k*n*k) 
		if (!hayDatos) return 0;
 
		Dijkstra();                                     // O(n*k*n*k)

		cout << DistanciaMinimaAlDestino() << endl;     // O(k)

		LiberarMatriz();
	}

	return 0;
}

		/*	
			auto start = ya();
		    auto end = ya();

		    t.push_back(chrono::duration_cast<std::chrono::microseconds>(end-start).count());*/