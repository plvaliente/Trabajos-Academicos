#include "GRASP/GRASP.h"

using namespace std;

int main(){

    int res;
    vector<int> cliqueMF;
    int n;
    int** mAdy;

    /*Abro archivo donde voy a guardar resultados*/
    fstream resultadosGRASP;
    resultadosGRASP.open("GRASP/Experimentos/res_GRASPMM.out", ios::out | ios::ate | ios::app);

    int resREAL;
    for(int i = 4; i <= 100; i++){ 
        resREAL = i * (i-1);    
        //abro archivo con datos de entrada
        string nn = to_string(i);
        string source = "GrafosGRASP/GraspMM"+ nn;
        const char *rutaarchivo = source.c_str();
        ifstream grafo(rutaarchivo);

        /*Cargo la mady con el archivo leido*/
        GenerarYCargarMatAdyArchivo(mAdy, n, grafo);
        /*Voy a almacenar los resultados de distintos algoritmos que resuelven CMF*/

        res =GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n);
        resultadosGRASP << resREAL << " " << res << endl;        

         /*Libero matriz de adyacencia*/
        for (int i = 0; i < n; ++i){
            delete [] mAdy[i];          
        }   
        delete [] mAdy;
        grafo.close();
    }
    resultadosGRASP.close();

    return 0;

}
