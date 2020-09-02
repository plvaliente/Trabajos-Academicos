#ifndef MODULO_MATRIZ_H_
#define MODULO_MATRIZ_H_

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Matriz {
    public:
        Matriz(int, int);                                       //Constructor (matriz 0)
        Matriz(const Matriz&);                                  //Constructor por copia
        Matriz(int, int, vector< vector< double > >);
        Matriz& operator =(const Matriz&);                      //Asignación
        double operator()(int, int) const;                      //get
        double& operator()(int, int);                           //set
        void EG();                                              //Eliminación Gaussiana
        void LU();
        friend ostream& operator<<(ostream&, const Matriz&);    
        Matriz operator+(const Matriz&);
        Matriz operator-(const Matriz&);
        Matriz operator*(const Matriz&);
        int filas() const;                                      //Devuelve tamaño de las filas
        int columnas() const;                                   //Devuelve tamaño de las columnas
        void concat(vector<double>);                          	//Concatena un vector en la ultima columna de la matriz
        vector<double> descat();                                //Quita y devuelve la ultima columna de la matriz
        Matriz dameL();                                         //Dada una matriz factorizada con LU devuelve L
        vector<double> resolverTS(vector<double> b);			//Resuelve un sistema triangular superior con vector de resultado b
        vector<double> resolverTI(vector<double> b);			//Resuelve un sistema triangular inferior con vector de resultado b

    private:
        int _filas;
        int _columnas;
        vector< vector< double > > _matriz;
};

Matriz::Matriz(int m, int n){ //matriz R(mxn)
    vector< vector< double > > matriz;
    for (int i = 0 ; i < m ; i++){
        vector< double > fila_i;
        for (int j = 0 ; j < n ; j++){
            fila_i.push_back(0);
        }
        matriz.push_back(fila_i);
    }
    _matriz = matriz;
    _filas = m;
    _columnas = n;
}

Matriz::Matriz(const Matriz& otra){
    *this = otra;
}

Matriz::Matriz(int m, int n, vector< vector< double > > mat){
    _matriz = mat;
    _filas = m;
    _columnas = n;
}

Matriz& Matriz::operator =(const Matriz& otra){
    int m = otra.filas();
    int n = otra.columnas();
    vector< vector< double > > matriz;
    for (int i = 0 ; i < m ; i++){
        vector< double > fila_i;
        for (int j = 0 ; j < n ; j++){
            fila_i.push_back(otra(i,j));
        }
        matriz.push_back(fila_i);
    }
    _matriz = matriz;
    _filas = m;
    _columnas = n;
    return *this;
}

double Matriz::operator()(int x, int y) const{
    return _matriz[x][y];
}

double& Matriz::operator()(int x, int y){
    return _matriz[x][y];
}

void Matriz::EG(){
  int c = columnas();
  int f = filas();
  for (int i = 0; i < f-1; i++){
    for(int j = i+1 ; j < f; j++){
      double multiplicador = _matriz[j][i]/(double)_matriz[i][i];
      for (int k = i ; k < c ; k++){
        _matriz[j][k] = _matriz[j][k] - multiplicador*(double)_matriz[i][k];
      }
    }
  }
}

void Matriz::LU(){
  int c = columnas();
  int f = filas();
  for (int i = 0; i < f-1; i++){
    for(int j = i+1 ; j < f; j++){
      double multiplicador = _matriz[j][i]/(double) _matriz[i][i];
      for (int k = i ; k < c ; k++){
        if(k != i){
            _matriz[j][k] = _matriz[j][k] - multiplicador*(double) _matriz[i][k];
        }
        else{
            _matriz[j][k] = multiplicador;
        }
      }
    }
  }
}


Matriz Matriz::operator+(const Matriz& otra){
    assert ( (otra.columnas() == columnas()) && (otra.filas() == filas()) );
    int col = columnas();
    int fil = filas();
    vector< vector< double > > mat;
    for (int i = 0 ; i < fil ; i++){
        vector< double > fila_i;
        for (int j = 0 ; j < col ; j++){
            double elem = otra(i,j) + _matriz[i][j];
            fila_i.push_back(elem);
        }
        mat.push_back(fila_i);
    }
   return Matriz(fil, col, mat);
}

Matriz Matriz::operator-(const Matriz& otra){
    assert ( (otra.columnas() == columnas()) && (otra.filas() == filas()) );
    int col = columnas();
    int fil = filas();
    vector< vector< double > > mat;
    for (int i = 0 ; i < fil ; i++){
        vector< double > fila_i;
        for (int j = 0 ; j < col ; j++){
            double elem = _matriz[i][j] - otra(i,j);
            fila_i.push_back(elem);
        }
        mat.push_back(fila_i);
    }
   return Matriz(fil, col, mat);
}

Matriz Matriz::operator*(const Matriz& otra){
    assert ( columnas() == otra.filas() );
    int fil_t = filas();
    int col_o = otra.columnas();
    int n = otra.filas(); // = this.columnas()
    vector< vector< double > > mat;
    for (int i=0; i < fil_t; i++){
        vector< double > fila_i;
        for (int j=0; j < col_o; j++){
            double elem = 0;
            for (int k=0; k < n ; k++){
                elem += _matriz[i][k] *(double) otra(k,j);
            }
            fila_i.push_back(elem);
        }
        mat.push_back(fila_i);
    }
    return Matriz(fil_t, col_o, mat);
}


int Matriz::filas() const{
    return _filas;
}

int Matriz::columnas() const{
    return _columnas;
}


ostream& operator<<(ostream& os, const Matriz& mtz){
    int fil = mtz.filas();
    int col = mtz.columnas();
    os << "[ ";
    for( int i = 0; i < fil; ++i) {
        for( int j = 0; j < col; ++j) {
            os << mtz(i,j) ; 
            if (j != col - 1){
                os << ", ";
            }
        }
        if(i != fil - 1){
                os << "; " << endl;
        }
    }
    os << " ]";
    return os;
}

void Matriz::concat(vector<double> v){
    for(int i=0 ; i < _filas ; i++){
        _matriz[i].push_back(v[i]);
    }
    _columnas = _columnas + 1 ;
}

vector<double> Matriz::descat(){
    vector<double> res;
    for(int i=0 ; i < _filas ; i++){
        double vi = _matriz[i].back();
        _matriz[i].pop_back();
        res.push_back(vi);
    }
    _columnas = _columnas - 1 ;
    return res;
}

Matriz Matriz::dameL(){
    Matriz res = Matriz(_filas, _columnas);
    for(int i = 0 ; i < _filas ; i++){
        for (int j = 0 ; j < _columnas ; j++){
            if(i == j){
                res(i,j) = 1;
            }
            else if(i < j){
                res(i,j) = 0;
            }
            else{
                res(i,j) = _matriz[i][j];
            }
        }
    }
    return res;
}

vector<double> Matriz::resolverTS(vector<double> b){
	vector<double> res(_filas, 0);
	for(int i = _filas-1; i>=0; i--){
		double acc = 0;
		for(int j = i+1; j<= _columnas-1; j++){
			acc += _matriz[i][j] *(double) res[j];
        }
		res[i] = (b[i]-acc)/(double) _matriz[i][i];
	}
	
	return res;
}

vector<double> Matriz::resolverTI(vector<double> b){
	vector<double> res(_filas, 0);
	for(int i = 0; i< _filas; i++){
		double acc = 0;
		for(int j = 0; j < i ; j++){
			acc += _matriz[i][j] *(double) res[j];
        }
		res[i] = (b[i]-acc)/(double) _matriz[i][i];
	}
	
	return res;
}


#endif
