#include "../Local/Local.h"

vector<int> noUsados;

vector< pair<int,int> >  dameVecinosClique(int** mAdy, int n, vector<int>& cliqueMF){
	vector< pair<int,int> > vecinos;
	for(int i=0; i<n; i++){
		for(int j=0; j < cliqueMF.size(); j++){
			if(mAdy[i][cliqueMF[j]] == 1 && !PerteneceAClique(cliqueMF, i)) {

				/* calculo el grado del nodo */
				int grado=0;
				for(int k = 0; k<n; k++){
					grado += mAdy[i][k];
				}
				vecinos.push_back(make_pair(grado, i));
				j = cliqueMF.size();
			}
		}
	}
	return vecinos;
}

int CMF_Rnd_sinClique(int** mAdy, int n, vector<int>& cliqueAux, vector<int>& cliqueMF){
	/*La idea es armar una clique random usando nodos*/
	/*que no están en la mejor solución hasta ahora*/
	/*ya que con una buena busqueda local deberia haber explorado estos casos*/
	vector<int> candidatos;

	/*Todos los nodos del grafo*/
	for(int i = 0; i<n; i++){
		candidatos.push_back(i);
	}
	/*Le saco los nodos de la clique*/
	for(int i=0; i<cliqueMF.size(); i++){
		for(int j = 0; j<candidatos.size(); j++){
			if(cliqueMF[i] == candidatos[j]){
				candidatos.erase (candidatos.begin()+j);
			}
		}
	}
	/*Mezclo los elementos para tener algo random*/
	random_shuffle (candidatos.begin(), candidatos.end() );

	/*Aca guardo la maxima frontera calculada hasta ahora correspondiente a cliqueMF*/
	int maxFront=0;

	vector<int> clique;

	for(int i=0; i<candidatos.size(); i++){
		/*Agrego un nodo*/
		clique.push_back(candidatos[i]);
		if(esClique(clique, mAdy)){		
			/*Si es una clique calculo su frontera*/
			int CardFront = TamFrontera(clique, mAdy, n);
			if(CardFront > maxFront){
				maxFront = CardFront;
				CopiarClique(clique, cliqueAux);
			}else{
				/*Si no mejora la solución saco el ultimo nodo*/
				clique.pop_back();
			}
		}else{
			/*Si no es clique saco el ultimo para que vuelva a ser clique y sigo probando con los sig*/
			clique.pop_back();	
		}
	}
	return maxFront;

}

int CMF_Rnd_GreedyGRASP(int** mAdy, int n, vector<int>& cliqueAux){
	/*Genero un vector de usados para no repetir busquedas*/
	if(noUsados.empty()){
		for(int i=0; i<n; i++){
			noUsados.push_back(i);
		}
		srand(time(NULL));
		random_shuffle ( noUsados.begin(), noUsados.end() );
	}
	/*Elijo un nodo al azar que no haya sido usado recientemente*/
	int nodo = noUsados.back();
	noUsados.pop_back();

	/*genero una clique y le agrego el nodo elegido al azar*/
	vector<int> clique;
	clique.push_back(nodo);
	int maxFront = Grado(nodo, mAdy, n);

	/*Busco los vecinos de ese nodo*/
	vector< pair<int,int> > vecinos = dameVecinosClique(mAdy, n, clique);
	/*Los ordeno de mayor a menor por su grado*/
	sort(vecinos.rbegin(), vecinos.rend());

	
	int tamClique = 1;

	for(int i=0 ; (i < vecinos.size()) && (vecinos[i].first > tamClique*2) ; i++){
		/*Agrego un nodo*/
		clique.push_back(vecinos[i].second);
		if(esClique(clique, mAdy)){				
			/*Si es una clique calculo su frontera*/
			//int CardFront = TamFrontera(clique, mAdy, n);	
			int CardFront = maxFront + vecinos[i].first - tamClique*2;
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
	CopiarClique(clique, cliqueAux);
	return maxFront;

}



int GRASP_CMF(int** mAdy, int n, vector<int>& cliqueMF, int limite){

	/*Primero busco una solucion inicial*/

	/*Por ahora uso LFS*/
	int maxFront = maxFronCliqueGLF(mAdy, n, cliqueMF);

	/*Auxiliares para usar en las iteraciones*/
	int maxFrontAux=0;
	vector<int> CMF_aux;

	/*Voy a ejecutar GRASP hasta que hayan pasado "limite" iteraciones sin mejorar la solución*/
	/*Decisión totalmente arbitraria, ver después si conviene otra cosa*/
	int iterSinMejorar = 0;

	

	while(iterSinMejorar < limite){

		maxFrontAux= CMF_Rnd_GreedyGRASP(mAdy, n, CMF_aux);

		/*Mejoro CMF_aux con busqueda local*/
		maxFrontAux = MejorarCMF_VecChica(mAdy, n, CMF_aux, maxFrontAux);
		/*Me quedo con la mejor solucion*/
		if(maxFrontAux > maxFront){
			/*Encontre una mejor solucion en esta iteracion*/
			maxFront = maxFrontAux;
			CopiarClique(CMF_aux, cliqueMF);
		}else{
			/*no mejore*/
			iterSinMejorar++;
		}
		CMF_aux.clear();
	}

	return maxFront;
}

int GRASP_CMFSinBLocal(int** mAdy, int n, vector<int>& cliqueMF, int limite){

	/*Primero busco una solucion inicial*/

	/*Por ahora uso LFS*/
	int maxFront = maxFronCliqueGLF(mAdy, n, cliqueMF);

	/*Auxiliares para usar en las iteraciones*/
	int maxFrontAux=0;
	vector<int> CMF_aux;

	/*Voy a ejecutar GRASP hasta que hayan pasado "limite" iteraciones sin mejorar la solución*/
	/*Decisión totalmente arbitraria, ver después si conviene otra cosa*/
	int iterSinMejorar = 0;

	while(iterSinMejorar < limite){

		maxFrontAux= CMF_Rnd_GreedyGRASP(mAdy, n, CMF_aux);
		
		/*Me quedo con la mejor solucion*/
		if(maxFrontAux > maxFront){
			/*Encontre una mejor solucion en esta iteracion*/
			maxFront = maxFrontAux;
			CopiarClique(CMF_aux, cliqueMF);
		}else{
			/*no mejore*/
			iterSinMejorar++;
		}
		CMF_aux.clear();
	}

	return maxFront;
}