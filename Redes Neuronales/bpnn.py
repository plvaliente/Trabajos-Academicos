import math
import random
import string
import numpy
from csv import reader

def invalidOption():
    print 'Opcion no valida'

def main():
    print 'Hola!!!!'
    networkType = raw_input("Trabajar con Red entrenada: 0 o trabajar con Red nueva: 1")
    if int(networkType) != 0 and int(networkType) != 1 and int(networkType) != 2:
        invalidOption()
    else:
        if int(networkType) == 0:
            if int(exercise) != 1 and int(exercise) != 2:
                invalidOption()
            else:
                exercise = raw_input("Ejercicio 1 o 2?")
                if int(exercise) == 1:
                    mapTarget = {'B': 0.0, 'M': 1.0}
                    trainPat, validPat = loadData('tp1_ej1_training.csv', range(1,11), [0], mapTarget, range(1,11), [0], 0.8)
                    nnEx1 = neuralNetwork(10, [8,5,3], 1, -.2, .2)
                    print 'ENTRENANDO RED'
                    nnEx1.train(trainPat, validPat, 800, 0.2)
                    nnDataFilename1 = raw_input('Ingresar: nombre del fichero csv')
                    mapTarget = {'B': 0.0, 'M': 1.0}
                    trainPat1, validPat1 = loadData(nnDataFilename1, range(1,11), [0], mapTarget, range(1,11), [0], 1)    
                    nnEx1.test(trainPat1)
                elif int(exercise) == 2:
                    trainPat, validPat = loadData('tp1_ej2_training.csv', range(10), [], {}, range(8), [8,9], 0.8)
                    nnEx2 = neuralNetwork(8, [8,5,5,3], 2, -.2, .2)
                    print 'ENTRENANDO RED'
                    nnEx2.train(trainPat, validPat, 900, 0.2)
                    nnDataFilename2 = raw_input('Ingresar: nombre del fichero csv')
                    trainPat2, validPat2 = loadData(nnDataFilename2, range(10), [], {}, range(8), [8,9], 1)
                    nnEx2.test(trainPat2)            
        elif int(networkType) == 1:
            if int(exercise) != 1 and int(exercise) != 2:
                invalidOption()
            else:
                exercise = raw_input("Ejercicio 1 o 2?")
                trainRate = raw_input('Ingresar porcentaje de del dataset a usar como train, entre 0 y 1')
                itRate = raw_input('ingresar numero de iteraciones')
                alphaNum = raw_input('ingesar alpha')
                if int(exercise) == 1:
                    nnDataFilename = raw_input('Ingresar: nombre del fichero csv')
                    mapTarget = {'B': 0.0, 'M': 1.0}
                    trainPat, validPat = loadData(nnDataFilename, range(1,11), [0], mapTarget, range(1,11), [0], float(trainRate))    
                    nnNewEx1 = neuralNetwork(10, [8,5,3], 1, -.2, .2)
                    print 'ENTRENANDO RED'
                    nnNewEx1.train(trainPat, validPat, int(itRate), float(alphaNum))
                    nnDataFilename1 = raw_input('Ingresar: nombre del fichero csv para testear')
                    mapTarget = {'B': 0.0, 'M': 1.0}
                    trainPat1, validPat1 = loadData(nnDataFilename1, range(1,11), [0], mapTarget, range(1,11), [0], 1)    
                    nnEx1.test(trainPat1)
                else:
                    nnDataFilename = raw_input('Ingresar: nombre del fichero csv')
                    trainPat, validPat = loadData(nnDataFilename, range(10), [], {}, range(8), [8,9], 1)
                    nnEx2 = neuralNetwork(8, [8,5,5,3], 2, -.2, .2)
                    print 'ENTRENANDO RED'
                    nnEx2.train(trainPat, validPat, int(itRate), float(alphaNum))
                    nnDataFilename2 = raw_input('Ingresar: nombre del fichero csv para testear')
                    trainPat2, validPat2 = loadData(nnDataFilename2, range(10), [], {}, range(8), [8,9], 1)
                    nnEx2.test(trainPat2)

#### Data and Testing ####

def loadCsv(aFilename):
    dataset = list()
    with open(aFilename, 'r') as file:
        csv_reader = reader(file)
        for row in csv_reader:
            if not row:
                continue
            dataset.append(row)
    return dataset

def strColumnToFloat(aDataset, aColumnIndex):
    for row in aDataset:
        row[aColumnIndex] = float(row[aColumnIndex].strip())

