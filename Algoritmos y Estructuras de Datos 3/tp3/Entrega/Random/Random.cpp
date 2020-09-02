#include "Random.h"
#include <utility>
#include <algorithm>

using namespace std;

int main(){


    int n;
    int** mAdy;
    GenerarYCargarMatAdy(mAdy,n);
	
	int res=0;

	/*Creo un vector de nodos para guardar la clique con maxfront*/
	vector<int> cliqueMF;

	res = CMF_Rand(mAdy,n, cliqueMF);

	MostrarResultado(cliqueMF,res);
	liberarMatriz(mAdy,n);

    return 0;

}