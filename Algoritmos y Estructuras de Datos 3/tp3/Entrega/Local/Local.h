#include "../Greedy/Greedies.h"

vector<int>  dameVecinosCliqueSimple(int** mAdy, int n, vector<int>& cliqueMF){
	vector<int> vecinos;
	for(int i=0; i<n; i++){
		for(int j=0; j < cliqueMF.size(); j++){
			if(mAdy[i][cliqueMF[j]] == 1 && !PerteneceAClique(cliqueMF, i)) {
				vecinos.push_back(i);
				j = cliqueMF.size();
			}
		}
	}
	return vecinos;
}

int mejorarAgregando(int** mAdy, int n, vector<int>& cliqueMF, int res){
	/*El nodo que más mejora la solución*/
	int mejorNodo= -1;
	/*Busco los vecinos de la clique*/
	vector<int> vecinosClique = dameVecinosCliqueSimple(mAdy, n, cliqueMF);
	for(int i=0; i < vecinosClique.size(); i++){
		/*Agrego el nodo i a la clique si se sigue formando una clique*/
		if(SigueCliqueAlAgregarNodo(mAdy, n, cliqueMF, vecinosClique[i])){
			cliqueMF.push_back(vecinosClique[i]);
			/*Calculo el tamaño de la frontera al agregar el nodo*/
			int tamFron = TamFrontera(cliqueMF, mAdy, n);
			if(tamFron > res){
				res = tamFron;
				mejorNodo = vecinosClique[i];
			}
			/*Saco el nodo agregado para probar con el resto*/
			cliqueMF.pop_back();
		}
	}

	/*Finalmente agrego el nodo que más mejora la solución*/
	/*Si ninguno mejora no agrego nada*/
	if(mejorNodo != -1){
		cliqueMF.push_back(mejorNodo);
	}
	return res;
}

int mejorarEliminando(int** mAdy, int n, vector<int>& cliqueMF, int res){
	/*El nodo que más mejora la solución*/
	int mejorNodo=-1;

	for(int i=0; i < cliqueMF.size(); i++){
		int nodoEliminado = cliqueMF[0];
		/*Elimino el primer nodo de la clique*/
		cliqueMF.erase(cliqueMF.begin());
		/*Calculo el tamaño de la frontera luego de eliminar el nodo*/
		int tamFron = TamFrontera(cliqueMF, mAdy, n);
		if(tamFron > res){
			res = tamFron;
			mejorNodo = nodoEliminado;
		}
		/*Agrego el nodo eliminado al final para probar con el resto*/
		cliqueMF.push_back(nodoEliminado);
	}

	/*Finalmente elimino el nodo que más mejora la solución*/
	/*Si ninguno mejora no elimino nada*/
	if(mejorNodo != -1){
		for(int i=0; i<cliqueMF.size(); i++){
			if(cliqueMF[i] == mejorNodo){
				cliqueMF.erase (cliqueMF.begin() + i);
			}

		}
	}
	return res;
}

int mejorarIntercambiando(int** mAdy, int n, vector<int>& cliqueMF, int res){
	int mejoraEliminar = -1;
	int mejoraAgregar = -1;
	for(int i=0; i<cliqueMF.size(); i++){
		int nodoEliminado = cliqueMF[0];
		/*Elimino el primer nodo*/
		cliqueMF.erase(cliqueMF.begin());
		vector<int> vecinosClique = dameVecinosCliqueSimple(mAdy, n, cliqueMF);
		for(int j = 0; j<vecinosClique.size(); j++){
			/*Agrego el nodo j a la clique si se sigue formando una clique*/
			if(SigueCliqueAlAgregarNodo(mAdy, n, cliqueMF, vecinosClique[j])){
				cliqueMF.push_back(vecinosClique[j]);
				/*Calculo el tamaño de la frontera al agregar el nodo*/
				int tamFron = TamFrontera(cliqueMF, mAdy, n);
				if(tamFron > res){
					res = tamFron;
					mejoraEliminar = nodoEliminado;
					mejoraAgregar = vecinosClique[j];
				}
				/*Saco el nodo agregado para probar con el resto*/
				cliqueMF.pop_back();
			}
		}
		/*Agrego el nodo eliminado al final para probar con el resto*/
		cliqueMF.push_back(nodoEliminado);
	}

	/*Hago el intercambio que más mejora la solución*/
	/*Si no hay intercambio que mejore, no hago nada*/
	if(mejoraEliminar != -1){
		for(int i=0; i<cliqueMF.size(); i++){
			if(cliqueMF[i] == mejoraEliminar){
				cliqueMF.erase (cliqueMF.begin() + i);
			}

		}
		cliqueMF.push_back(mejoraAgregar);
	}
	return res;
}

int MejorarCMF_VecChica(int** mAdy, int n, vector<int>& cliqueMF, int res){

	/*En cada iteracion voy a ver si la soluciona mejora agregando un nodo vecino,*/
	/*eliminando un nodo de la clique o intercambiando un nodo por otro*/
	/*y se va a aplicar la solucion que más mejore a la solución inicial*/

	/*Creo una clique auxiliar para cada operacion a realizar*/
	vector<int> cliqueMFAgregar;
	vector<int> cliqueMFEliminar;
	vector<int> cliqueMFIntercambiar;

	/*Voy a seguir mientras siga mejorando mi solucion*/
	bool sigoMejorando = true;

	while(sigoMejorando){

		/*Copio la CMF a las cliques auxiliares*/		
		CopiarClique(cliqueMF, cliqueMFAgregar);
		CopiarClique(cliqueMF, cliqueMFEliminar);
		CopiarClique(cliqueMF, cliqueMFIntercambiar);

		int resAgregar = mejorarAgregando(mAdy, n, cliqueMFAgregar, res);
		int resEliminar = mejorarEliminando(mAdy, n, cliqueMFEliminar, res);
		int resIntercambiar = mejorarIntercambiando(mAdy, n, cliqueMFIntercambiar, res);
		if(res == resAgregar && resAgregar == resEliminar && resEliminar== resIntercambiar){
			/*Significa que ninguna operacion mejora la solucion*/
			sigoMejorando = false;
		}else{
			/*Aplico la operacion que más mejora la solución*/
			if(resAgregar >= resEliminar){
				if(resAgregar >= resIntercambiar){
					res = resAgregar;
					CopiarClique(cliqueMFAgregar, cliqueMF);
				}else{
					res = resIntercambiar;
					CopiarClique(cliqueMFIntercambiar, cliqueMF);
				}
			}else if(resEliminar >= resIntercambiar){
				res = resEliminar;
				CopiarClique(cliqueMFEliminar, cliqueMF);
				}else{
					res = resIntercambiar;
					CopiarClique(cliqueMFIntercambiar, cliqueMF);
				}
		}
	}

	return res;
}

