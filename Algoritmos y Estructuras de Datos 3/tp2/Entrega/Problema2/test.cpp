#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include "ejercicio2.h"

#define ya chrono::high_resolution_clock::now

using namespace std;



int main(){

    vector<int> resultados;
    int res;
    int cantcasos;
    vector<int> t;

    //abro archivo con datos de entrada
    ifstream grafos("grafo");

    fstream medicion;
    medicion.open("medicion", ios::out | ios::ate | ios::app);

    grafos >> cantcasos;

    int n = 0;
    int m = 0;

    while(n!=-1 && m!= -1){
        //cout << "dame n y m:" << endl;
        grafos >> n >> m;


        //cout << "cargame " << m << " rutas como c1 c2 peso" << endl;

        if (n != -1){

            arista ArrAristas[m];


            for(int i = 0; i<m; i++){
                grafos >> ArrAristas[i].c1;
                grafos >> ArrAristas[i].c2;
                grafos >> ArrAristas[i].costo;
            }

            //mido tiempo de ejecución del programa para 1 grafo
            auto start = ya();
            res = maximaRebaja(n, m, ArrAristas);
            auto end = ya();


            t.push_back(chrono::duration_cast<std::chrono::microseconds>(end-start).count());


            resultados.push_back(res); 
            
        }


    }

    int promt = 0;
    for (int j=0 ; j<cantcasos; j++){
        promt += t[j];
    }
    promt = promt / cantcasos;

    medicion << promt << endl;

    medicion.close();
    grafos.close();
    return 0;

}
