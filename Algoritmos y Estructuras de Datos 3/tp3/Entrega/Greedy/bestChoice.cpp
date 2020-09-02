#include "Greedies.h"
#include <utility>
#include <algorithm>

using namespace std;



int main(){


    int n;
 
    int** mAdy;
    GenerarYCargarMatAdy(mAdy,n);
	srand(time(NULL));
	int n_rand = rand() % n;
	// nodos del 0 al n-1
	int sigo_b = n;
	int tam_front;
	vector<int>	clique = bestChoiceGreedy(mAdy, n, n_rand, sigo_b, tam_front);	

	MostrarResultado(clique, tam_front);
	liberarMatriz(mAdy,n);

    return 0;
}