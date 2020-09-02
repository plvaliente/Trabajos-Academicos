import random as rnd
from sets import Set
from subprocess import call

def grafoCompletoEj1SinCierreArchivoSINPREMIUM(n, k, pathSalida,limite, cantRep):
    fOut = open(pathSalida, 'w')
    for rep in range(cantRep):
        fOut.write(str(n) + " " + str((n*(n-1))/2 ) + '\n' )
        origen = rnd.randint(1,n)
        destino = rnd.randint(1,n)
        while destino == origen:
            destino = rnd.randint(1,n)
        fOut.write(str(origen) + " " + str(destino) + " " + str(k) + '\n')
        for i in range(1,n + 1):
            for j in range(i,n+1):
                if j != i:
                    linea = str(i)+ " " + str(j) + " " + str(0) + " " + str(rnd.randint(1,limite)) 
                    fOut.write(linea + '\n')
    fOut.write("-1 -1" + '\n')                


pathSalida = "InGrafoCOMP"

valoresN = [5, 7, 10, 12, 15, 17, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80]

for i in range(100,301,20):
    valoresN.append(i)
for i in range(350,1001,50):
    valoresN.append(i)

for i in range(len(valoresN)): 
    grafoCompletoEj1SinCierreArchivoSINPREMIUM(valoresN[i], 0, "InGrafoCOMP",30, 10)
    print(valoresN[i])
    call("./expC")
