#include <algorithm>
#include <stdio.h>
#include <vector>
#include <limits>
#include <math.h>

using namespace std;

#define infinito std::numeric_limits<int>::max()

struct arista {
    int c1;
    int c2;
    int costo;
    
    bool operator<(const arista a) const
    {
        if (costo != a.costo)
            return costo < a.costo;
        if (c1 != a.c1)
            return c1 < a.c1;
        return c2 < a.c2;
    }
};


void copiargrafoyrestar(arista Origen [], arista Destino[], int c, int m){
    
    //Copia el contenido de la matriz y le resta c a todos los pesos//
    for(int i=0; i<m; i++){
        Destino[i].c1 = Origen[i].c1;
        Destino[i].c2 = Origen[i].c2;
        Destino[i].costo = Origen[i].costo -c;
    }
}

bool HayCicloNegativo(arista G[], int n, int m, int v){


    //Creo un arreglo donde voy a guardar la distancia de mi nodo v al nodo i
    //Dado que no existe el nodo 0, creo un arreglo de tamaño n+1 para ver los nodos 1 a n e ignoro la posición 0
    long int caminos[n+1];
    for(int i = 1; i<n+1; i++){
        caminos[i] = infinito;
    }
    caminos[v]=0;


    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<m; j++){
            if(G[j].c2 != v && caminos[G[j].c1] != infinito){
                caminos[G[j].c2]= min(caminos[G[j].c2], caminos[G[j].c1] + G[j].costo);
            }
        }
    }

    //Quiero ver si hay caminos negativos, hago una iteracion más y veo si cambiaron mis caminos
    //uso long int para que no se produzca overflow en la suma
    long int caminosaux[n+1];
    //Copio los caminos minimos a un auxiliar
    for(int i = 0; i<n+1; i++){
        caminosaux[i] = caminos[i];
    }


    for(int j = 0; j<m; j++){
        if(G[j].c2 != v){
            caminos[G[j].c2]= min(caminos[G[j].c2], caminos[G[j].c1] + G[j].costo);
        }
    }

    bool cambiocamino = false;
    for(int i=1; i<n+1; i++){
        cambiocamino = cambiocamino || (caminos[i] != caminosaux[i]);
    }

    //printf("cambiocamino %d\n", cambiocamino);
    return cambiocamino;
}

int maximaRebaja(int n, int m, arista GOrig[]){


    //leer todos los parametros
    //Voy a obtener:
    //n = cantidad de nodos
    //m= cantidad de aristas
    //GOrig= arreglo de m aristas con sus pesos

    //Voy a agregar un nodo dirigido a todos los otros nodos asi me aseguro que es conexo con peso 0 en sus aristas
    //Para ello necesito un nuevo arreglo de aristas

    //agrego un nodo
    n++;
    //agrego n-1 aristas
    int morig = m;
    m = m + n-1;

    arista G [m];

    for(int j =0; j<morig; j++){
        G[j]=GOrig[j];
    }

    for(int k=morig; k<m; k++){
            G[k].costo= 0;
            G[k].c1= n;
            G[k].c2= m - k; 
    }




    //primero voy a buscar quien es "C", o sea el mayor costo de un peaje

    int c = G[0].costo;

    for(int i = 1; i<m; i++){
        c = max(G[i].costo, c);
    }


    //voy a hacer búsqueda binaria viendo el maximo "c" que no me genera ciclos negativos

    bool loencontre = false;
    int cup = c;
    //cdown guarda el máximo valor que encontre hasta el momento tal que no genera ciclos negativos//
    int cdown = 0;

    int ccentr;

    //*Me genero una matriz auxiliar para no modificar G*//
    arista GAux[m];
    bool MeSirveC;
    bool MeSirveCProx;

    /*Primero veo si c es mi solución*/
    copiargrafoyrestar(G, GAux, cup, m);
    MeSirveC = !(HayCicloNegativo(GAux, n, m, n));

    if(!MeSirveC){

        //si no me sirve arranco la busqueda binaria entre 0 y c
        cup--;

        while(cup != cdown && !loencontre){
            //Veo si funciona para Cup y para Cup + 1
            copiargrafoyrestar(G, GAux, cup, m);
            MeSirveC = !(HayCicloNegativo(GAux, n, m, n));
            copiargrafoyrestar(G, GAux, cup + 1, m);
            MeSirveCProx = !(HayCicloNegativo(GAux, n, m, n));


            //guardo el medio entre cup y cdown
            ccentr = (cup + cdown) / 2;

            if(MeSirveC){
                if(!MeSirveCProx){
                    //*Encontre mi valor máximo posible de C*//
                    loencontre = true;
                }else{
                    ccentr = cup;
                    cup = cup + ((cup-cdown) / 2 + 1);
                    cdown = ccentr + 1;
                }
            }else{
                cup = ccentr;
            }
        }

    }

    return cup;

}

