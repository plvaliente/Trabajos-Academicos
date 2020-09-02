#ifndef ALGORITMOS_H_
#define ALGORITMOS_H_

#include <math.h>

using namespace std;

int altura[1000000];
int padre[1000000];

void init(int n) {
	for(int i=0 ; i < n; i++){
		altura[i] = 1;
		padre[i] = i;
	}
}

int find(int x) {
	if(padre[x] != x){
		padre[x] = find(padre[x]);
	}
	return padre[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if( altura[x] < altura[y]){
		padre[x] = y;
	}
	else{
		padre[y] = x;
	}
	if(altura[x] == altura[y]){
		altura[x]++;
	}
}


struct arista {
	int c1;
	int c2;
	int costo;
	
	bool operator<(const arista a) const
	{
		if (costo != a.costo)
			return costo < a.costo;
		if (c1 != a.c1)
			return c1 < a.c1;
		return c2 < a.c2;
	}
};

std::ostream& dump(std::ostream &o,const arista& a) {
	o << '(' ;
	o << a.c1 << ',' << a.c2 << ',' << a.costo;
	o << ") ";
}

std::ostream& operator << (std::ostream &o, const arista &a){
		return dump(o,a);
}

void coutAristas(vector<arista> v){
    cout << '[' ;
    for(int i = 0; i < v.size() ; i++){
        cout << v[i] ;
        if(i != v.size() -1 ){
            cout << ", ";
        }
    }
    cout << ']' << endl;
}

 int problema3(vector<arista>& aristas, int n, vector<arista>& solucion){

	int gasto = 0;

	init(n);
	sort(aristas.begin(), aristas.end());

	//coutAristas(aristas);
	
	int i = 0;
	int j = 0;
	while(j < n-1){
	//while(i < (n*(n-1))/2){
		if( find(aristas[i].c1) != find(aristas[i].c2) ){
			solucion.push_back(aristas[i]);

			uni(aristas[i].c1, aristas[i].c2);

			//Si la ruta no existia, como la estroy construyendo sumo a gasto el costo de construccion.
			if(aristas[i].costo > 0){
				gasto += aristas[i].costo;
			}
			j++;
		}
		// Si la ruta ya existia, como no me sirve para la solucion sumo el costo de destruccion.
		else if(aristas[i].costo < 0){
				gasto -= aristas[i].costo;
		}
		i++;
		//cout << j << endl;
	}
	//cout << i << endl;
	return gasto;
}



#endif