#include "AltoHorno.h"
#include <iostream>
#include <ostream>
#include <ctime>
#include <ratio>
#include <chrono>

// para compilar: g++ -std=c++11 -o output test.cpp

using namespace std::chrono;
using namespace std;

void testchico(){
	Matriz m3 = Matriz(3,3);
	m3(2,0)= 12.65;
	m3(2,1)= 5.1;
	m3(2,2)= 8.84;
	m3(0,0)= 98.12;
	m3(0,1)= 684.52;
	m3(0,2)= 0.000145;
	m3(1,0)= 56.516;
	m3(1,1)= 65.111;
	m3(1,2)= 11111;
	cout << m3 << endl;
	m3.EG();
	cout << m3 << endl;
}	


void testEG(){
	int n = 3;
	int m = 11;								// SE ROMPE CUANDO DELTA-R < 1 (Re-Ri < m)
	Matriz m1 = crear(n,m,10,20);

	vector<double> v1;
	int l = 10;
	for(int i = 0; i < n*(m+1) ; i++){

		if( i<n ){
			v1.push_back(1500);
		}
		else if(i >= n && i < n*m){
			v1.push_back(0);
		}
		else{
			v1.push_back(50 + l);
			l = l*(-1);	
		}
	}
	
	cout << m1 << endl << endl; 
	//coutVector(v1);
	m1.concat(v1);
	m1.EG();
	vector<double> v1bis = m1.descat();
	//cout << m1 << endl;
	//coutVector(v1bis);
	vector<double> resEG = m1.resolverTS(v1bis);
	coutVector(resEG);
}

void testLU(){
	int n = 3;
	int m = 11;								// SE ROMPE CUANDO DELTA-R < 1 (Re-Ri < m)
	Matriz m2 = crear(n,m,10,110);

	vector<double> v1;
	int l = 10;
	for(int i = 0; i < n*(m+1) ; i++){

		if( i<n ){
			v1.push_back(1500);
		}
		else if(i >= n && i < n*m){
			v1.push_back(0);
		}
		else{
			v1.push_back(50);
			l = l*(-1);	
		}
	}
	
	m2.LU();
	//cout << m2 << endl;
	Matriz L = m2.dameL();
	//cout << L << endl;
	vector<double> y1 = L.resolverTI(v1) ;
	vector<double> resLU = m2.resolverTS(y1);
	coutVector(resLU);

}

