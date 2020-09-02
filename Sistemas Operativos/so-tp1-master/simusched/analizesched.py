#!/usr/bin/env python
# coding: utf-8

import sys
from graphsched import parseData, dataGantt
from graphsched import LOAD, CPU, BLOCK, UNBLOCK, EXIT, DEADLINE, CMDS


def analize_one(task):
    latencia = 0
    for tm, cmd, core in task:
        if cmd == LOAD:
            latencia = -tm
            continue
        latencia += tm
        break

    start = 0
    end = 0
    cpus = 0
    for tm, cmd, core in task:
        if cmd == LOAD:
            start = tm
        elif cmd == EXIT:
            end = tm
        elif cmd == CPU:
            cpus += 1

    return {
        'latencia': latencia,
        'waiting_time': end - start - cpus
    }


def analize_all(gantt):
    d = {}
    n = 0
    t = []
    max_tm = 0
    for pid, task in gantt.items():
        if pid == -1:
            continue
        r = analize_one(task)
        d['task_' + str(pid)] = r
        t.append(r)
        n += 1

        max_tm = max(max_tm, max([tm for tm, cmd, _ in task if cmd == EXIT]))

    d['promedio'] = {
        'latencia': sum(i['latencia'] for i in t) / float(n),
        'waiting_time': sum(i['waiting_time'] for i in t) / float(n),
        'cantidad_tareas': n,
        'tiempo_total': max_tm,
        'throughput': float((n * 1000) / max_tm) / 1000,
    }

    return d


def printGantt(gantt):
    print '{'
    for name, data in gantt.items():
        print '  %s: [' % name
        for tm, cmd, core in data:
            print '    t %s \t@ %s\t%s' % (tm, core, CMDS[cmd])
        print '  ]'
    print '}'


def main(argv):
    if len(argv) <= 1:
        fin = sys.stdin
        fout = sys.stdout
    else:
        fin = open(argv[1], 'r')
        fout = open(argv[1] + '.liz', 'w')

    with fin, fout:
        settings, data, cores = parseData(fin)
        gantt = dataGantt(data, cores)

        # printGantt(gantt)
        # exit()

        result = analize_all(gantt)

        import json
        fout.write(json.dumps(result, sort_keys=True, indent=4))


if __name__ == "__main__":
    main(sys.argv)
