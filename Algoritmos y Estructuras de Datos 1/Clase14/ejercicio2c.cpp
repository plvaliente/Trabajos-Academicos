#include <vector>
using namespace std;
int suma (vector<int> v , int i) ;
vector<int> ejercicio2c(vector<int> &xs){
  int i = 0;
  int n = xs.size();
  vector<int> res(n);
  while(i<n){
//    if(i<0 || i>n) NOCUMPLEINV("2c"); // Comentar para probar tiempos
    //******************* Completar desde aca
// I : 0 ≤ i ≤ n ∧ (∀ j ← [0..i)) res[j] == suma(xs_[j..|xs|) )
    res.at(i) = suma(xs, i) ;   
    i++ ;
    //******************* hasta aca
//    if(i<0 || i>n) NOCUMPLEINV("2c"); // Comentar para probar tiempos
  }
  return res;
}

int suma (vector<int> v , int i){
  int res = 0 ;
  for(int k = i ; k < v.size() ; k++ ){
    res += v.at(k) ;
  } 
  return res ;
}