void tTimeLU(int n, int m){
	Matriz m2 = crear(n,m,10,100);
	vector<double> v1;
	for(int i = 0; i < n*(m+1) ; i++){

		if( i<n ){
			v1.push_back(1500);
		}
		else if(i >= n && i < n*m){
			v1.push_back(0);
		}
		else{
			v1.push_back(50);
		}
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	/************A MEDIR***************/
	m2.LU();
	Matriz L = m2.dameL();

	vector<double> y1 = L.resolverTI(v1) ;
	vector<double> resLU = m2.resolverTS(y1);
	/**********************************/
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << fixed;
    std::cout << time_span.count() << std::endl;	
}

void tTimeEG(int n, int m){
	Matriz m2 = crear(n,m,10,100);
	vector<double> v1;
	for(int i = 0; i < n*(m+1) ; i++){

		if( i<n ){
			v1.push_back(1500);
		}
		else if(i >= n && i < n*m){
			v1.push_back(0);
		}
		else{
			v1.push_back(50);
		}
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	/************A MEDIR***************/
	m2.concat(v1);
	m2.EG();
	vector<double> v1bis = m2.descat();
	vector<double> resEG = m2.resolverTS(v1bis);
	/**********************************/
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << fixed;
    std::cout << time_span.count() << std::endl;	
}

void tInsTimeEG(int n, int m, int inst){
	high_resolution_clock::time_point tinit = high_resolution_clock::now();
	duration<double> time_acc = duration_cast<duration<double>>(tinit - tinit);
	for(int i = 0; i < inst ; i++){
		Matriz m2 = crear(n,m,10,100);
		vector<double> v1;
		for(int j = 0; j < n*(m+1) ; j++){

			if( j<n ){
				v1.push_back(1500);
			}
			else if(j >= n && j < n*m){
				v1.push_back(0);
			}
			else{
				v1.push_back(rand() % 100);
			}
		}
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		/************A MEDIR***************/
		m2.concat(v1);
		m2.EG();
		vector<double> v1bis = m2.descat();
		vector<double> resEG = m2.resolverTS(v1bis);
		/**********************************/
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
	    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	    time_acc += time_span;
	}
	std::cout << fixed;
	std::cout << time_acc.count() << std::endl;   
}

void tPaCadaInsFIJATimeEG(int n, int m, int inst){
	for(int i = 0; i < inst ; i++){
		Matriz m2 = crear(n,m,10,100);
		vector<double> v1;
		for(int j = 0; j < n*(m+1) ; j++){

			if( j<n ){
				v1.push_back(1500);
			}
			else if(j >= n && j < n*m){
				v1.push_back(0);
			}
			else{
				v1.push_back(rand() % 100);
			}
		}
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		/************A MEDIR***************/
		m2.concat(v1);
		m2.EG();
		vector<double> v1bis = m2.descat();
		vector<double> resEG = m2.resolverTS(v1bis);
		/**********************************/
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
	    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	    std::cout << fixed;
		std::cout << time_span.count() << std::endl;
	}
   
}

void tInsTimeLU(int n, int m, int inst){
	Matriz m1 = crear(n,m,10,100);
	vector<double> v1;
	high_resolution_clock::time_point tinit = high_resolution_clock::now();
	/************A MEDIR***************/
	m1.LU();
	Matriz L = m1.dameL();	
	/**********************************/
	high_resolution_clock::time_point tLU = high_resolution_clock::now();
	duration<double> time_acc = duration_cast<duration<double>>(tLU - tinit);
	for(int i = 0; i < inst ; i++){	
		for(int j = 0; j < n*(m+1) ; j++){

			if( j<n ){
				v1.push_back(1500);
			}
			else if(j >= n && j < n*m){
				v1.push_back(0);
			}
			else{
				v1.push_back(rand() % 100);
			}
		}
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		/************A MEDIR***************/
		vector<double> y1 = L.resolverTI(v1) ;
		vector<double> resLU = m1.resolverTS(y1);
		/**********************************/
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
	    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	    time_acc += time_span;
	}
	std::cout << fixed;
	std::cout << time_acc.count() << std::endl;   
}

void tPaCadaInsFIJATimeLU(int n, int m, int inst){
	Matriz m1 = crear(n,m,10,100);
	vector<double> v1;
	high_resolution_clock::time_point tinit = high_resolution_clock::now();
	/************A MEDIR***************/
	m1.LU();
	Matriz L = m1.dameL();	
	/**********************************/
	high_resolution_clock::time_point tLU = high_resolution_clock::now();
	duration<double> time_acc = duration_cast<duration<double>>(tLU - tinit);
	for(int i = 0; i < inst ; i++){	
		for(int j = 0; j < n*(m+1) ; j++){

			if( j<n ){
				v1.push_back(1500);
			}
			else if(j >= n && j < n*m){
				v1.push_back(0);
			}
			else{
				v1.push_back(rand() % 100);
			}
		}
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		/************A MEDIR***************/
		vector<double> y1 = L.resolverTI(v1) ;
		vector<double> resLU = m1.resolverTS(y1);
		/**********************************/
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
	    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	    time_acc += time_span;
		if(i == 0){	
			std::cout << fixed;
			std::cout << time_acc.count() << std::endl;
		}
		else{
			std::cout << fixed;
			std::cout << time_span.count() << std::endl;
		}	   
	}
}

vector<double> GenVector(int n, int m){
	vector<double> v1;
	for(int j = 0; j < n*(m+1) ; j++){

		if( j<n ){
			v1.push_back(1500);
		}
		else if(j >= n && j < n*m){
			v1.push_back(0);
		}
		else{
			v1.push_back(rand() % 100);
		}
	}
	return v1;
}

void ResVcEG(int n,int m, vector<double> v, string s){
	const char* out = s.c_str(); 
	Matriz mEG = crear(n,m,10,100);
	mEG.concat(v);
	mEG.EG();
	vector<double> vbis = mEG.descat();
	vector<double> resEG = mEG.resolverTS(vbis);
    ofstream myfile;
    myfile.open(out);
    if (myfile.is_open()){
    	myfile << fixed;
    	myfile << '[' ;
    	for(int i = 0; i < resEG.size() ; i++){
        	myfile << resEG[i] ;
        	if(i != resEG.size() -1 ){
           		myfile << ", ";
        	}
    	}
		myfile << ']' << endl;
	}
}

void ResVcLU(Matriz L, Matriz U, vector<double> v, string s){
	const char* out = s.c_str();
	vector<double> y = L.resolverTI(v) ;
	vector<double> resLU = U.resolverTS(y);
    ofstream myfile;
    myfile.open(out);
    if (myfile.is_open()){
    	myfile << fixed;
    	myfile << '[' ;
    	for(int i = 0; i < resLU.size() ; i++){
        	myfile << resLU[i] ;
        	if(i != resLU.size() -1 ){
           		myfile << ", ";
        	}
    	}
		myfile << ']' << endl;
	}
}

void ErrorGenerator(int n, int m){
	char* name0 = "v0";
	vector<double> v0 = GenVector(n,m);
    ofstream myfile0;
    myfile0.open(name0);
    if (myfile0.is_open()){
    	myfile0 << fixed;
    	myfile0 << '[' ;
    	for(int i = 0; i < v0.size() ; i++){
        	myfile0 << v0[i] ;
        	if(i != v0.size() -1 ){
           		myfile0 << ", ";
        	}
    	}
		myfile0 << ']' << endl;
	}
	char* name1 = "v1";
	vector<double> v1 = GenVector(n,m);
    ofstream myfile1;
    myfile1.open(name1);
    if (myfile1.is_open()){
    	myfile1 << fixed;
    	myfile1 << '[' ;
    	for(int i = 0; i < v1.size() ; i++){
        	myfile1 << v1[i] ;
        	if(i != v1.size() -1 ){
           		myfile1 << ", ";
        	}
    	}
		myfile1 << ']' << endl;
	}
	char* name2 = "v2";
	vector<double> v2 = GenVector(n,m);
    ofstream myfile2;
    myfile2.open(name2);
    if (myfile2.is_open()){
    	myfile2 << fixed;
    	myfile2 << '[' ;
    	for(int i = 0; i < v2.size() ; i++){
        	myfile2 << v2[i] ;
        	if(i != v2.size() -1 ){
           		myfile2 << ", ";
        	}
    	}
		myfile2 << ']' << endl;
	}
	char* name3 = "v3";
	vector<double> v3 = GenVector(n,m);
    ofstream myfile3;
    myfile3.open(name3);
    if (myfile3.is_open()){
    	myfile3 << fixed;
    	myfile3 << '[' ;
    	for(int i = 0; i < v3.size() ; i++){
        	myfile3 << v3[i] ;
        	if(i != v3.size() -1 ){
           		myfile3 << ", ";
        	}
    	}
		myfile3 << ']' << endl;
	}
	char* name4 = "v4";
	vector<double> v4 = GenVector(n,m);
    ofstream myfile4;
    myfile4.open(name4);
    if (myfile4.is_open()){
    	myfile4 << fixed;
    	myfile4 << '[' ;
    	for(int i = 0; i < v4.size() ; i++){
        	myfile4 << v4[i] ;
        	if(i != v4.size() -1 ){
           		myfile4 << ", ";
        	}
    	}
		myfile4 << ']' << endl;
	}
////////////////////////////////
	char* out; 
	Matriz mLU = crear(n,m,10,100);
	cout << fixed << mLU;
	mLU.LU();
	Matriz L = mLU.dameL();

	ResVcEG(n, m, v0, "R0EG");
	ResVcEG(n, m, v1, "R1EG");
	ResVcEG(n, m, v2, "R2EG");
	ResVcEG(n, m, v3, "R3EG");
	ResVcEG(n, m, v4, "R4EG");

	ResVcLU(L, mLU, v0, "R0LU");
	ResVcLU(L, mLU, v1, "R1LU");
	ResVcLU(L, mLU, v2, "R2LU");
	ResVcLU(L, mLU, v3, "R3LU");
	ResVcLU(L, mLU, v4, "R4LU");	
		
}

void testiso(){
	vector< double > vec;
	vec.push_back(600);
	vec.push_back(600);
	vec.push_back(600);
	vec.push_back(550);
	vec.push_back(550);
	vec.push_back(550);
	vec.push_back(450);
	vec.push_back(450);
	vec.push_back(450);
	vec.push_back(350);
	vec.push_back(350);
	vec.push_back(350);

	int metros = isoDeTita(vec, 500, 3, 50, 10, 2);
	cout << "Deberia dar 65. Da: " << metros << endl;
}

int main(){

	//cout << m1 << endl;
	//cout << endl;

	//testchico();
	//testEG();
	//testLU();
	//testiso();

	/*****DE 3*3 A 40*40*LU**/
	/*
	int n = 40;
	for(int i = 3; i <= n ; i++){
		tTimeLU(i, i);
	}
	*/
	/************************/

	/*****DE 3*3 A 40*40*EG**/
	/*
	int n = 40;
	for(int i = 3; i <= n ; i++){
		tTimeEG(i, i);
	}
	*/
	/************************/	

	/*****DE 30*30 - 1 a 25 instancias LU**/
	//devuelve un vector(COUT) con lo que tarda en resolver
	// un sistema de posicion instancias
	/*
	int n = 25;
	for(int i = 1; i <= n ; i++){
		tInsTimeLU(30,30,i);
	}
	*/
	/************************/

	/*****DE 30*30 - 1 a 25 instancias EG**/
	//devuelve un vector(COUT) con lo que tarda en resolver
	// un sistema de posicion instancias
	/*
	int n = 25;
	for(int i = 1; i <= n ; i++){
		tInsTimeEG(30,30,i);
	}
	*/
	/************************/

	/*****DE 30*30 - 10 instancias EG**/
	//devuelve un vector(COUT) con lo que tarda en resolver la
	// instancia posicion para un numero i de instancias
	/*
	tPaCadaInsFIJATimeEG(30,30,10);
	*/
	/************************/

	/*****DE 30*30 - 10 instancias LU**/
	//devuelve un vector(COUT) con lo que tarda en resolver la
	// instancia posicion para un numero i de instancias
	/*
	tPaCadaInsFIJATimeLU(30,30,10);
	*/
	/************************/

	//ErrorGenerator(5, 5);
	
	return 0;
}