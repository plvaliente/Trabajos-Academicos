#include "Back.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <limits>
#include <chrono>


using namespace std;

#define infinito std::numeric_limits<int>::max()

#define ya chrono::high_resolution_clock::now

int main(){

	GenerarYCargarMatAdy(mAdy,n);

	vector<int> clique;

	auto start = ya();
	maximaFrontera(clique, 0);
	auto end = ya();

	cout << chrono::duration_cast<std::chrono::microseconds>(end-start).count() << endl;

	liberarMatriz(mAdy,n);

    return 0;
}