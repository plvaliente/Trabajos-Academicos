import random

def lotePrioridadCreciente(cantTareas, salida, gapTareas, durTareas):
    # cantTareas % 5 == 0
    fOut = open(salida, 'w')
    mod = cantTareas/5
    tiempo = 0
    for i in range(5):
        for k in reversed(range(1,mod+1)):
            fOut.write('@'+str(tiempo)+':\n')
            fOut.write('TaskPriorizada '+str(5-i)+' '+str(durTareas*k)+'\n')
            tiempo += gapTareas

def lotePrioridadDecreciente(cantTareas, salida, gapTareas, durTareas):
    # cantTareas % 5 == 0
    fOut = open(salida, 'w')
    mod = cantTareas/5
    tiempo = 0
    for i in range(1,6):
        for k in range(1,mod+1):
            fOut.write('@'+str(tiempo)+':\n')
            fOut.write('TaskPriorizada '+str(i)+' '+str(durTareas*k)+'\n')
            tiempo += gapTareas

def lotePrioridadRnd(cantTareas, salida, gapTareas):
    # cantTareas % 5 == 0
    fOut = open(salida, 'w')
    mod = cantTareas/5
    tiempo = 0
    for i in range(5):
        for k in range(1,mod+1):
            fOut.write('@'+str(tiempo)+':\n')
            fOut.write('TaskPriorizada '+str(random.randint(1, 5))+' '+str(random.randint(1, 10))+'\n')
            tiempo += gapTareas

def loteGrande(cantTareas,salida):
    fOut = open(salida, 'w')
    for i in range(cantTareas):
        fOut.write('@0:\n')
        fOut.write('TaskIO '+str(random.randint(1, 8))+' '+str(random.randint(1, 5))+'\n')

def loteMisteryNoOrder(cantTareas,salida,gapTareas):
    fOut = open(salida, 'w')
    tiempo = 0
    for i in range(cantTareas):
            fOut.write('@'+str(tiempo)+':\n')
            fOut.write('TaskCPU '+str(cantTareas-i)+'\n')
            tiempo += gapTareas

def loteMisteryInOrder(cantTareas,salida,gapTareas):
    fOut = open(salida, 'w')
    tiempo = 0
    for i in range(cantTareas):
            fOut.write('@'+str(tiempo)+':\n')
            fOut.write('TaskCPU '+str(i+1)+'\n')
            tiempo += gapTareas

def loteControl(cantTareas,salida):
    fOut = open(salida, 'w')
    for i in range(cantTareas):
            fOut.write('@'+str(random.randint(1, cantTareas))+':\n')
            fOut.write('TaskCPU '+str(random.randint(1, 10))+'\n')


#lotePrioridadDecreciente(10,'LotePrioDec',2,3)
#lotePrioridadCreciente(10,'LotePrioCre',2,3)
#lotePrioridadRnd(10,'LotePrioRnd',2)
#loteGrande(25,'LoteGrande')
#loteMisteryNoOrder(10,'LoteMysNoOrder',2)
loteMisteryInOrder(10,'LoteMysInOrder',2)
#loteControl(10,'LoteControl')
