#COMPILAR CON PYTHON3

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import pylab as pl
import random
import numpy as np

ns = range(10,151)
ms = [16,13,16,14,19,17,20,23,26,26,29,32,36,41,47,54,61,66,73,76,92,96,97,107,119,125,140,152,156,173,188,198,189,198,221,232,225,240,243,261,269,285,278,305,309,309,353,351,359,385,374,394,381,409,408,432,439,501,488,505,524,504,548,517,560,565,572,637,602,639,709,676,689,721,769,761,806,773,853,848,852,898,898,927,970,940,984,1068,1023,1052,1052,1184,1124,1139,1163,1136,1186,1316,1232,1326,1312,1327,1320,1371,1364,1401,1451,1456,1512,1523,1595,1561,1670,1661,1689,1695,1651,1701,1743,1776,1765,1768,1826,1990,1862,1942,1997,1977,2082,1974,2053,2133,2209,2249,2213,2286,2280,2314,2376,2385,2349]
tiemposBack = [213,241,418,291,469,357,414,572,553,543,727,660,826,808,945,1066,1157,1488,2120,1614,3239,2541,2099,2218,3069,3299,3169,5318,3944,5645,6286,6700,4397,6123,13198,14005,6569,11171,7651,11536,16514,27069,11287,50632,30574,13319,98706,41426,31932,120000,37958,69491,15261,42751,17316,23469,19051,428964,77721,36678,135026,26754,250442,27314,140853,59714,69960,982110,33125,94914,4036460,101702,115022,126389,1090173,181326,2178118,91785,4417749,198256,169516,664396,182221,242741,2437316,131018,219349,19368858,431457,756575,112408,80395134,1386416,357497,1511250,204294,256085,176888537,263838,52264513,6010987,570319,381175,616383,347223,3191559,14384585,2134336,25959702,6904122,103960427,3657351,457247917,116646200,137954270,31667945,393085,1341823,1959324,10893166,1756187,1091931,3391935,8899401676,2480380,274594975,557400229,67552974,2278956048,4352325,70970387,153335734,568328984,576244826,17493055,146855390,9932382,3288737,36444973,36343602,611180]
tiemposBackCompleto = [184,299,601,1263,2590,5325,10570,21837,45354,93132,186772,388921,805033,1659986,3299862,7059715,14890105,30437126,61138537,128968885,274630008,543795692,1146350329,2381324873]
complejidad = [random.normalvariate((2**n)*(n**2),50) / 10**3 for n in ns[0:24]]

'''
tuplas = []
for i in range(len(ms)):
	par = (ms[i], tiemposBack[i])
	tuplas.append(par)

tuplas.sort()

msOrd = []
tiemposBackOrd = []

for i in range(len(tuplas)):
	msOrd.append(tuplas[i][0])
	tiemposBackOrd.append(tuplas[i][1])

print(msOrd)
'''

plt.clf()
df = pd.DataFrame({'Backtracking': tiemposBackCompleto, 'n': ns[0:24], 'g(n) = 2^n * n^2 * n^-3': complejidad})
df.plot(x='n', logy=True)
plt.ylabel('Tiempo (microsegundos)')
plt.show()


'''
plt.clf()
df3 = pd.DataFrame()

#df3 = pd.DataFrame({'Backtracking': tiemposBack, 'n': ns,'Complejidad (2^n)*(n^2)': complejidad })

df3['n'] = ns
df3['Backtracking'] = tiemposBack
df3['Complejidad (2^n)*(n^2)'] = complejidad

df3.plot(x='n', logy=True)
plt.ylabel('Tiempo (microsegundos)')

correlation = df3.corr()
#print(correlation)
sns.plt.show()
'''