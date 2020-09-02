#!/usr/bin/env python
# For Python, this file uses encoding: utf-8

import matplotlib.pyplot as plt
import numpy as np
import json
import sys
from itertools import cycle
import matplotlib.patches as mpatches
from copy import deepcopy

tableau20 = [(31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),
             (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),
             (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),
             (227, 119, 194), (247, 182, 210), (127, 127, 127),
             (199, 199, 199),
             (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229)]

for i in range(len(tableau20)):
    r, g, b = tableau20[i]
    tableau20[i] = (r / 255., g / 255., b / 255.)


def estimar_hops_desconocidos(hops):
    hops = deepcopy(hops)
    i = 1
    while i < len(hops):
        if hops[i]['rtt'] is None:
            j = i+1
            while hops[j]['rtt'] is None:
                j += 1
            for k in xrange(i, j):
                delta = hops[j]['rtt'] - hops[i-1]['rtt']
                hops[k]['rtt'] = hops[k-1]['rtt'] + delta / (j-i+1)
            i = j+1
        else:
            i += 1
    return hops


def main(hops):
    hops = estimar_hops_desconocidos(hops)
    relative_rtts = [hops[0]['rtt']] + [hops[i+1]['rtt'] - hops[i]['rtt']
                                        for i in xrange(len(hops)-1)]

    # armar_barras(hops, relative_rtts)
    armar_boxplot(hops, relative_rtts)


def armar_boxplot(hops, relative_rtts):
    fig, ax = plt.subplots(figsize=(20, 10))
    ind = np.arange(len(relative_rtts))
    mean = np.mean(relative_rtts)
    std = np.std(relative_rtts)
    zrtts = (relative_rtts-mean)/std
    ax.scatter(np.ones(len(zrtts)), zrtts, color='green', label='zrtts')
    ax.boxplot(relative_rtts)
    ax.set_xticks([])
    ax.set_ylabel('Milisegundos', size='x-large')
    ax.set_title(u'Ubicación de zrtts en la distribución '
                 'de los rtts relativos (entre saltos)', size='xx-large')

    ax.legend(fancybox=True, loc='best', prop={'size': 'xx-large'})
    ax.grid(True)
    # return fig, ax


def armar_barras(hops, relative_rtts):
    fig, ax = plt.subplots(figsize=(15, 10))
    ind = np.arange(len(relative_rtts))
    bar_width = 0.9
    rects = ax.bar(ind, relative_rtts, bar_width, alpha=0.95)
    ax.set_xticks(ind + bar_width / 2)
    ax.set_xticklabels(ind)
    ax.set_xlabel(u'Número de hop')
    ax.set_ylabel('Diferencia en milisegundos')
    ax.set_title("Rtt's entre saltos")
    ax.grid(True)

    colors = cycle(tableau20)
    for idx, rect in enumerate(rects):
        height = rect.get_height()
        # ax.text(rect.get_x() + rect.get_width()/2., 0.4*height,
        #         round(hops[idx]['rtt'], 2),
        #         ha='center', va='bottom')

        if hops[idx]['ip_address'] is None:
            rect.set_color('grey')
        else:
            # rect.set_color(colors.next())
            rect.set_color('green')

    bar_unknown = mpatches.Patch(color='grey', label='Host desconocido')
    ax.legend(handles=[bar_unknown], fancybox=True, loc='best')
    ax.set_xlim([0, max(ind)+bar_width])
    plt.tight_layout()


if __name__ == '__main__':
    basedir = 'Exp comparacion modelos/'
    files = ['CarnegieFiltrado.txt', 'OxfordFiltrado.txt', 'tokyoFiltrado.txt',
             'hiFiltrado.txt']

    for file in files:
        with open(basedir+file) as f:
            lines = f.read()
            hosts = json.loads(lines)

            main(hosts)
            fname, ext = file.split('.')
            plt.savefig('graficos/'+fname+'_box.pdf')
