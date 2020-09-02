#include "Greedies.h"
#include <utility>
#include <algorithm>

using namespace std;



int main(){
    int n;
    int** mAdy;
    
    GenerarYCargarMatAdy(mAdy,n);

	int sigo_b = n;
	int tam_front;

	vector<int> res;

	res = BCMultiple(mAdy, n, sigo_b, tam_front);	
	
	MostrarResultado(res, tam_front);

	liberarMatriz(mAdy,n);

    return 0;
}