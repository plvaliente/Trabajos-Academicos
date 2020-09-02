#include <vector>
using namespace std;

int ejercicio1b(vector<int> &xs,int k){
  
  int i= 0;
  int res = 0;
  // PC: i = 0 & res = 0 
  while(i < (int) xs.size()){
  // I : 0 <= i < |xs| & res = suma([ xs[j] div 2 − k | j ← [0..i] ])	
    int aux = xs[i]/2 - k  ;
    res = res + aux ;  
    i++ ;  
  }
 // QC: suma([ x div 2 − k | x ← xs ])
  return res;
}
