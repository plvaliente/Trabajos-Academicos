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
i=5
while i <= 100:
    grafoCompleto(i,"grafo")
    call ("./Test")
    if i == 5:
        i = 10
    elif i <= 50:
        i = i + 10
    else:
        i = i + 25
if os.path.isfile('medicion'):
    shutil.copy('medicion', './Resultados/Completo.txt')
    os.remove('medicion')
    medicion = open('medicion', 'wb')
    medicion.close()


#Testeo ciclos simples
i=5
while i <= 100:
    grafoCicloSimple(i,"grafo")
    call ("./Test")
    if i == 5:
        i = 10
    elif i <= 50:
        i = i + 10
    else:
        i = i + 25
if os.path.isfile('medicion'):
    shutil.copy('medicion', './Resultados/Simple.txt')
    os.remove('medicion')
    medicion = open('medicion', 'wb')
    medicion.close()

#Testeo grafos random de entre n y n*n-1 aristas
i=5
while i <= 100:
    grafoRnd(i,"grafo")
    call ("./Test")
    if i == 5:
        i = 10
    elif i <= 50:
        i = i + 10
    else:
        i = i + 25
if os.path.isfile('medicion'):
    shutil.copy('medicion', './Resultados/Random.txt')
    os.remove('medicion')
    medicion = open('medicion', 'wb')
    medicion.close()


#Borro archivo de grafo que no me sirve mas
if os.path.isfile("grafo"):
    os.remove("grafo")
