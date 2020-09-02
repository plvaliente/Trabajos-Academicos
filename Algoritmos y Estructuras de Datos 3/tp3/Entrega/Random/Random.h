#include "../GRASP/GRASP.h"


int CMF_Rand(int** mAdy, int n, vector<int>& clique){
	
	/*Creo un vector donde voy a guardar todos los nodos*/
	vector<int> candidatos;
	for(int i=0; i<n; i++){
		candidatos.push_back(i);
	}
	/*Mezclo los elementos para tener aleatoreidad en la forma en que armo la clique*/
	random_shuffle (candidatos.begin(), candidatos.end() );

	/*Aca guardo la maxima frontera calculada hasta ahora correspondiente a cliqueMF*/
	int maxFront=0;

	clique.clear();
	int tamClique = 0;

	/*Prueba de ciclos*/
	//int cantIter=0;

	for(int i=0; i<n; i++){
		//cantIter++;
		/*Agrego un nodo*/
		clique.push_back(candidatos[i]);
		if(esClique(clique, mAdy)){					

			/*Si es una clique calculo su frontera*/
			int CardFront = maxFront + Grado(candidatos[i], mAdy, n) - tamClique*2;														//O(n^2)
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
