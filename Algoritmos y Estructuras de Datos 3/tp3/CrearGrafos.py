import random as rnd
from sets import Set
                       
def grafoCompleto(n,salida):
    # genero 5 grafos completos de mismo tam y pesos random
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    for t in range(1,canttesteos + 1):
        fOut.write(str(n)+ " " + str(n*(n-1)) + '\n')
        for i in range(1,n + 1):
            for j in range(1,n+1):
                if j != i:
                    linea = str(i)+ " " + str(j) 
                    fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def grafoCicloSimple(n,salida):
    # genero 5 grafos que son un unico ciclo simple
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    for t in range(1,canttesteos + 1):
        fOut.write(str(n)+ " " + str(n) + '\n')
        for i in range(1,n + 1):
            j = i+1
            if j > n:
                j = 1
            linea = str(i)+ " " + str(j) 
            fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def grafoRnd(n,salida):
    # 5 grafos random con por lo menos un ciclo
    fOut = open(salida, 'w')
    m = rnd.randint(n, n*(n-1))
    fOut.write(str(n)+ " " + str(m) + '\n')
    k=0
    #me armo una matriz de adyacencias para ver que no repito aristas
    #matriz = [[ 0 for x in range(n)] for y in range(n)]
    matriz = []
    for i in range(n):
        matriz.append([])
        for j in range(n):
            matriz[i].append(None)
            matriz[i][j] = 0
    #armo un ciclo
    for i in range(1,n + 1):
        j = i+1
        if j > n:
            j = 1
        linea = str(i)+ " " + str(j)
        matriz[i-1][j-1]=1
        k = k +1 
        fOut.write(linea + '\n')
    #armo aristas aleatorias viendo que no se repitan
    while k < m:
        for i in range(1,n + 1):
            base = rnd.randint(1,n)
            cant = rnd.randint(1,n)
            tope = rnd.randint(base, min(n, base+cant))   
            for j in range(base, tope):
                if k >= m:
                    j = tope
                    i = n+1
                else:
                    nodoDestino = rnd.randint(base, tope)
                    if matriz[i-1][nodoDestino-1] != 1 and i != nodoDestino:
                        matriz[i-1][nodoDestino-1]=1
                        linea = str(i)+ " " + str(nodoDestino) 
                        fOut.write(linea + '\n')
                        k = k+1

def grafoMaloMalosoGRASP(tamClique,salida):
    gradoAlto = (tamClique * 2) -1
    n = tamClique + tamClique * (tamClique-1) + tamClique * ((2*tamClique)-2)
    m = tamClique*(tamClique-1) + tamClique * (tamClique-1) + tamClique * ((2*tamClique)-2)
    fOut = open(salida, 'w')
    fOut.write(str(n)+ " " + str(m) + '\n')
    for i in range(1,tamClique + 1):
        for j in range(1,tamClique+1):
            if j != i:
                linea = str(i)+ " " + str(j) 
                fOut.write(linea + '\n')
    nodo = tamClique+1
    altosNodos = []
    for i in range(1,tamClique + 1):
        altosNodos.append(nodo)
        for j in range(0,tamClique-1):
            linea = str(i)+ " " + str(nodo) 
            fOut.write(linea + '\n')
            nodo += 1
    for nAlto in altosNodos:
        for i in range(gradoAlto-1):
            linea = str(nAlto)+ " " + str(nodo) 
            fOut.write(linea + '\n')
            nodo+=1 
#blabla
for i in range(10,201):
    out = "./GrafoMM" + str(i)
    grafoMaloMalosoGRASP(i,out)