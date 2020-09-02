#include "AltoHorno.h"
#include <iostream>
#include <fstream>
#include <ostream>
  
using namespace std;

int main(int argc, char* argv[]){

	string in = argv[1];
	const char * out = argv[2];
	string EGLU = argv[3];
	heptla< int, int, int, int, int, int, vector< vector< double > > > datos = cargar(in);

	int ri = datos.first();
	int re = datos.second();
	int m = datos.third() - 1;
	int n = datos.fourth();
	int iso = datos.fifth() ;
	int ninst = datos.sixth();
	vector< vector< double > > lineas = datos.seventh();

	Matriz m0 = crear(n,m,ri,re);
	vector< vector< double > > resultados;
	//cout << m0 << endl;
	//coutVector(lineas[0]);

	if(EGLU == "0"){
		for(int i = 0; i < ninst ; i++){
			Matriz m1 = m0;
			m1.concat(lineas[i]);
			m1.EG();
			vector<double> v1bis = m1.descat();
			vector<double> resEG = m1.resolverTS(v1bis);
			//coutVector(resEG);
 	
			resultados.push_back(resEG);
			//cout << endl << m1 << endl;
		}
	}

	if(EGLU == "1"){
		m0.LU();
		Matriz L = m0.dameL();
		for(int i = 0; i < ninst ; i++){
			vector<double> y1 = L.resolverTI(lineas[i]) ;
			vector<double> resLU = m0.resolverTS(y1);
			//coutVector(resLU);

			resultados.push_back(resLU);
		}
	}	

	guardar(resultados, out);
	
	double deltaR = (re - ri) /(double) m;
	isoterma(resultados, iso, ri, deltaR, n);

	//cout << m << endl;

	return 0;
}