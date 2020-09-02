#include "../mainfunctions.h"

int maxFrontera;
int n;
int** mAdy;
vector<int> cliqueMax;


void maximaFrontera(vector<int> clique, int nodo){

	//Si ya se de antemano que es clique (porque lo era en el paso anterior
	//	y no se agregó nada) no vuelvo a chequearlo.
	bool yaEraClique = !(clique.size() > 0 && clique.back() == nodo-1);  
	if(!yaEraClique && esClique(clique, mAdy)){		

		// calcula el tamaño de la frontera					 
		int tamFron = TamFrontera(clique, mAdy, n); 
		if (tamFron > maxFrontera){
			maxFrontera = tamFron;
			cliqueMax = clique;
		}
	}

	// Si no es clique entonces no sigue la rama. (si llegué a la rama else porque ya sabía que era clique, no hago nada)
	else if(!yaEraClique)  
		return;

	// si ya recorrí todos los nodos, termino.
	if(nodo == n )  
		return;

	// recursión en el siguiente nodo sin agregar nada.
	maximaFrontera(clique, nodo+1); 
	clique.push_back(nodo);

	// recursión en el siguiente nodo agregando el nodo de la pos.
	maximaFrontera(clique, nodo+1); 
	
}