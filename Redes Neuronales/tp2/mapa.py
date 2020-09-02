import numpy as np
from neupy import algorithms, environment, init
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from collections import Counter
from csv import reader
import time

environment.reproducible()
plt.style.use('ggplot')

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

def savePCtoCsv(check, data, filename='out', data_type='%.8f'):
    arr_c = np.array(check)
    arr_d = np.array(data)
    output_data = np.c_[arr_c,arr_d]
    np.savetxt(filename, output_data, delimiter=', ', fmt=data_type)

def loadDataTP2(filename='tp2_training_dataset.csv', size=851, trainRate=0.9):
    data = loadCsv(filename)
    for i in range(size):
        strColumnToFloat(data, i)
    arr_data = np.array(data)
    qty_data = len(arr_data)
    #divide
    targets = arr_data[:,0]
    inputs = arr_data[:,1:]
    #normalize
    min_by_col = np.zeros(size-1)
    max_by_col = np.max(inputs,axis=0)
    for row in inputs:
        for j in range(len(row)):
            row[j] = (row[j] - min_by_col[j]) / (max_by_col[j] - min_by_col[j])
    #test and train
    qty_train = min(int(qty_data * trainRate), qty_data-1)
    qty_test = qty_data - qty_train 
    if qty_train <= 0:
        qty_train = qty_data
        qty_test = 0
    targets_train = targets[:qty_train]
    inputs_train = inputs[:qty_train, :]
    targets_test = targets[qty_train:]
    inputs_test = inputs[qty_train:, :]
    return targets_train, inputs_train, targets_test, inputs_test
  
def count_elapsed_time(fun):
    start_t = time.time()
    fun
    end_t = time.time()
    return end_t - start_t

def scatter_plot(data, categories, filename='out.pdf'):  
    plt.figure(figsize=(6, 6))
    plt.set_cmap('Set1')
    views = [( 30, 30), (120, 120), ( 0,-90), (0,0)]
    for i in range(4):
        ax = plt.subplot(2,2,i+1, projection='3d')
        ax.scatter(xs=data[:,0],  ys=data[:,1],  zs=data[:,2], c=categories,  marker='.', linewidths=0)
        ax.view_init(views[i][0], views[i][1])                       
        ax.w_xaxis.line.set_color((1.0, 1.0, 1.0, 0.0)) 
        ax.w_yaxis.line.set_color((1.0, 1.0, 1.0, 0.0)) 
        ax.w_zaxis.line.set_color((1.0, 1.0, 1.0, 0.0))                         
        ax.set_xticks([])                               
        ax.set_yticks([])                               
        ax.set_zticks([])
        plt.savefig(filename)

class redHebb:
    def __init__(self, n_inputs, n_outputs, weights_init=[], learningRate=0.001, weightDelimiters=(-0.1,0.1)):
        self.sizeW = (n_outputs, n_inputs)
        if len(weights_init) > 0: 
            self.weights = weights_init
        else:
            self.weights = np.random.uniform(weightDelimiters[0],weightDelimiters[1], self.sizeW )
        self.outputs = np.array([1.0]*n_outputs)
        self.eta = learningRate

    def ojaRule(self, inputData):
        self.weights += self.eta * (np.dot( self.outputs[:, np.newaxis], 
            (inputData - np.dot(self.outputs, self.weights) )[np.newaxis, :]) )

    def sangerRule(self,inputData):
        self.weights += self.eta * (np.outer(self.outputs,inputData) - np.dot(np.tril(np.outer(self.outputs,self.outputs)),self.weights))

    def train(self, inputDataSet, epochs=100, rule='oja'):
        for i in range(epochs):
            np.random.seed(i)
            np.random.shuffle(inputDataSet)
            for inputData in inputDataSet:
                self.outputs = np.dot(self.weights, inputData)
                if rule == 'oja':
                    self.ojaRule(inputData)
                elif rule == 'sanger':
                    self.sangerRule(inputData)
                else:
                    raise ValueError('Error: Not supported rule')

    def test(self, anInput):
        # No actualiza outputs
        return np.dot(self.weights, anInput)

    def testSet(self, inputDataSet):
        result = list()
        for inputData in inputDataSet:
            result.append(self.test(inputData))
        arr_r = np.array(result)
        return arr_r