def mapColumnToFloat(aDataset, aColumnIndex, aDictionaryForStringValues):
    for row in aDataset:
        row[aColumnIndex] = aDictionaryForStringValues[row[aColumnIndex].strip()]

def convertDataToFloat(aDataset, aListOfColumnIndexes, aListOfColumnIndexesThatHasStringValues,
 aDictionaryForStringValues={}):
    for i in aListOfColumnIndexes:
        strColumnToFloat(aDataset, i)
    for i in aListOfColumnIndexesThatHasStringValues:
        mapColumnToFloat(aDataset, i, aDictionaryForStringValues)

def divideTargetsFromInputs(aDataset, aListOfInputsIndexes, aListOfTargetsIndexes):
    inputs = list()
    targets = list()
    aInput = range(len(aListOfInputsIndexes))
    aTarget = range(len(aListOfTargetsIndexes))  
    for row in aDataset:
        j = 0
        k = 0
        for i in aListOfInputsIndexes:
            aInput[j] = row[i]
            j += 1    
        for t in aListOfTargetsIndexes:
            aTarget[k] = row[t]
            k += 1
        inputs.append(aInput[:])
        targets.append(aTarget[:])
    return targets, inputs

def getMinimumAndMaximumFromColumns(aDataset):
    minimums = list()
    maximums = list()
    for column in zip(*aDataset):
        minimums.append(min(column))
        maximums.append(max(column))
    return minimums, maximums

def normalizeDataset(aDataset, aVectorOfMinimumsByColumnmax, aVectorOfMaximumsByColumnmax):
    for row in aDataset:
        for i in range(len(row)):
            row[i] = (row[i] - aVectorOfMinimumsByColumnmax[i]) / (aVectorOfMaximumsByColumnmax[i] - aVectorOfMinimumsByColumnmax[i])

def parallelShuffle(aVector, otherVector, aSeed):
    rand_state = numpy.random.RandomState(aSeed)
    rand_state.shuffle(aVector)
    rand_state.seed(aSeed)
    rand_state.shuffle(otherVector)

def getTrainAndValidationSets(inputs, targets, aTrainRate):
    if len(inputs) != len(targets):
            raise ValueError('Dimensions error')
    patternsTrain= list()
    patternsValidation = list()
    trainRange = int(len(targets) * aTrainRate)
    for i in range(len(targets)):
        if i < trainRange:
            patternsTrain.append([inputs[i][:], targets[i][:]])
        else:
            patternsValidation.append([inputs[i][:], targets[i][:]])
    return patternsTrain, patternsValidation
def loadData(aFile, aListOfColumnIndexes, aListOfColumnIndexesThatHasStringValues,
 aDictionaryForStringValues, aListOfInputsIndexes, aListOfTargetsIndexes, aTrainRate):
    data = loadCsv(aFile)
    convertDataToFloat(data, aListOfColumnIndexes, aListOfColumnIndexesThatHasStringValues, aDictionaryForStringValues)
    targets, inputs = divideTargetsFromInputs(data, aListOfInputsIndexes, aListOfTargetsIndexes)
    minimumsI, maximumsI = getMinimumAndMaximumFromColumns(inputs)
    minimumsT, maximumsT = getMinimumAndMaximumFromColumns(targets)
    normalizeDataset(inputs, minimumsI, maximumsI)
    normalizeDataset(targets, minimumsT, maximumsT)
    parallelShuffle(inputs, targets, 0)
    trainPat, validPat = getTrainAndValidationSets(inputs, targets, aTrainRate)
    return trainPat, validPat
#### Math functions #### 

def rand(a, b):
    return random.uniform(a,b)

#tanh    
def sigmoid(x): return math.tanh(x)
def dsigmoid(y): return 1.0 - y**2

#sigmoidal
#def sigmoid (x): return 1/(1 + numpy.exp(-x))
#def dsigmoid(y): return y * (1 - y)

def meanSquaredError(aVector, anotherVector):
    error = 0.0
    for i in range(len(aVector)):
        error = error + 0.5*(aVector[i]-anotherVector[i])**2
    return error

def difVector(aVector, otherVector):
    if len(otherVector) != len(aVector):
        raise ValueError('Error: vectors size')
    result = 0.0    
    for idx in range(len(aVector)):
        result += abs(aVector[idx] - otherVector[idx])
    return result

#### Matrix ####

