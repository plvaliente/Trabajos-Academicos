#include "../mainfunctions.h"



bool PerteneceAClique(vector<int>& cliqueMF, int nodo){
	
	/*Veo si un nodo pertenece a l clique*/
	bool esta = false;
	for(int i=0; i<cliqueMF.size(); i++){
		esta = (cliqueMF[i] == nodo);
		if(esta){
			return esta;
		}
	}
	return esta;

}


int maxFronCliqueGLF(int** mAdy, int n, vector<int>& clique){

	/*Creo un vector donde voy a guardar cada nodo con su grado*/
	vector <pair<int,int> > grados;

	for(int i=0; i<n; i++){

		grados.push_back(make_pair(Grado(i, mAdy, n), i));
	}

	/*Ordeno el vector de mayor a menor por grados*/
	sort(grados.rbegin(), grados.rend());   // usando iteradores inversos.

	/*Aca guardo la maxima frontera calculada hasta ahora*/
	int maxFront=0;
	clique.clear();
	int tamClique = 0;

	/*Prueba de ciclos*/
	//int cantIter=0;


	for(int i=0 ; (i < n) && (grados[i].first > tamClique*2) ; i++){
		//cantIter++;
		/*Agrego un nodo*/
		clique.push_back(grados[i].second);
		if(esClique(clique, mAdy)){

			/*Si es una clique calculo su frontera*/
			int CardFront = maxFront + grados[i].first - tamClique*2;

			if(CardFront > maxFront){
				maxFront = CardFront;
				
				tamClique++;
			}
			else{
				/*Si no mejora la frontera saco el ultimo y sigo probando con los sig*/
				clique.pop_back();
			}
		}else{
			/*Si no es clique saco el ultimo para que vuelva a ser clique y sigo probando con los sig*/
			clique.pop_back();	
		}
	}

	/*Prueba de ciclos*/
	//return cantIter;
	return maxFront;
}


bool SigueCliqueAlAgregarNodo(int** mAdy, int n, vector<int>& cliqueMF, int nodo){
	bool sigoSiendoClique;
	for(int i=0; i<cliqueMF.size(); i++){
		sigoSiendoClique = (mAdy[cliqueMF[i]][nodo] == 1);
		if (!sigoSiendoClique){
			return false;
		}
	}
	return true;

}

unordered_set<int> dameVecinos(int** mAdy, int n, vector<int>& clique){
	unordered_set<int> vecinos;
	for(int i=0; i<n; i++){
		for(int j=0; j < clique.size(); j++){
			if(mAdy[i][clique[j]] == 1 ) {
				vecinos.insert(i);
			}
		}
	}
	return vecinos;
}

int fronteraSimple(int tam_front_ant,int nodo_nuevo,int tam_clique_ant, vector<int>& grados){
	int nuevaFrontera = tam_front_ant + grados[nodo_nuevo] - tam_clique_ant*2;
	return nuevaFrontera;
}

vector<int> bestChoiceGreedy(int** mAdy, int n, int nodo_inicial, int sigo_buscando, int& maxFront){ // O(n^2*CLIQUE SIZÈ^2) < O(n^4)
	vector<int> grados;
	for(int i=0; i<n; i++){ //O(n^2)
		grados.push_back(Grado(i, mAdy, n));
	}
	
	vector<int> solucion;
	vector<int> clique;

	bool continuo = true;
	bool hayCliqueMayor = true; 
	int no_mejoro = 0;
	unordered_set<int> vecinos;

	solucion.push_back(nodo_inicial);
	clique.push_back(nodo_inicial);

	maxFront= grados[nodo_inicial];
	int fronteraActual = maxFront;

	for(int i=0 ; (i < n - 1) && continuo && hayCliqueMayor; i++){ //O(n)
		vecinos = dameVecinos(mAdy, n, clique); // O(n*CLIQUE SIZÈ^2)
		int actual;
		int fronteraSinAgregar = fronteraActual;
		hayCliqueMayor = false;	
		for(auto nodo_vecino = vecinos.begin(); (nodo_vecino != vecinos.end()); ++nodo_vecino){ //O(TAM VECINOS < n)
			clique.push_back(*nodo_vecino);
			if(esClique(clique, mAdy)){ //O(n)
				hayCliqueMayor = true;				
				int CardFront = fronteraSimple(fronteraSinAgregar, *nodo_vecino, i+1, grados); //O(1)	
				if(CardFront > fronteraActual){
					fronteraActual = CardFront;
					actual = *nodo_vecino;
				}
			}
			clique.pop_back();	
		}
		clique.push_back(actual);

		if(fronteraActual > maxFront){
			solucion = clique;
			maxFront = fronteraActual;
			no_mejoro = 0;
		} else{
			no_mejoro++;
		}

		if(no_mejoro >= sigo_buscando){
			continuo = false;
		}
	}
	return solucion;
}

vector<int> BCMultiple(int** mAdy, int n, int sigo_buscando, int& front_solucion){
	vector<int> clique;
	front_solucion = 0;
	int frontera;
	for (int i = 0; i < n; ++i){
		clique = bestChoiceGreedy(mAdy, n, i, sigo_buscando, frontera);
		if(frontera > front_solucion){
			front_solucion = frontera;
		}
	}
	return clique;
}