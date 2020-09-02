#include <vector>
using namespace std;
#define NOCUMPLEINV(s) { cout << " No cumple Inv ej " <<  s << endl; exit(-1); }
void ejercicio2b(vector<int> &xs){
  int i = 0;
  int n = xs.size();
  vector<int> prexs = xs; // Comentar para probar tiempos
  while(i<n){
    // if(i<0 || i>n+1) NOCUMPLEINV("2b"); // Comentar para probar tiempos
    // if(i%2!=0)  NOCUMPLEINV("2b"); // Comentar para probar tiempos
    // for(int _i = 0; _i < i; _i++) if(_i%2==0 && xs[_i]!=0) NOCUMPLEINV("2b");// Comentar para probar tiempos
    // for(int _i = 0; _i < i; _i++) if(_i%2==1 && xs[_i]!=-prexs[_i]) NOCUMPLEINV("2b");// Comentar para probar tiempos
    // for(int _i = i; _i < n; _i++) if(xs[_i]!=prexs[_i]) NOCUMPLEINV("2b"); // Comentar para probar tiempos
    //******************
// I : 0 ≤ i ≤ n + 1 ∧ i mod 2 == 0 ∧ (∀j ← [0..i)) if j mod 2 == 0 then xs[j] == 0 else xs[j] == −pre(xs) j ∧ (∀j ←[i..n))xs[j] == pre(xs)
      xs.at(i) = 0 ;
    if(i+1 < n){ 
      xs.at(i+1) = -xs.at(i+1) ;
    }
    i += 2 ;
    //*******************
    // if(i<0 || i>n+1) NOCUMPLEINV("2b");// Comentar para probar tiempos
    // if(i%2!=0)  NOCUMPLEINV("2b");// Comentar para probar tiempos
    // for(int _i = 0; _i < min(i,n); _i++) if(_i%2==0 && xs[_i]!=0) NOCUMPLEINV("2bf");// Comentar para probar tiempos
    // for(int _i = 0; _i < min(i,n); _i++) if(_i%2==1 && xs[_i]!=-prexs[_i]) NOCUMPLEINV("2ba"); // Comentar para probar tiempos
    // for(int _i = i; _i < n; _i++) if(xs[_i]!=prexs[_i]) NOCUMPLEINV("2b"); // Comentar para probar tiempos
  }
}

