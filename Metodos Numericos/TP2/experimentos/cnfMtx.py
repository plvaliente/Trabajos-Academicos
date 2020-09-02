import numpy as np
import matplotlib.pyplot as plt

conf_arr = np.array( [
[ 819, 0, 0.6, 0.2, 0.2, 1, 3.6, 0.2, 1, 0.6 ],
[ 0, 927.4, 2.6, 1.4, 0.6, 0.4, 0.8, 1.4, 0.8, 1.4 ],
[ 2.6, 3, 812.2, 3.2, 0.6, 0.2, 0.8, 9.8, 2.2, 0.8 ],
[ 0.6, 0.8, 6.2, 830, 0, 12.4, 0.4, 3.8, 11.4, 4.6 ],
[ 0.4, 2, 0.2, 0, 791.4, 0.2, 2.6, 0.8, 0.2, 16.6 ],
[ 1.2, 0.4, 0.6, 9.2, 0.8, 731.6, 7.2, 0, 3, 5 ],
[ 2.2, 1, 0.4, 0.2, 1, 3.2, 818.4, 0, 1, 0 ],
[ 0, 5.4, 4.2, 0.8, 1.6, 0.2, 0, 856, 0, 12 ],
[ 1, 2.8, 2.6, 10.2, 2.6, 6, 3.6, 1.4, 775.2, 7.2 ],
[ 2.6, 0.8, 0.4, 5.2, 14.2, 2.6, 0.4, 8.2, 2.2, 801 ],
 ] )

norm_conf = []
for i in conf_arr:
    a = 0
    tmp_arr = []
    a = sum(i, 0)
    for j in i:
        tmp_arr.append(float(j)/float(a))
    norm_conf.append(tmp_arr)

fig = plt.figure()

fig.suptitle('M. Confusion PLS Gamma(50) k(1) Folds(5)', fontsize=14, fontweight='bold')
fig.subplots_adjust(top=0.85)
# plt.clf()
ax = fig.add_subplot(111)

ax.set_xlabel('Predicted')
ax.set_ylabel('True')

ax.set_aspect(1)
res = ax.imshow(np.array(norm_conf), cmap=plt.cm.jet, 
                interpolation='nearest')

width, height = conf_arr.shape

for x in range(width):
    for y in range(height):
        if (conf_arr[x][y] != 0):
            ax.annotate(str(conf_arr[x][y]), xy=(y, x), 
                    horizontalalignment='center',
                    verticalalignment='center')

cax = ax.matshow(conf_arr)
cb = fig.colorbar(cax)
alphabet = '0123456789'
plt.xticks(range(width), alphabet[:width])
plt.yticks(range(height), alphabet[:height])
plt.savefig('cMtxPLSk1F5.png', format='png')
