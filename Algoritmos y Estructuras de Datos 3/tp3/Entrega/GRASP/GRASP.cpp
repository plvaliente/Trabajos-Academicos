#include "GRASP.h"

using namespace std;

int main(){


    int n;
    int** mAdy;
    GenerarYCargarMatAdy(mAdy,n);
	
	int res=0;

	/*Creo un vector de nodos para guardar la clique con maxfront*/
	vector<int> cliqueMF;


	/*Uso GRASP para buscar la CMF*/
	/*El ultimo parametro n dice cuantas iteraciones seguir haciendo sin que mejore la solucion*/
	res = GRASP_CMF(mAdy,n, cliqueMF, n);

	MostrarResultado(cliqueMF,res);

	liberarMatriz(mAdy,n);

    return 0;

}