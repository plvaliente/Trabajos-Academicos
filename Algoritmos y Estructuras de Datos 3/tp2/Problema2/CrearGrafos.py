import random as rnd
from sets import Set


def grafoCompletoEj3(n,salida,limite):
    fOut = open(salida, 'w')
    for i in range(1,n + 1):
        for j in range(i,n+1):
            if j != i:
                linea = str(i)+ " " + str(j) + " " + str(rnd.randint(0,1)) + " " + str(rnd.randint(1,limite)) 
                fOut.write(linea + '\n')
    fOut.write("-1"+'\n')           

def grafoCompletoEj1(n,salida,limite):
    fOut = open(salida, 'w')
    for i in range(1,n + 1):
        for j in range(i,n+1):
            if j != i:
                p = 1
                if rnd.randint(0,2) <= 1:
                    p = 0
                linea = str(i)+ " " + str(j) + " " + str(p) + " " + str(rnd.randint(1,limite)) 
                fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')                        

def grafoCompletoEj2(n,salida,limite):
    # genero 5 grafos completos de mismo tam y pesos random
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    for t in range(1,canttesteos + 1):
        fOut.write(str(n)+ " " + str(n*(n-1)) + '\n')
        for i in range(1,n + 1):
            for j in range(1,n+1):
                if j != i:
                    linea = str(i)+ " " + str(j) + " " + str(rnd.randint(1,limite)) 
                    fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def grafoCicloSimple(n,salida,limite):
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
            linea = str(i)+ " " + str(j) + " " + str(rnd.randint(1,limite)) 
            fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def grafoRndEj2(n,salida,limite):
    # 5 grafos random con por lo menos un ciclo
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    #por lo menos tiene que haber un ciclo y ser "conexo" asi que el minimo es m aristas
    m = rnd.randint(n, n*(n-1))
    for t in range(1,canttesteos + 1):
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
            linea = str(i)+ " " + str(j) + " " + str(rnd.randint(1,limite))
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
                            linea = str(i)+ " " + str(nodoDestino) + " " + str(rnd.randint(1,limite)) 
                            fOut.write(linea + '\n')
                            k = k+1
    fOut.write("-1 -1"+'\n')

def grafoCompletoMejorCasoC(n,salida,limite):
    # genero 5 grafos completos de mismo tam y pesos fijo
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    for t in range(1,canttesteos + 1):
        fOut.write(str(n)+ " " + str(n*(n-1)) + '\n')
        for i in range(1,n + 1):
            for j in range(1,n+1):
                if j != i:
                    linea = str(i)+ " " + str(j) + " " + str(limite) 
                    fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def grafoCompletoPeorCasoC(n,salida,limite):
    # genero 5 grafos completos de mismo tam y un nodo con peso limite y el resto 1
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    for t in range(1,canttesteos + 1):
        fOut.write(str(n)+ " " + str(n*(n-1)) + '\n')
        for j in range(2, n+1):
            linea = str(1)+ " " + str(j) + " " + str(limite) 
            fOut.write(linea + '\n')
        for i in range(2,n + 1):
            for j in range(1,n+1):
                if j != i:
                    linea = str(i)+ " " + str(j) + " " + str(1) 
                    fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def CicloSimpleMejorCaso(n,salida,limite):
    # genero 5 grafos que son un unico ciclo simple y peso fijo
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    for t in range(1,canttesteos + 1):
        fOut.write(str(n)+ " " + str(n) + '\n')
        for i in range(1,n + 1):
            j = i+1
            if j > n:
                j = 1
            linea = str(i)+ " " + str(j) + " " + str(limite)
            fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def CicloSimplePeorCaso(n,salida,limite):
    # genero 5 grafos que son dos ciclos simples y con unos nodos de peso limite y el resto 1
    canttesteos = 5
    fOut = open(salida, 'w')
    fOut.write(str(canttesteos) + '\n')
    for t in range(1,canttesteos + 1):
        fOut.write(str(n)+ " " + str(n+1) + '\n')
        for i in range(1,4):
            j = i+1
            if j == 4:
                j = 1
            linea = str(i)+ " " + str(j) + " " + str(limite)
            fOut.write(linea + '\n')
        for i in range(3,n + 1):
            j = i+1
            if j > n:
                j = 3
            linea = str(i)+ " " + str(j) + " " + str(1)
            fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

#blabla
