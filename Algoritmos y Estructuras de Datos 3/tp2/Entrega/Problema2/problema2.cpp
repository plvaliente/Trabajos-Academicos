#include <iostream>
#include <fstream>
#include <ostream>
#include "ejercicio2.h"

using namespace std;



int main(){

    vector<int> resultados;

    int n = 0;
    int m = 0;

    while(n!=-1 && m!= -1){
        //cout << "dame n y m:" << endl;
        cin >> n >> m;


        //cout << "cargame " << m << " rutas como c1 c2 peso" << endl;

        if (n != -1){

            arista ArrAristas[m];


            for(int i = 0; i<m; i++){
                cin >> ArrAristas[i].c1;
                cin >> ArrAristas[i].c2;
                cin >> ArrAristas[i].costo;
            }



            resultados.push_back(maximaRebaja(n, m, ArrAristas)); 
            
        }
    }

    for(int i=0; i < resultados.size(); i++){
        cout << resultados[i] << endl;
    }
    return 0;

}
