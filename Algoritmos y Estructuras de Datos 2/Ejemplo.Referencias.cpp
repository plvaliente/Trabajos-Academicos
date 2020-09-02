#include "iostream"

using namespace std;

int& dame5_ref(){
	int x = 5;
	int *w = &x;
	return *w; //si devuelvo x, da WARNING
}
int& dame5_static(){
	static int x = 5;
	return x;
}
int dame5_val(){
	int x = 5;
	return x; 
}
int main() {
	int& y = dame5_ref();		// 1
	int x = dame5_ref();		// 2
	int& s = y;				    // 3      
	int z = dame5_val();		// 4
	int& a = dame5_static();	// 5 
	int& b = a;					// 6
	int c = dame5_static();		// 7
	int i = 1;
	while (i < 3){
		cout << "RONDA NUMERO: " << i << endl;
		cout << "1. [int& y] El valor es(REF): " << y << endl;
		cout << "1. [int& y] El valor es(MEM): " << &y << endl;
		cout << "---------------------------" << endl;
		cout << "2. [int x] El valor es(REF): " << x << endl;
		cout << "2. [int x] El valor es(MEM): " << &x << endl;
		cout << "---------------------------" << endl;
		cout << "3. [int& s] El valor es(s = y): " << s << endl;
		cout << "3. [int& s] El valor es(MEM): " << &s << endl;
		cout << "---------------------------" << endl;
		cout << "4. [int z] El valor es(VAL): " << z << endl;
		cout << "4. [int z] El valor es(MEM): " << &z << endl;
		cout << "---------------------------" << endl;
		cout << "5. [int& a] El valor es(STATIC): " << a << endl;
		cout << "5. [int& a] El valor es(MEM): " << &a << endl;
		cout << "---------------------------" << endl;
		cout << "6. [int& b] El valor es(b = a): " << b << endl;
		cout << "6. [int& b] El valor es(MEM): " << &b << endl;
		cout << "---------------------------" << endl;
		cout << "7. [int c] El valor es(STATIC): " << c << endl;
		cout << "7. [int c] El valor es(MEM): " << &c << endl;
		cout << "+++++++++++++++++++++++++++" << endl;
		cout << "+++++++++++++++++++++++++++" << endl;
		i++; 
	}
	return 0;
}