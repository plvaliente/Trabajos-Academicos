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

def grafoCompletoEj1(n, k, pathSalida,limite):
    fOut = open(pathSalida, 'w')
    fOut.write(str(n) + " " + str((n*(n-1))/2 ) + '\n' )
    origen = rnd.randint(1,n)
    destino = rnd.randint(1,n)
    while destino == origen:
        destino = rnd.randint(1,n)
    fOut.write(str(origen) + " " + str(destino) + " " + str(k) + '\n')
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
    fOut = open(salida, 'w')
    for i in range(1,n + 1):
        for j in range(1,n+1):
            if j != i:
                linea = str(i)+ " " + str(j) + " " + str(rnd.randint(1,limite)) 
                fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def grafoRndEj2(n,salida,limite):
    # del nodo 1 se llega a todos y los demas nodos tienen ejes random
    fOut = open(salida, 'w')
    for i in range(2,n + 1):
        linea = str(1)+ " " + str(i) + " " + str(rnd.randint(1,limite)) 
        fOut.write(linea + '\n')
    for i in range(2,n + 1):
        base = rnd.randint(1,n)
        cant = rnd.randint(1,n)
        tope = rnd.randint(base, max(n+1, base+cant))   
        usados = Set()
        for j in range(base, tope):
            nodoDestino = rnd.randint(base, tope)
            if nodoDestino not in usados:
                usados.add(j)
                linea = str(i)+ " " + str(nodoDestino) + " " + str(rnd.randint(1,limite)) 
                fOut.write(linea + '\n')
    fOut.write("-1 -1"+'\n')

def grafoCompletoEj1SinCierreArchivo(n, k, pathSalida,limite):
    fOut = open(pathSalida, 'a')
    fOut.write(str(n) + " " + str((n*(n-1))/2 ) + '\n' )
    origen = rnd.randint(1,n)
    destino = rnd.randint(1,n)
    while destino == origen:
        destino = rnd.randint(1,n)
    fOut.write(str(origen) + " " + str(destino) + " " + str(k) + '\n')
    for i in range(1,n + 1):
        for j in range(i,n+1):
            if j != i:
                p = 1
                if rnd.randint(0,2) <= 1:
                    p = 0
                linea = str(i)+ " " + str(j) + " " + str(p) + " " + str(rnd.randint(1,limite)) 
                fOut.write(linea + '\n')

#blabla

def exp1Prob1():



    valoresN = [1024, 512, 256, 128, 64, 32]
    valoresK = [0, 1, 3, 7, 15, 31]

    limite = 15
    pathSalida = "Problema1/expIgualNxK"

    cantRepeticiones = 20

    for i in range(len(valoresK)):

        for rep in range(20):
            grafoCompletoEj1SinCierreArchivo(valoresN[i], valoresK[i], pathSalida,limite)

    f = open(pathSalida, 'a')
    f.write("-1 -1" + '\n')


exp1Prob1()