#include <iostream>
#include <fstream> 
#include <math.h>

using namespace std;

double ternaria(double x1 , double y1 , double x2 , double y2 ) ;
double distancia(double mid , double x1 , double y1 , double x2 , double y2 ) ;

int main() { 
double x1 ;
double y1 ;
double x2 ; 
double y2 ;
string file ;
cout << "Ingresa Prueba" << endl ;
cin >> file ;
ifstream myfile( file.c_str()); 
myfile >> x1 ;
myfile >> y1 ;
myfile >> x2 ;
myfile >> y2 ;
cout << fixed ;
cout << "Resultado:" << ternaria( x1 , y1 , x2 , y2 ) << endl ;

    return 0;
}


double ternaria(double x1 , double y1 , double x2 , double y2 ){
    double inf = x1 ;
    double sup = x2 ;
    double mid1 = inf + (sup - inf) / 3 ;
    double mid2 = inf + ((sup - inf) * 2) / 3 ; 
    while (mid2 - mid1 < .01){
        if ( distancia(mid1, x1 , y1 , x2 , y2 ) <= distancia( mid2 , x1 , y1 , x2 , y2 ) ){
            sup = mid2 ;
            mid2 = inf + (sup - inf) * 2 / 3; 
        }
        else {
            inf = mid1 ; 
            mid1 = inf + (sup - inf) / 3 ;
        }
    }
    return distancia(mid1, x1 , y1 , x2 , y2 ) ;    
}

double distancia(double mid , double x1 , double y1 , double x2 , double y2 ){
    double res = sqrt((x1-mid)*(x1-mid)+(y1)*(y1)) + sqrt((x2-mid)*(x2-mid)+(y2)*(y2)) ;
    return res ;    
}