#include "Random/Random.h"


using namespace std;

vector<int> maxMascara;

int maxFrontera;
vector<int> cliqueMax;


void maximaFrontera(vector<int> clique, int nodo, int** mAdy, int n){

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

    maximaFrontera(clique, nodo+1, mAdy, n); // recursión en el siguiente nodo sin agregar nada.
    clique.push_back(nodo);
    maximaFrontera(clique, nodo+1, mAdy, n); // recursión en el siguiente nodo agregando el nodo de la pos.
    
}

int main(){

    int res;
    vector<int> cliqueMF;
    int n;
    int** mAdy;


    /*Abro archivo donde voy a guardar resultados*/
    fstream resultadosBack;
    resultadosBack.open("Backtracking/res_backMalos.out", ios::out | ios::ate | ios::app);
    fstream resultadosGreedy;
    resultadosGreedy.open("Greedy/res_greedyMalos.out", ios::out | ios::ate | ios::app);
    fstream resultadosRndGreedy;
    resultadosRndGreedy.open("Greedy/res_RndGreedyMalos.out", ios::out | ios::ate | ios::app);
    fstream resultadosLocal;
    resultadosLocal.open("Local/res_localComplMalos.out", ios::out | ios::ate | ios::app);
    fstream resultadosGRASPSinBLocal;
    resultadosGRASPSinBLocal.open("GRASP/res_GRASPSinBLocalMalos.out", ios::out | ios::ate | ios::app);


    for(int i = 16; i <= 199; i=i+3){ 
        //abro archivo con datos de entrada
        string nn = to_string(i);
        string source = "GrafosMalos/grafoMalo"+nn;
        const char *rutaarchivo = source.c_str();
        ifstream grafo(rutaarchivo);

        /*Cargo la mady con el archivo leido*/
        GenerarYCargarMatAdyArchivo(mAdy, n, grafo);

        /*Voy a almacenar los resultados de distintos algoritmos que resuelven CMF*/

        /*Backtracking*/
        maxFrontera=0;
        cliqueMF.clear();
        cliqueMax.clear();
        maximaFrontera(cliqueMF, 0, mAdy, n);
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
        /*GRASP sin BLocal*/
        res =GRASP_CMFSinBLocal(mAdy, n, cliqueMF, n);
        resultadosGRASPSinBLocal << res << endl;        

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
    resultadosGRASPSinBLocal.close();

    return 0;

}
