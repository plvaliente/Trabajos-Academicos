#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "ejercicio1a.cpp"
#include "ejercicio1b.cpp"
#include "ejercicio2a.cpp"
#include "ejercicio2b.cpp"
#include "ejercicio2c.cpp"
#include "ejercicio2d.cpp"
#include <sys/time.h>

using namespace std;


int main(){

  vector<int> data;
  vector<int> ids;
  int i;
  
  
  data.push_back(8);
  data.push_back(1);
  data.push_back(3);
  data.push_back(4);
  
  ids.push_back(2);
  ids.push_back(1);
  ids.push_back(3);

  cout << "Ejercicio 1a " << endl;
  cout <<  "Resultado esperado: 17   Resultado obtenido: " << ejercicio1a(data,ids) << endl;
  data.push_back(15);
  ids.push_back(3);
  ids.push_back(0);
  ids.push_back(3);
  ids.push_back(1);
  ids.push_back(3);
  ids.push_back(2);
  ids.push_back(3);

  cout <<  "Resultado esperado: 203  Resultado obtenido: " << ejercicio1a(data,ids) << endl;

  
  data.clear();
  data.push_back(11); 
  data.push_back(12); 
  data.push_back(13); 
  
  cout << "Ejercicio 1b " << endl;
  cout <<  "Resultado esperado: 2   Resultado obtenido: " << ejercicio1b(data,5) << endl;
  cout <<  "Resultado esperado: -4  Resultado obtenido: " << ejercicio1b(data,7) << endl;
  
  
  
  data.clear();
  data.push_back(1);
  data.push_back(5);
  data.push_back(2);
  data.push_back(4);
  data.push_back(1);
  
  ejercicio2a(data);
  cout << "Ejercicio 2a " << endl;
  cout << "Resultado esperado: [0,-5,0,-4,0] Resultado obtenido: ";
  for(i=0;i<data.size();i++) cout <<(i?',':'[') << data[i];
  cout << "]" << endl;
  
  data.clear();
  data.push_back(1);
  data.push_back(5);
  data.push_back(2);
  data.push_back(4);
  data.push_back(1);
  
  ejercicio2b(data);
  cout << "Ejercicio 2b " << endl;
  cout << "Resultado esperado: [0,-5,0,-4,0] Resultado obtenido: ";
  for(i=0;i<data.size();i++) cout <<(i?',':'[') << data[i];
  cout << "]" << endl;
  
  
  cout << "Ejercicio 2c " << endl;
  
  data.clear();
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  
  data = ejercicio2c(data);
  cout << "Resultado esperado: [10,9,7,4] Resultado obtenido: ";
  for(i=0;i<data.size();i++) cout <<(i?',':'[') << data[i];
  cout << "]" << endl;
  
  
  data.clear();
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data = ejercicio2d(data);
  cout << "Ejercicio 2d " << endl;
  cout << "Resultado esperado: [10,9,7,4] Resultado obtenido: ";
  for(i=0;i<data.size();i++) cout <<(i?',':'[') << data[i];
  cout << "]" << endl;
  
  
  
  int casos = 10000;
  int sem = 34;
  data.push_back(sem);
  for(i=0;i<casos-1;i++) data.push_back((data.back()*7)%50);
  
  
  
  
  timeval tbeg;
  timeval tend;
  gettimeofday(&tbeg, NULL);
  ejercicio2a(data);
  gettimeofday(&tend, NULL);
  
  cout << "Tiempo ej2a " << (tend.tv_sec - tbeg.tv_sec) * 1000000 + (tend.tv_usec - tbeg.tv_usec) << endl;
  
  gettimeofday(&tbeg, NULL);
  ejercicio2b(data);
  gettimeofday(&tend, NULL);
  
  cout << "Tiempo ej2b " << (tend.tv_sec - tbeg.tv_sec) * 1000000 + (tend.tv_usec - tbeg.tv_usec) << endl;
  
  
  
  gettimeofday(&tbeg, NULL);
  ejercicio2c(data);
  gettimeofday(&tend, NULL);
  
  cout << "Tiempo ej2c " << (tend.tv_sec - tbeg.tv_sec) * 1000000 + (tend.tv_usec - tbeg.tv_usec) << endl;
  
  gettimeofday(&tbeg, NULL);
  ejercicio2d(data);
  gettimeofday(&tend, NULL);
  
  cout << "Tiempo ej2d " << (tend.tv_sec - tbeg.tv_sec) * 1000000 + (tend.tv_usec - tbeg.tv_usec) << endl;
  
  
  
  
  
  
  
  return 0;
}
