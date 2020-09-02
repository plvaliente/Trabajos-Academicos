#!/usr/bin/env python

import shutil
import os
from CrearGrafos import *
from subprocess import call

#Borro las mediciones anteriores
if os.path.exists("Resultados"):
    shutil.rmtree("Resultados")
os.mkdir("Resultados")

# Testeo sobre completos
limitec=10
while limitec <=1000:
    i=5
    while i <= 500:
        grafoCompletoEj2(i,"grafo",limitec)
        call ("./Test")
        if i == 10:
            i = 25
        elif i == 100:
            i = 250
        else:
            i = 2 * i
    if os.path.isfile('medicion'):
        shutil.copy('medicion', './Resultados/CompletoC' + str(limitec) + '.txt')
        os.remove('medicion')
        medicion = open('medicion', 'wb')
        medicion.close()
    limitec = limitec * 10

#Testeo ciclos simples
limitec=10
while limitec <=1000:
    i=5
    while i <= 500:
        grafoCicloSimple(i,"grafo",limitec)
        call ("./Test")
        if i == 10:
            i = 25
        elif i == 100:
            i = 250
        else:
            i = 2 * i
    if os.path.isfile('medicion'):
        shutil.copy('medicion', './Resultados/SimpleC' + str(limitec) + '.txt')
        os.remove('medicion')
        medicion = open('medicion', 'wb')
        medicion.close()
    limitec = limitec * 10

#Testeo grafos random de entre n y n*n-1 aristas
limitec=10
while limitec <=1000:
    i=5
    while i <= 500:
        grafoRndEj2(i,"grafo",limitec)
        call ("./Test")
        if i == 10:
            i = 25
        elif i == 100:
            i = 250
        else:
            i = 2 * i
    if os.path.isfile('medicion'):
        shutil.copy('medicion', './Resultados/RndC' + str(limitec) + '.txt')
        os.remove('medicion')
        medicion = open('medicion', 'wb')
        medicion.close()
    limitec = limitec * 10

#Veo mejor caso de C en un completo
i = 50
limitec=10
while limitec <=1000000:
    grafoCompletoMejorCasoC(i,"grafo",limitec)
    call ("./Test")
    if os.path.isfile('medicion'):
        shutil.copy('medicion', './Resultados/CompletoMejorC' + str(limitec) + '.txt')
        os.remove('medicion')
        medicion = open('medicion', 'wb')
        medicion.close()
    limitec = limitec * 10

#Veo peor caso de C en un completo
i = 50
limitec=10
while limitec <=1000000:
    grafoCompletoPeorCasoC(i,"grafo",limitec)
    call ("./Test")
    if os.path.isfile('medicion'):
        shutil.copy('medicion', './Resultados/CompletoPeorC' + str(limitec) + '.txt')
        os.remove('medicion')
        medicion = open('medicion', 'wb')
        medicion.close()
    limitec = limitec * 10

#Veo mejor caso de C en un ciclo simple
i = 50
limitec=10
while limitec <=1000000:
    CicloSimpleMejorCaso(i,"grafo",limitec)
    call ("./Test")
    if os.path.isfile('medicion'):
        shutil.copy('medicion', './Resultados/SimpleMejorC' + str(limitec) + '.txt')
        os.remove('medicion')
        medicion = open('medicion', 'wb')
        medicion.close()
    limitec = limitec * 10

#Veo peor caso de C en un simple
i = 50
limitec=10
while limitec <=1000000:
    CicloSimplePeorCaso(i,"grafo",limitec)
    call ("./Test")
    if os.path.isfile('medicion'):
        shutil.copy('medicion', './Resultados/SimplePeorC' + str(limitec) + '.txt')
        os.remove('medicion')
        medicion = open('medicion', 'wb')
        medicion.close()
    limitec = limitec * 10

#Borro archivo de grafo que no me sirve mas
if os.path.isfile("grafo"):
    os.remove("grafo")
