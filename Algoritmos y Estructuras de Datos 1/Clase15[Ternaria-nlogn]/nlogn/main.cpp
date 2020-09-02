#include <iostream>
#include <fstream> 
#include <math.h>

using namespace std;

int binNln(double c , double t) ;

int main() {
// cout << "ingresa" << endl ;
// ifstream arch ("nlogn1.in") ; 
double c ; 
double t ;
string file ;
cout << "Ingresa Prueba" << endl ;
cin >> file ;
ifstream myfile( file.c_str()); 
myfile >> c ;
myfile >> t ;
cout << fixed ;
cout << "Resultado:" << binNln(c , t) << endl ;
// cout << "Check: " << res << endl ;	
    return 0;
}

int binNln(double c , double t){
    long int inf = 0 ;
    long int sup = t/c + 5 ;
    long int mid ; 
    while (inf + 1 != sup){
        mid = inf + (sup - inf)/2 ; 
        if ( c*mid*log(mid) <= t ){
            inf = mid ;
        }
        else {
            sup = mid ; 
        }
    }
    return inf ;    
}