class matrix:

    def __init__(self, rows, columns, aMatrix = [] ):
        if len(aMatrix) == 0:
            aMatrix = numpy.zeros((rows,columns))
        self.mat = aMatrix
        self.rows = rows
        self.columns = columns

    def getValue(self, aRowIndex, aColumnIndex):
        return self.mat[aRowIndex][aColumnIndex] 
    
    def setValue(self, aRowIndex, aColumnIndex, aValue):
        self.mat[aRowIndex][aColumnIndex] = aValue

    def getColumn(self,aIndex):
        return self.mat[:, [aIndex]]

    def getRow(self, aIndex):
        return self.mat[aIndex]

    def dot(self, otherMatrix):
        if self.columns != otherMatrix.rows:
            raise ValueError('dot: Dimension error')
        return matrix(self.rows, otherMatrix.columns, self.mat.dot(otherMatrix.mat))
    
    def dotSelf(self, otherMatrix):
        if self.columns != otherMatrix.rows:
            raise ValueError('dotS: Dimension error')
        self.columns =  otherMatrix.columns, 
        self.mat = self.mat.dot(otherMatrix.mat)
    
    def dotColumnWithDelimiters(self, aColumnIndex, aVector, aBeginIndex, AEndIndex):
        if (AEndIndex - aBeginIndex) + 1 != len(aVector):
            raise ValueError('dotCwDelimiters: Dimension error')
        result = 0.0
        column = self.getColumn(aColumnIndex)
        for i in range(aBeginIndex,AEndIndex+1):
            result += aVector[i - aBeginIndex] * column[i]
        return result
    def dotColumn(self, aColumnIndex, aVector):
        if self.rows != len(aVector):
            raise ValueError('dotC: Dimension error')
        return self.dotColumnWithDelimiters(aColumnIndex, aVector, 0, len(aVector)-1)

    def dotRow(self, aRowIndex, aVector):
        if self.columns != len(aVector):
            raise ValueError('dotR: Dimension error')
        result = 0.0
        row = self.getRow(aRowIndex)
        for i in range(self.columns):
            result += aVector[i] * row[i]
        return result               

    def rnd(self, aMinimumValue, aMaximumValue):
        for i in range(self.rows):
            for j in range(self.columns):
                self.setValue(i, j, rand(aMinimumValue, aMaximumValue))

    def printMe(self):
        for f in range(self.rows):
            for c in range(self.columns):
                print str(self.getValue(f,c))+',',

#### Neaural Network ####

