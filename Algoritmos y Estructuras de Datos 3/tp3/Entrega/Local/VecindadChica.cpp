#include "Local.h"
#include <utility>
#include <algorithm>

using namespace std;



int main(){


    int n;
    int** mAdy;
    GenerarYCargarMatAdy(mAdy,n);
	
	int res=0;

	/*Creo un vector de nodos para guardar la clique con maxfront*/
	vector<int> cliqueMF;


	/*Primero uso una heurística para obtener alguna solución*/

	/*Por ahora uso LFS*/

	res = maxFronCliqueGLF(mAdy, n, cliqueMF);

	// Descomentar para comparar resultados antes y despues de la busqueda local
	//MostrarResultado(cliqueMF,res);

	/*Prueba con random*/
	//res= CMF_Rand(mAdy, n, cliqueMF);

	/*Voy a intentar mejorarla con Busqueda Local Vecindad Chica*/
	res = MejorarCMF_VecChica(mAdy,n, cliqueMF, res);

	MostrarResultado(cliqueMF,res);
	liberarMatriz(mAdy,n);

    return 0;

}