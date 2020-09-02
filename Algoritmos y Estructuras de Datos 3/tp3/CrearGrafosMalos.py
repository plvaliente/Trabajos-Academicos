#!/usr/bin/env python
import random as rnd
from sets import Set
import shutil
import os
from subprocess import call
                       
def grafoUnionEstrellas(n,salida):
    # genero un grafo tal que greedy de siempre mal
    fOut = open(salida, 'w')
    fOut.write(str(n)+ " " + str(n-1) + '\n')
    gradoMaximo = 6 + (n-16)/3
    for i in range(1, 4):
        linea = str(i)+ " " + str(i+1) 
        fOut.write(linea + '\n')
    nodoNuevo=5
    for i in range(0, gradoMaximo-1):
        linea = str(1)+ " " + str(nodoNuevo + i) 
        fOut.write(linea + '\n')
    nodoNuevo = 5 + gradoMaximo-1
    for i in range(0, (3 + (n-16)/3)):
        linea = str(3)+ " " + str(nodoNuevo + i) 
        fOut.write(linea + '\n')        
    nodoNuevo = nodoNuevo + (3 + (n-16)/3)
    for i in range(0, (4 + (n-16)/3)):
        linea = str(4)+ " " + str(nodoNuevo + i) 
        fOut.write(linea + '\n')


n = 16
while(n<=199):
    pathSalida = "./GrafosMalos/grafoMalo"+str(n)
    grafoUnionEstrellas(n,pathSalida)
    n=n+3