class redSOM:
    def __init__(self, inputs, gridSize, gridType='rect', learningRate=0.1, log=False, logFreq=20, 
        shuffleInput=False, initialLearningRadius=0, distanceType='euclid', std_reduce = None, 
        radiusReduceCycle=None, weights=init.Normal()):
        self.grid = gridSize
        self.red = algorithms.SOFM(
            n_inputs = inputs,
            features_grid = gridSize,
            grid_type = gridType,
            step = learningRate,
            verbose = log,
            show_epoch = logFreq,
            shuffle_data = shuffleInput,
            learning_radius = initialLearningRadius,
            distance = distanceType,
            reduce_std_after = std_reduce,
            reduce_radius_after = radiusReduceCycle,
            weight = weights, 
        )

    def train(self, inputData, epochs=1000):
        return self.red.train(inputData, epochs= epochs)

    def test(self, anInput):
        return self.red.predict(anInput)

    def winnerPosition(self, planarGrid):
        for i in range(self.grid[0]):
            for j in range(self.grid[1]):
                if planarGrid[(i*self.grid[0])+j] == 1:
                    return i, j


    def getActivations(self, inputs, targets):
        if len(inputs) != len(targets):
            raise ValueError('Error: input/target size')
        matches = list()
        for i in range(self.grid[0]):
            row = list()
            for j in range(self.grid[1]):
                row.append(Counter())
            matches.append(row)
        for i in range(len(inputs)):
            p_x, p_y = self.winnerPosition(self.test(inputs[i])[0])
            matches[p_x][p_y][targets[i]] += 1
        result = np.zeros(self.grid)
        for i in range(self.grid[0]):
            for j in range(self.grid[1]):
                if len(matches[i][j]) > 0:
                    result[i][j] = matches[i][j].most_common(1)[0][0]
                else:
                    result[i][j] = np.nan
        return result

    def confMat(self, aMatrix, aColorMap='Set1', filename='out.pdf'):
        plt.imshow(aMatrix)
        plt.set_cmap(aColorMap)
        plt.grid(False)
        plt.xticks([])
        plt.yticks([])
        plt.savefig(filename)

def exp1(filename, eta=0.0001, epochs = 100, rule='oja'):
    red = redHebb(n_inputs=850, n_outputs= 3, learningRate=eta)
    x = np.copy(inp_train)
    red.train(x, epochs=epochs, rule=rule)
    train_y = red.testSet(inp_train)
    test_y = red.testSet(inp_test)
    scatter_plot(train_y,tgt_train,filename+'.Train.pdf')
    scatter_plot(test_y,tgt_test,filename+'.Test.pdf')

def exp2(filename, n_inputs=850, gridSize=(6,6), eta=0.1, radius=0):
    red = redSOM(inputs=n_inputs, gridSize=gridSize, learningRate=eta, 
        initialLearningRadius=radius, std_reduce=300, radiusReduceCycle=300)
    if n_inputs == 3:
        x = np.copy(inp_3_train)
        red.train(x, epochs=1000)
        mtx_train = red.getActivations(inp_3_train, tgt_train)
        mtx_test = red.getActivations(inp_3_test, tgt_test)
        red.confMat(aMatrix=mtx_train, filename=filename+'.PC3.Train.pdf')
        red.confMat(aMatrix=mtx_test, filename=filename+'.PC3.Test.pdf')
    elif n_inputs == 9:
        x = np.copy(inp_9_train)
        red.train(x, epochs=1000)
        mtx_train = red.getActivations(inp_9_train, tgt_train)
        mtx_test = red.getActivations(inp_9_test, tgt_test)
        red.confMat(aMatrix=mtx_train, filename=filename+'.PC9.Train.pdf')
        red.confMat(aMatrix=mtx_test, filename=filename+'.PC9.Test.pdf')
    else:
        x = np.copy(inp_train)
        red.train(x, epochs=1000)
        mtx_train = red.getActivations(inp_train, tgt_train)
        mtx_test = red.getActivations(inp_test, tgt_test)
        red.confMat(aMatrix=mtx_train, filename=filename+'.ALL.Train.pdf')
        red.confMat(aMatrix=mtx_test, filename=filename+'.ALL.Test.pdf')

