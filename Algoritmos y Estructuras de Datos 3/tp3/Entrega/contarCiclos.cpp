#include "Random/Random.h"
#include <chrono>

using namespace std;


void ciclosGreedy(int** mAdy, int n, vector<int>& cliqueMF){
    fstream cicloGreedy;
    cicloGreedy.open("Greedy/ciclos_greedy.out", ios::out | ios::ate | ios::app);
    cliqueMF.clear();
    int res=maxFronCliqueGLF(mAdy, n, cliqueMF);
    cicloGreedy << res << endl;
    cicloGreedy.close();
}

void ciclosRandom(int** mAdy, int n, vector<int>& cliqueMF){
    fstream cicloRandom;
    cicloRandom.open("Greedy/ciclos_random.out", ios::out | ios::ate | ios::app);
    int res=CMF_Rand(mAdy, n, cliqueMF);
    cicloRandom << res << endl;
    cicloRandom.close();
}




int main(){

    vector<int> cliqueMF;
    int n;
    int** mAdy;

    for(int i = 10; i <= 200; i++){ 
        /*Cargo la mady con el archivo leido*/
        MatrizGrafoCompleto(mAdy, i);
        /*Veo tiempos para cada algoritmo*/
        ciclosGreedy(mAdy, i, cliqueMF);
        ciclosRandom(mAdy, i, cliqueMF);
        /*Libero matriz de adyacencia*/
        liberarMatriz(mAdy,i);
    }

    return 0;

}
