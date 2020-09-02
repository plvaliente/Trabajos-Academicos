#include "Back.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main(){

	GenerarYCargarMatAdy(mAdy,n);

	vector<int> clique;

	maximaFrontera(clique, 0);

	MostrarResultado(cliqueMax, maxFrontera);

	liberarMatriz(mAdy,n);


    return 0;
}