def r9(inp, gridSize):
        red_9 = redHebb(n_inputs=850, n_outputs= 9, learningRate=0.0001)
        red_9.train(inp, epochs=1000, rule='sanger')
        inp_9_t_train = red_9.testSet(inp_train)
        red = redSOM(inputs=9, gridSize=gridSize, learningRate=0.1, 
        initialLearningRadius=3, std_reduce=300, radiusReduceCycle=300)
        red.train(inp_9_t_train, epochs=1000)

def r9_w(inp, gridSize):
        red = redSOM(inputs=9, gridSize=gridSize, learningRate=0.1, 
        initialLearningRadius=3, std_reduce=300, radiusReduceCycle=300)
        red.train(inp, epochs=1000)

def r3(inp, gridSize):
        red_3 = redHebb(n_inputs=850, n_outputs= 3, learningRate=0.0001)
        red_3.train(inp, epochs=1000, rule='sanger')
        inp_3_t_train = red_3.testSet(inp_train)
        red = redSOM(inputs=3, gridSize=gridSize, learningRate=0.1, 
        initialLearningRadius=3, std_reduce=300, radiusReduceCycle=300)
        red.train(inp_3_t_train, epochs=1000)

def r3_w(inp, gridSize):
        red = redSOM(inputs=3, gridSize=gridSize, learningRate=0.1, 
        initialLearningRadius=3, std_reduce=300, radiusReduceCycle=300)
        red.train(inp, epochs=1000)

def rA(inp, gridSize):
        red = redSOM(inputs=850, gridSize=gridSize, learningRate=0.1, 
        initialLearningRadius=3, std_reduce=300, radiusReduceCycle=300)
        red.train(inp, epochs=1000)


def exp2Time():
    arrG = [(3,3), (6,6), (9,9)] 
    times = list()
    for grid in arrG:
        tGrid = list()
        x_3 = np.copy(inp_train)
        x_9 = np.copy(inp_train)
        x_A = np.copy(inp_train)
        x_3_w = np.copy(inp_3_train)
        x_9_w = np.copy(inp_9_train)
        t_3 = 0.0
        t_9 = 0.0
        t_A = 0.0
        t_3_w = 0.0
        t_9_w = 0.0
        for i in range(3):
            x_3 = np.copy(inp_train)
            x_9 = np.copy(inp_train)
            x_A = np.copy(inp_train)
            x_3_w = np.copy(inp_3_train)
            x_9_w = np.copy(inp_9_train)
            t_3 += count_elapsed_time(r3(x_3, grid))
            t_9 += count_elapsed_time(r9(x_9, grid))
            t_A += count_elapsed_time(rA(x_A, grid))
            t_3_w += count_elapsed_time(r3_w(x_3_w, grid))
            t_9_w += count_elapsed_time(r9_w(x_9_w, grid))
            print(t_3, t_9, t_A, t_3_w, t_9_w)
        t_3 = float(t_3 / 5)
        t_9 = float(t_9 / 5)
        t_A = float(t_A / 5)
        t_3_w = float(t_3_w / 5)
        t_9_w = float(t_9_w / 5)
        tGrid.append(t_3)
        tGrid.append(t_9)
        tGrid.append(t_A)
        tGrid.append(t_3_w)
        tGrid.append(t_9_w)
        times.append(tGrid[:])
    arr_times = np.array(times)
    #Orden mtx
    #t(PC=3+getPC3) t(PC=9+getPC9) t(all) t(PC=3) t(PC=9)  todos en grilla 3x3
    #t(PC=3+getPC3) t(PC=9+getPC9) t(all) t(PC=3) t(PC=9)  todos en grilla 6x6
    #t(PC=3+getPC3) t(PC=9+getPC9) t(all) t(PC=3) t(PC=9)  todos en grilla 9x9
    np.savetxt('tiemposDeEjecucion', arr_times, delimiter=', ', fmt='%.2f')


