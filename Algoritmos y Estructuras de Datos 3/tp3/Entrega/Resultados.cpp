#include "Random/Random.h"

using namespace std;

int maxFrontera;
int** mAdy;
vector<int> cliqueMax;


void maximaFrontera(vector<int> clique, int nodo, int n){

    //Si ya se de antemano que es clique (porque lo era en el paso anterior
    //  y no se agregó nada) no vuelvo a chequearlo.
    bool yaEraClique = !(clique.size() > 0 && clique.back() == nodo-1);  
    if(!yaEraClique && esClique(clique, mAdy)){     

        // calcula el tamaño de la frontera                  
        int tamFron = TamFrontera(clique, mAdy, n); 
        if (tamFron > maxFrontera){
            maxFrontera = tamFron;
            cliqueMax = clique;
        }
    }

    // Si no es clique entonces no sigue la rama. (si llegué a la rama else porque ya sabía que era clique, no hago nada)
    else if(!yaEraClique)  
        return;

    // si ya recorrí todos los nodos, termino.
    if(nodo == n )  
        return;

    // recursión en el siguiente nodo sin agregar nada.
    maximaFrontera(clique, nodo+1, n); 
    clique.push_back(nodo);

    // recursión en el siguiente nodo agregando el nodo de la pos.
    maximaFrontera(clique, nodo+1, n); 
    
}


int main(){

    int res;
    vector<int> cliqueMF;
    int n;


    /*Abro archivo donde voy a guardar resultados*/
    fstream resultadosBack;
    resultadosBack.open("Backtracking/res_back.out", ios::out | ios::ate | ios::app);
    fstream resultadosGreedy;
    resultadosGreedy.open("Greedy/res_greedy.out", ios::out | ios::ate | ios::app);
    fstream resultadosRndGreedy;
    resultadosRndGreedy.open("Greedy/res_RndGreedy.out", ios::out | ios::ate | ios::app);
    fstream resultadosLocal;
    resultadosLocal.open("Local/res_localCompl.out", ios::out | ios::ate | ios::app);
    fstream resultadosGRASP;
    resultadosGRASP.open("GRASP/res_GRASP.out", ios::out | ios::ate | ios::app);
    fstream resultadosGRASPSinBLocal;
    resultadosGRASPSinBLocal.open("GRASP/res_GRASPSinBLocal.out", ios::out | ios::ate | ios::app);

    fstream resultadosRndGreedy2;
    resultadosRndGreedy2.open("Greedy/res_RndGreedyparaBLocal.out", ios::out | ios::ate | ios::app);
    fstream resultadosBLocalRandom;
    resultadosBLocalRandom.open("Local/res_BLocalRandom.out", ios::out | ios::ate | ios::app);

    /*Variación de limite*/
    fstream resultadosGRASPn_2;
    resultadosGRASPn_2.open("GRASP/res_GRASPn_2.out", ios::out | ios::ate | ios::app);

    fstream resultadosGRASPn_4;
    resultadosGRASPn_4.open("GRASP/res_GRASPn_4.out", ios::out | ios::ate | ios::app);

    fstream resultadosGRASPn_8;
    resultadosGRASPn_8.open("GRASP/res_GRASPn_8.out", ios::out | ios::ate | ios::app);

    fstream resultadosGRASPn_1;
    resultadosGRASPn_1.open("GRASP/res_GRASPn_1.out", ios::out | ios::ate | ios::app);




    for(int i = 10; i <= 200; i++){ 
        //abro archivo con datos de entrada
        string nn = to_string(i);
        string source = "GrafosRandom/grafo_d2_n"+nn+".in";
        const char *rutaarchivo = source.c_str();
        ifstream grafo(rutaarchivo);

        /*Cargo la mady con el archivo leido*/
        GenerarYCargarMatAdyArchivo(mAdy, n, grafo);

        /*Voy a almacenar los resultados de distintos algoritmos que resuelven CMF*/

        /*Backtracking*/
        maxFrontera=0;
        cliqueMF.clear();
        cliqueMax.clear();
        maximaFrontera(cliqueMF, 0, n);
        resultadosBack << maxFrontera << endl;
        /*Random Greedy*/
        cliqueMF.clear();
        res = CMF_Rand(mAdy,n, cliqueMF);
        resultadosRndGreedy << res << endl;
        cliqueMF.clear();
        /*Goloso LFS*/
        res = maxFronCliqueGLF(mAdy,n, cliqueMF);
        resultadosGreedy << res << endl;
        /*Busq Local completo*/
        res =MejorarCMF_VecChica(mAdy, n, cliqueMF, res);
        resultadosLocal << res << endl;
        /*GRASP con limite n*/
        cliqueMF.clear();
        res =GRASP_CMF(mAdy, n, cliqueMF, n);
        resultadosGRASP << res << endl;
        /*GRASP sin BLocal*/
        res =GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n);
        resultadosGRASPSinBLocal << res << endl;        

        /*Random para BLocal*/
        cliqueMF.clear();
        res = CMF_Rand(mAdy,n, cliqueMF);
        resultadosRndGreedy2 << res << endl;
        /*Busq Local completo con greedy random*/
        res =MejorarCMF_VecChica(mAdy, n, cliqueMF, res);
        resultadosBLocalRandom << res << endl;

        /*Variacion de limites*/
        cliqueMF.clear();
        res =GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n/2);
        resultadosGRASPn_2 << res << endl;

        cliqueMF.clear();
        res =GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n/4);
        resultadosGRASPn_4 << res << endl;

        cliqueMF.clear();
        res =GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n/8);
        resultadosGRASPn_8 << res << endl;

        cliqueMF.clear();
        res =GRASP_CMFSinBLocal(mAdy, n, cliqueMF, 1);
        resultadosGRASPn_1 << res << endl;

        /*Libero matriz de adyacencia*/
        for (int i = 0; i < n; ++i){
            delete [] mAdy[i];          
        }   
        delete [] mAdy;
        grafo.close();
    }

    resultadosBack.close();
    resultadosGreedy.close();
    resultadosRndGreedy.close();
    resultadosLocal.close();
    resultadosGRASP.close();
    resultadosGRASPSinBLocal.close();
    resultadosBLocalRandom.close();
    resultadosRndGreedy2.close();
    resultadosGRASPn_2.close();
    resultadosGRASPn_4.close();
    resultadosGRASPn_8.close();
    resultadosGRASPn_1.close();
    return 0;

}