class neuralNetwork:

    def initWeights(self, rows, columns, aMinimumValue, aMaximumValue):
        mat = matrix(rows, columns)
        mat.rnd(aMinimumValue, aMaximumValue)
        self.w.append(mat)

    def updateLayer(self, receptors, aInputActivationVector, aOutputActivationVector, aIndex):
        for i in range(receptors):
            aOutputActivationVector[i] = sigmoid(self.w[aIndex].dotColumn(i, aInputActivationVector))

    def calculateDelta(self, aDeltaToPropagate, anActivationValue, aWeightMatrix, aIndex):
        return dsigmoid(anActivationValue) * aWeightMatrix.dotRow(aIndex, aDeltaToPropagate)

    def updateWeightsOfLayer(self, emiters, receptors, aWeightsMatrixOfTheLayer, aLearningRate, aDeltaVector, anActivationVector):
        weight = 0.0
        for j in range(emiters):
            for k in range(receptors):
                weight = aWeightsMatrixOfTheLayer.getValue(j, k) 
                aWeightsMatrixOfTheLayer.setValue(j, k, weight + (aLearningRate * (aDeltaVector[k]*anActivationVector[j])))

    def __init__(self, ni, nh, no, aMinimumValue, aMaximumValue):
        self.ni = ni + 1# +1 for bias nod
        self.nh = nh
        self.no = no
        self.ch = len(nh)
        self.isASimpleLayerNetwork = (self.ch == 0)

        # activations for nodes
        self.ai = [1.0]*self.ni
        self.ah = []
        for i in range(self.ch):
             self.ah.append([1.0]*self.nh[i])     
        self.ao = [1.0]*self.no
        
        self.w = []
        if self.isASimpleLayerNetwork:
            self.initWeights(self.ni, self.no, aMinimumValue, aMaximumValue)
        else:
            for c in range(self.ch + 1):
                if c == 0:
                    self.initWeights(self.ni, self.nh[0], aMinimumValue, aMaximumValue)
                elif c == self.ch:
                    self.initWeights(self.nh[c-1], self.no, aMinimumValue, aMaximumValue)
                else:
                    self.initWeights(self.nh[c-1], self.nh[c], aMinimumValue, aMaximumValue)

    def update(self, inputs):
        if len(inputs) != self.ni-1:
            raise ValueError('wrong number of inputs')

        for i in range(self.ni-1):
            self.ai[i] = inputs[i]

        if self.isASimpleLayerNetwork:
            self.updateLayer(self.no, self.ai, self.ao, 0)            
        else:
            for c in range(self.ch + 1):
                if c == 0: 
                    self.updateLayer(self.nh[0], self.ai, self.ah[0], 0)
                elif c == self.ch:
                    self.updateLayer(self.no, self.ah[self.ch-1], self.ao, c)
                else:
                    self.updateLayer(self.nh[c], self.ah[c-1], self.ah[c], c)             
        return self.ao[:]

    def updateOja(self, inputs):
        for i in range(self.ni):
            self.ai[i] = inputs[i]
        if self.isASimpleLayerNetwork:
            self.updateLayer(self.no, self.ai, self.ao, 0)  
        return self.ao[:]

    def backPropagate(self, targets, alpha):
        if len(targets) != self.no:
            raise ValueError('wrong number of target values')

        # calculate error terms for output
        output_deltas = [0.0] * self.no
        for i in range(self.no):
            output_deltas[i] = dsigmoid(self.ao[i]) * (targets[i]-self.ao[i])

        if self.isASimpleLayerNetwork:
            self.updateWeightsOfLayer(self.ni, self.no, self.w[0], alpha, output_deltas, self.ai)            
        
        else:        
            # calculate error terms for hidden
            hidden_deltas = []
            for i in range(self.ch):
                 hidden_deltas.append([1.0]*self.nh[i]) 
            for i in range(self.ch-1, -1, -1):
                for j in range(self.nh[i]):
                    error = 0.0
                    if i == self.ch-1:
                        hidden_deltas[i][j] = self.calculateDelta(output_deltas, self.ah[i][j], self.w[i+1], j)
                    else:
                        hidden_deltas[i][j] = self.calculateDelta(hidden_deltas[i+1], self.ah[i][j], self.w[i+1], j)

            # update weights
            self.updateWeightsOfLayer(self.nh[self.ch-1], self.no, self.w[self.ch], alpha, output_deltas, self.ah[self.ch-1])
            for c in range(self.ch):
                if c == 0:
                    self.updateWeightsOfLayer(self.ni, self.nh[0], self.w[0], alpha, hidden_deltas[0], self.ai)
                else:
                    self.updateWeightsOfLayer(self.nh[c-1], self.nh[c], self.w[c], alpha, hidden_deltas[c], self.ah[c-1])
        # calculate error
        return meanSquaredError(targets,self.ao)
    
    def updateWeightsUsingOjaRule(self, aWeightMatrix, aLearningRate, aOutputUnitsNumber):
        for i in  range(aWeightMatrix.rows):
            for j in range(aWeightMatrix.columns):
                delta = aLearningRate * self.ao[i] * (self.ai[j] - aWeightMatrix.dotColumnWithDelimiters(j, self.ao, 0, aOutputUnitsNumber) )
                updatedWeight = aWeightMatrix.getValue(i, j)
                aWeightMatrix.setValue(i, j, updatedWeight)

#    def updateWeightsUsingSangerRule(self, aWeightMatrix, aLearningRate):

    def ojaRule(self, aLearningRate, aOutputUnitsNumber):
        if self.isASimpleLayerNetwork:
            self.updateWeightsUsingOjaRule(self.w[0], aLearningRate, aOutputUnitsNumber)

    def test(self, patterns):
        for p in patterns:
            for i in range(self.no):
                print(p[0], '->', "%.10f" % float(self.update(p[0])[i]))
    
    def valid(self, patterns):
        error = 0.0
        for p in patterns:
            inputs = p[0]
            targets = p[1]
            predict = self.update(inputs)
            error += difVector(predict, targets) 
        #print('%-.5f' % error)
        return error

    def train(self, patterns, aValidationSet, iterations=1000, N=0.5):
        # N: learning rate
        error = 0.0
        for i in range(iterations):
            error = 0.0
            for p in patterns:
                inputs = p[0]
                targets = p[1]
                self.update(inputs)
                error = error + self.backPropagate(targets, N)
            if i % 100 == 0:
                print error, self.valid(aValidationSet)
        return error

    def trainOja(self, patterns, iterations=1000, S=0.5):
        # N: learning rate
        error = 0.0
        for i in range(iterations):
            for p in patterns:
                outputValue = self.updateOja(p)
                print(p, '->', outputValue)
                self.ojaRule( S, self.no-1)

