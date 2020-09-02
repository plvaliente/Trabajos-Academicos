#include <vector>
using namespace std;

int ejercicio1a(vector<int> &xs, vector<int> &pos){
  
  int res = 0;
  int i  = 0;
  int cantidad = 0;
  // PC: res = 0 & i = 0 & cantidad = 0 & (∀p ← pos)0 ≤ p < |xs|
  while(cantidad < (int) pos.size()){
  // I: 0 <= i < |xs| & 0 <= cantidad <= |pos| &
  // res == suma([ (j + 1)*xs[pos_j] | j ← [0..cantidad) ])
     i = pos[cantidad];
     res += (cantidad+1) * xs[i];
     cantidad++;
  }

  return res;
}
// Qc: res == suma( [ (c + 1)*xs[pos_c] | c ← [0..|pos|) ] )
