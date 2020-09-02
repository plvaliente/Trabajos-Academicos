#include "Random/Random.h"
#include <chrono>

using namespace std;

#define ya chrono::high_resolution_clock::now
int cantRepeticiones = 5;

int maxFrontera;
vector<int> cliqueMax;


void maximaFronteraBack(vector<int> clique, int nodo, int** mAdy, int n){

    bool yaEraClique = !(clique.size() > 0 && clique.back() == nodo-1);  // Si ya se de antemano que es clique (porque lo era en el paso anterior
    if(!yaEraClique && esClique(clique, mAdy)){                          //  y no se agregó nada) no vuelvo a chequearlo.
        int tamFron = TamFrontera(clique, mAdy, n); // calcula el tamaño de la frontera
        if (tamFron > maxFrontera){
            maxFrontera = tamFron;
            cliqueMax = clique;
        }
    }
    //else if(clique.size() != 0)  // Si no es clique (y la clique no está vacía) entonces no sigue la rama.
    else if(!yaEraClique)  // Si no es clique entonces no sigue la rama. (si llegué a la rama else porque ya sabía que era clique, no hago nada)
        return;
    if(nodo == n )  // si ya recorrí todos los nodos, termino.
        return;

    maximaFronteraBack(clique, nodo+1, mAdy, n); // recursión en el siguiente nodo sin agregar nada.
    clique.push_back(nodo);
    maximaFronteraBack(clique, nodo+1, mAdy, n); // recursión en el siguiente nodo agregando el nodo de la pos.
}

void timeBack(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposBack;
    tiemposBack.open("Backtracking/time_back.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMax.clear();
        cliqueMF.clear();
        maxFrontera=0;
        auto start = ya();
        maximaFronteraBack(cliqueMF, 0, mAdy, n);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposBack << tiempo << endl;
    tiemposBack.close();
}

void timeGreedy(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposGreedy;
    tiemposGreedy.open("Greedy/time_greedy.out", ios::out | ios::ate | ios::app);
    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=maxFronCliqueGLF(mAdy, n, cliqueMF);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposGreedy << tiempo << endl;
    tiemposGreedy.close();
}

void timeRandom(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposRandom;
    tiemposRandom.open("Greedy/time_random.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=CMF_Rand(mAdy, n, cliqueMF);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposRandom << tiempo << endl;
    tiemposRandom.close();
}

void timeLocal(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposLocal;
    tiemposLocal.open("Local/time_local.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        int res= maxFronCliqueGLF(mAdy, n, cliqueMF);
        auto start = ya();
        res=MejorarCMF_VecChica(mAdy, n, cliqueMF, res);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposLocal << tiempo << endl;
    tiemposLocal.close();
}

void timeGRASP(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposGRASP;
    tiemposGRASP.open("GRASP/time_GRASP.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=GRASP_CMF(mAdy, n, cliqueMF, n);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposGRASP << tiempo << endl;
    tiemposGRASP.close();
}

void timeGRASPSinBLocal(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposGRASP;
    tiemposGRASP.open("GRASP/time_GRASPSinBlocal.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposGRASP << tiempo << endl;
    tiemposGRASP.close();
}

void timeGRASPSinBLocal2(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposGRASP;
    tiemposGRASP.open("GRASP/time_GRASPSinBlocaln_2.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n/2);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposGRASP << tiempo << endl;
    tiemposGRASP.close();
}

void timeGRASPSinBLocal4(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposGRASP;
    tiemposGRASP.open("GRASP/time_GRASPSinBlocaln_4.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n/4);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposGRASP << tiempo << endl;
    tiemposGRASP.close();
}

void timeGRASPSinBLocal8(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposGRASP;
    tiemposGRASP.open("GRASP/time_GRASPSinBlocaln_8.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n/8);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposGRASP << tiempo << endl;
    tiemposGRASP.close();
}

void timeGRASPSinBLocal1(int** mAdy, int n, vector<int>& cliqueMF){
    long int tiempo = 0;
    /*Abro archivo donde voy a guardar tiempos*/
    fstream tiemposGRASP;
    tiemposGRASP.open("GRASP/time_GRASPSinBlocaln_1.out", ios::out | ios::ate | ios::app);

    for(int i=0; i<cantRepeticiones; i++){
        cliqueMF.clear();
        auto start = ya();
        int res=GRASP_CMFSinBLocal(mAdy, n, cliqueMF, 1);
        auto end = ya();
        tiempo += chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }

    tiempo = tiempo / cantRepeticiones;
    tiemposGRASP << tiempo << endl;
    tiemposGRASP.close();
}


int main(){

    vector<int> cliqueMF;
    int n;
    int** mAdy;

    for(int i = 10; i <= 200; i++){ 
        /*Cargo la mady con el archivo leido*/
        cout << i << endl;
        MatrizGrafoCompleto(mAdy, i);
        /*Veo tiempos para cada algoritmo*/
        timeBack(mAdy, i, cliqueMF);
        timeGreedy(mAdy, i, cliqueMF);
        timeRandom(mAdy, i, cliqueMF);
        timeLocal(mAdy, i, cliqueMF);
        timeGRASP(mAdy, i, cliqueMF);
        timeGRASPSinBLocal(mAdy, i, cliqueMF);
        timeGRASPSinBLocal2(mAdy, i, cliqueMF);
        timeGRASPSinBLocal4(mAdy, i, cliqueMF);
        timeGRASPSinBLocal8(mAdy, i, cliqueMF);
        timeGRASPSinBLocal1(mAdy, i, cliqueMF);



        /*Libero matriz de adyacencia*/
        liberarMatriz(mAdy,i);
    }

    return 0;

}