def demoEjP4(a_i, aLenght):
    patterns = list()
    for p in range(10):
        pat = [rand(-a_i, a_i)]*aLenght
        patterns.append(pat[:])
    random.seed(0)
    nn = neuralNetwork(5, [], 4,-.2, .2)
    nn.trainOja(patterns, 1, 0.05)

def demoXOR():
    pat = [
        [[0,0], [0]],
        [[0,1], [1]],
        [[1,0], [1]],
        [[1,1], [0]]
    ]
    random.seed(0)
    
    n = neuralNetwork(2, [6, 3], 1, -.2, .2)
    #n.weights()
    n.train(pat, pat, 1000, 0.5)
    #n.weights()    
    n.test(pat)
    n.valid(pat)

def demoOR():
    pat = [
        [[0,0], [0]],
        [[0,1], [1]],
        [[1,0], [1]],
        [[1,1], [1]]
    ]
    random.seed(0)
    
    n = neuralNetwork(2, [], 1, -.6, .6)
    #n.weights()
    n.train(pat, pat, 1000, 0.5)
    #n.weights()    
    n.test(pat)
    n.valid(pat)

def testEj1():
    mapTarget = {'B': 0.0, 'M': 1.0}
    trainPat, validPat = loadData('tp1_ej1_training.csv', range(1,11), [0], mapTarget, range(1,11), [0], 0.8)    

    print '######'
    print 'TESTING EJ 1'
    print '######'

    hiddens = [[10], [8], [5], [3], [10, 10], [10, 5], [10, 3],
    [8, 5], [8, 3], [3, 10], [10, 8, 5], [10, 8, 3], [8, 5, 3], [3, 5, 8], [10, 8, 5, 3] ]
    for conf in hiddens:
        print 'red tipo:', conf
        random.seed(0)
        n = neuralNetwork(10, conf, 1, -.2, .2)
        errT = n.train(trainPat, validPat, 1000, 0.5)

def testEj2():
    trainPat, validPat = loadData('tp1_ej2_training.csv', range(10), [], {}, range(8), [8,9], 0.8)

    print '######'
    print 'TESTING EJ 2'
    print '######'
    
    hiddens = [[10], [8], [5], [3], [8, 10], [10, 8], [8, 5],
    [8, 3], [5, 3], [3, 8], [8, 5, 3], [10, 5, 3], [5, 10, 3], [3, 5, 8], [8, 5, 5, 3] ]
    for conf in hiddens:
        print 'red tipo:', conf
        random.seed(0)
        n = neuralNetwork(8, conf, 2, -.2, .2)
        errT = n.train(trainPat, validPat, 1000, 0.5)

def testEj1alphas():
    mapTarget = {'B': 0.0, 'M': 1.0}
    trainPat, validPat = loadData('tp1_ej1_training.csv', range(1,11), [0], mapTarget, range(1,11), [0], 0.8)    
    print 'TESTING ALPHA EJ1'
    random.seed(0)
    nn1 = neuralNetwork(10, [3, 5, 8], 1, -.2, .2)      
    random.seed(0)
    nn2 = neuralNetwork(10, [8, 5, 3], 1, -.2, .2)      
    alphas = [0.2, 0.8]
    for alpha in alphas:
        print 'best train w/alpha:', alpha
        nn1.train(trainPat, validPat, 1000, alpha)
    for alpha in alphas:
        print 'best valid w/alpha:', alpha
        nn2.train(trainPat, validPat, 1000, alpha)

def testEj2alphas():
    trainPat, validPat = loadData('tp1_ej2_training.csv', range(10), [], {}, range(8), [8,9], 0.8)
    print 'TESTING ALPHA EJ2'
    random.seed(0)
    nn1 = neuralNetwork(8, [8, 5, 5, 3], 2, -.2, .2)      
    alphas = [0.2, 0.8]
    for alpha in alphas:
        print 'best train w/alpha:', alpha
        nn1.train(trainPat, validPat, 1000, alpha)

#demoXOR()
#demoOR()
#testEj1alphas()
#testEj2alphas()

demoEjP4(1, 6)
#main()

