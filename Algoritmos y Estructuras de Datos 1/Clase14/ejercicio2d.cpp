#include <vector>
using namespace std;
vector<int> ejercicio2d(vector<int> &xs){
  int n = xs.size();
  int i = n;
  vector<int> res(n); // res tiene tamaño n
  int acum = 0 ; 
  while(i>=1){
//    if(i<0 || i>n) NOCUMPLEINV("2d"); // Comentar para probar tiempos
    //******************* Completar desde aca
 //  I : 0 ≤ i ≤ n ∧ (∀j ← (i..n)) res[j] == suma( xs_[j..|xs|) )  
    res.at(i-1) = xs.at(i-1) + acum ;   
    acum += xs.at(i-1) ;
    i-- ;
    //******************* hasta aca
//    if(i<0 || i>n) NOCUMPLEINV("2d"); // Comentar para probar tiempos
  }
  return res;
}