import random
import string

def igualesIN(pathSalida,tam):
    fOut = open(pathSalida, 'w')
    for i in range(tam):
        fOut.write("palabra" + '\n')

def randomIN(pathSalida,tam):
    fOut = open(pathSalida, 'w')
    s=string.lowercase
    for i in range(tam):
        fOut.write(''.join(random.sample(s,random.randint(2,7))) + '\n')

igualesIN("iguales10",10)
for i in range(10):
	randomIN("rnd10_"+str(i),10)

igualesIN("iguales100",100)
for i in range(10):
	randomIN("rnd100_"+str(i),100)

igualesIN("iguales1000",1000)
for i in range(10):
	randomIN("rnd1000_"+str(i),1000)
