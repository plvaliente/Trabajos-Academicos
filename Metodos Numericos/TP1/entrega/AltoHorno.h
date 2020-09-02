#include "Matriz.h"
#include <cmath>
#include <fstream>

using namespace std;

template< typename K, typename V, typename M, typename N, typename W, typename X, typename Y>
struct heptla {
    K _fst;
    V _snd;
    M _trd;
    N _for;
    W _fif;
    X _sxt;
    Y _svn;
    heptla(K& k, V& v,M& m, N& n,W& w, X& x,Y& y) : _fst(k), _snd(v),_trd(m), _for(n),_fif(w), _sxt(x),_svn(y){}
    K& first(){
        return _fst;
    }
    V& second(){
        return _snd;
    }
    M& third(){
        return _trd;
    }
    N& fourth(){
        return _for;
    }
    W& fifth(){
        return _fif;
    }
    X& sixth(){
        return _sxt;
    }
    Y& seventh(){
        return _svn;
    }
};
template< typename K, typename V >
struct dupla {
    K _fst;
    V _snd;
    dupla(K& k, V& v) : _fst(k), _snd(v){}
    K& first(){
        return _fst;
    }
    V& second(){
        return _snd;
    }
};

int ijAPos(int i, int j, int N){    //Esto esta mal expresado, nos habíamos confundido el orden de los indices y quedó escrito todo al revez. 
    return N*j + i;                 //Lo solucionamos cambiando las ecuaciones de lugar, por lo que simplemente estan mal puestos los nombres.
}

dupla<int, int> posAij(int x, int N){
    int uno = x % N;
    int dos = x / N;
    dupla<int, int> result(uno, dos);
    return result;
}

Matriz crear(int N, int M, int Ri, int Re){
	double dR = (Re - Ri)/(double)M;
	double dT = (2*(double) M_PI )/(double)N;

    Matriz mat = Matriz(N*(M+1) , N*(M+1) );

    for(int i=0 ; i < N ; i++){             //Identidad en las primeras N filas
        mat(i,i) = 1;   
    }

    for(int j=0 ; j < N ; j++ ){
		for(int k =1; k < M; k++){
		    double r = Ri + (dR *(double) k);
		    int jk = ijAPos(j,k, N);
            int jkmas = ijAPos(j,k + 1, N);
            int jkmenos = ijAPos(j,k - 1, N);
            int jmask = ijAPos((j + 1) % N, k, N);
            int jmenosk = ijAPos((j - 1 + N) % N, k, N);
	        mat(jk, jk) = (1/(double) (r*(double)dR)) - (2/(double) (dR*(double)dR)) - (2/(double) (r*(double)r*(double)dT*(double)dT));           
            mat(jk, jmask) = 1/(double) (r*(double)r*(double)dT*(double)dT);    //Esto esta mal expresado, nos habíamos confundido el orden de los indices y quedó escrito todo al revez. 
            mat(jk, jmenosk) = 1/(double) (r*(double)r*(double)dT*(double)dT);  //Lo solucionamos cambiando las ecuaciones de lugar, por lo que simplemente estan mal puestos los nombres.
            mat(jk, jkmas) = 1/(double) (dR*(double)dR);
            mat(jk, jkmenos) = (1/(double) (dR*(double)dR)) - (1/(double) (r*(double)dR));
}
    }

    for(int i= 0 ; i < N ; i++){             //Identidad en las ultimas N filas
        mat(N*(M+1) - i - 1, N*(M+1) - i - 1) = 1;   
    }
    return mat;
}

heptla< int, int, int, int, int, int, vector< vector< double > > > cargar(string str){	
	char *s = &str[0u];
	ifstream myReadFile;
    myReadFile.open(s);
    int r_i;
	int r_e;
	int mplus1;
	int n;
	int iso;
	int ninst;
	vector< vector< double > > instancias;
    if (myReadFile.is_open()) {
        myReadFile >> r_i;          //cargo r_i
        myReadFile >> r_e;          //cargo r_e    
        myReadFile >> mplus1;		//cargo m+1
        myReadFile >> n;			//cargo n
        myReadFile >> iso;			//cargo iso
        myReadFile >> ninst;
        		//por cada instancia un vector
        for(int k=0 ; k < ninst ; k++ ){			//cargo ninst instacias
	        vector<double> b;
	        double elem;
	        for(int i=0 ; i < n ; i++ ){			//cargo los primeros n valores
	        	myReadFile >> elem;
	        	b.push_back(elem);
	        }
	        int cerosN = n*(mplus1 - 2); 			//cargo n*(m-1) ceros
	        for(int i=0 ; i < cerosN ; i++ ){
	        	b.push_back(0);
	        }
	        for(int i=0 ; i < n ; i++ ){			//cargo los ultimos n valores
	        	myReadFile >> elem;
	        	b.push_back(elem);
	        }
	    	instancias.push_back(b);
	    }
    }
    heptla< int, int, int, int, int, int, vector< vector< double > > > result(r_i, r_e, mplus1, n, iso, ninst, instancias);
	myReadFile.close();
	return result;
}

void guardar(vector< vector< double > > resultados, const char * out){
    ofstream myfile;
    myfile.open (out);
    int ninst = resultados.size();
    if (myfile.is_open()){
        for(int i = 0; i < ninst ; i++){
            int n = resultados[i].size();
            for(int j = 0; j < n ; j++){
                myfile << fixed << resultados[i][j] << endl;
            }
        }
    }   
}

double isoDeTita( vector< double > res, int isom, int angulos, int radioint, double deltaR, int tita){
	int i = tita;
	double radioi = radioint;
	while(res[i] > isom){
		radioi += deltaR;
		i += angulos;
	}
	double ret = ( ( (isom - res[i-angulos]) * deltaR ) /(double) (res[i] - res[i-angulos]) ) + (radioi - deltaR);
	return ret;
}

void isoterma(vector< vector< double > > resultados, int isom, int radioint, double deltaR, int angulos){
	int ninst = resultados.size();
	vector<double> distancias;
	ofstream myfile;
    myfile.open ("isofile2015c");
	if (myfile.is_open()){
		for(int i = 0; i < ninst; i++){
			for (int j = 0; j < angulos; j++){
				double distancia = isoDeTita(resultados[i], isom, angulos, radioint, deltaR, j);
				myfile << fixed << distancia << endl;
			}
		}
	}
}






void coutVector(vector<double> v){
    cout << '[' ;
    for(int i = 0; i < v.size() ; i++){
        cout << v[i] ;
        if(i != v.size() -1 ){
            cout << ", ";
        }
    }
    cout << ']' << endl;
}