tgt_train, inp_train, tgt_test, inp_test = loadDataTP2()

# #EXP1
# #exp1('SP.eta.0001.Epoch100.Oja')
# #exp1('SP.eta.0001.Epoch1000.Oja', epochs=1000)
# #exp1('SP.eta.001.Epoch100.Oja', eta=0.001)
# #exp1('SP.eta.001.Epoch1000.Oja', eta=0.001, epochs=1000)
# #exp1('SP.eta.0001.Epoch100.Sanger', rule='sanger')
# # exp1('SP.eta.0001.Epoch1000.Sanger', epochs=1000, rule='sanger')
# # exp1('SP.eta.001.Epoch100.Sanger', eta=0.001, rule='sanger')
# # exp1('SP.eta.001.Epoch1000.Sanger', eta=0.001, epochs=1000, rule='sanger')

#PC == 3
red_3 = redHebb(n_inputs=850, n_outputs= 3, learningRate=0.0001)
x_3 = np.copy(inp_train)
red_3.train(x_3, epochs=1000, rule='sanger')
inp_3_train = red_3.testSet(inp_train)
inp_3_test = red_3.testSet(inp_test)

#PC == 9
red_9 = redHebb(n_inputs=850, n_outputs= 9, learningRate=0.0001)
x_9 = np.copy(inp_train)
red_9.train(x_9, epochs=1000, rule='sanger')
inp_9_train = red_9.testSet(inp_train)
inp_9_test = red_9.testSet(inp_test)

print('datos pc3, pc9 y all generados')
# #EXP2
# ALL
# exp2('M.eta.1.R0.6x6')
# exp2('M.eta.9.R0.6x6', eta=0.9)
# exp2('M.eta.1.R3.6x6', radius=3)
# exp2('M.eta.9.R3.6x6', eta=0.9, radius=3)
# print('ALL terminado')
# 9
# exp2('M.eta.1.R0.6x6', n_inputs= 9)
# exp2('M.eta.9.R0.6x6', n_inputs= 9, eta=0.9)
# exp2('M.eta.1.R3.6x6', n_inputs= 9, radius=3)
# exp2('M.eta.9.R3.6x6', n_inputs= 9, eta=0.9, radius=3)
# print('9 terminado')
# # 3
# exp2('M.eta.1.R0.6x6', n_inputs= 3)
# exp2('M.eta.9.R0.6x6', n_inputs= 3, eta=0.9)
# exp2('M.eta.1.R3.6x6', n_inputs= 3, radius=3)
# exp2('M.eta.9.R3.6x6', n_inputs= 3, eta=0.9, radius=3)
# print('3 terminado')
# # Sizes
# exp2('M.eta.1.R3.3x3', n_inputs= 3, eta=0.1, radius=3, gridSize=(3,3))
# exp2('M.eta.1.R3.9x9', n_inputs= 3, eta=0.1, radius=3, gridSize=(9,9))
# exp2('M.eta.1.R3.3x3', n_inputs= 9, eta=0.1, radius=3, gridSize=(3,3))
# exp2('M.eta.1.R3.9x9', n_inputs= 9, eta=0.1, radius=3, gridSize=(9,9))
# exp2('M.eta.1.R3.3x3', eta=0.1, radius=3, gridSize=(3,3))
# exp2('M.eta.1.R3.9x9', eta=0.1, radius=3, gridSize=(9,9))
# print('Sizes terminado')
# Times

exp2Time()
