# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <codecell>

import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import random as rd
%matplotlib inline 

# <codecell>

N = 100
M = 120
MAX = N + M + 1
MAX_EDGE = 1000
MAX_DEG = 450
ITERATIONS = 100000
S1 = 0.
T1 = 1.
S2 = 0.
T2 = 1.
beta = 0.1

# <codecell>

# initial fraction of cooperators
p1, p2 = .5, .5
# number of cooperators
cc1, cc2 = 0, 0
# fraction of cooperators
r1, r2 = np.zeros(ITERATIONS + 1, dtype=np.float), np.zeros(ITERATIONS + 1, dtype=np.float)

payoff = np.array(
        [
            [1, S1],
            [T1, 0]
        ]
        , dtype=np.float, ndmin=2)

payoff2 = np.array(
        [
            [1, S2],
            [T2, 0]
        ]
        , dtype=np.float, ndmin=2)

# <codecell>

def interaction(x, y):
    if x < N:
        return payoff[g.node[x]['strategy']][g.node[y]['strategy']]
    else:
        return payoff2[g.node[x]['strategy']][g.node[y]['strategy']]


def change_prob(x, y):
    return 1. / (1 + np.exp(-beta * (y - x)))


def complete():
    return nx.complete_bipartite_graph(N, M)


def random():
    g = nx.Graph()
    g.add_nodes_from(np.arange(0, N + M, 1, dtype=np.int))
    while g.number_of_edges() < MAX_EDGE:
        a, b = rd.randint(0, N - 1), rd.randint(N, N + M - 1)
        if b not in g[a]:
            g.add_edge(a, b)

    return g


def set_initial_strategy(g):
    global cc1, cc2
    coop = range(0, int(p1 * N), 1) + range(N, int(p2 * M) + N, 1)
    cc1 = int(p1 * N)
    defect = set(range(0, N + M, 1)) - set(coop)
    cc2 = int(p2 * M)
    coop = dict(zip(coop, len(coop) * [0]))
    defect = dict(zip(defect, len(defect) * [1]))
    nx.set_node_attributes(g, 'strategy', coop)
    nx.set_node_attributes(g, 'strategy', defect)


def fitness(x):
    ret = 0
    for i in g.neighbors(x):
        ret += interaction(x, i)
    return ret


def simulate():
    global cc1, cc2
    it = 0
    while it < ITERATIONS:
        it += 1
        if it % 2:
            a = rd.randint(0, N - 1)
        else:
            a = rd.randint(N, N + M - 1)
        if len(g.neighbors(a)) == 0:
            it -= 1
            continue
        b = g.neighbors(a)[rd.randint(0, len(g.neighbors(a)) - 1)]
        b = g.neighbors(b)[rd.randint(0, len(g.neighbors(b)) - 1)]
        if a == b:
            it -= 1
            continue

        assert (a < N and b < N) or (a >= N and b >= N)
        if g.node[a]['strategy'] != g.node[b]['strategy']:
            fa, fb = fitness(a), fitness(b)
            l = np.random.random()
            p = change_prob(fa, fb)
            if l <= p:
                if a < N:
                    if g.node[a]['strategy'] == 0:
                        cc1 -= 1
                    else:
                        cc1 += 1
                else:
                    if g.node[a]['strategy'] == 0:
                        cc2 -= 1
                    else:
                        cc2 += 1
                nx.set_node_attributes(g, 'strategy', { a:g.node[b]['strategy'] })

        r1[it] = float(cc1) / N
        r2[it] = float(cc2) / M

    #print('simulation finished')

# <codecell>

# g = complete()
g = random()

set_initial_strategy(g)

pos = nx.shell_layout(g)
labels = { }
for i in xrange(0, N + M, 1):
    labels[i] = 'C' if g.node[i]['strategy'] == 0 else 'D'
nx.draw_networkx_nodes(g, pos, nodelist=range(0, N, 1), node_color='r')
nx.draw_networkx_nodes(g, pos, nodelist=range(N, N + M, 1), node_color='b')
nx.draw_networkx_edges(g, pos, width=1.0, alpha=0.5)
nx.draw_networkx_labels(g, pos, labels, font_color='w')

plt.show()

# <codecell>

simulate()

labels = { }
for i in xrange(0, N + M, 1):
    labels[i] = 'C' if g.node[i]['strategy'] == 0 else 'D'
nx.draw_networkx_nodes(g, pos, nodelist=range(0, N, 1), node_color='r')
nx.draw_networkx_nodes(g, pos, nodelist=range(N, N + M, 1), node_color='b', node_shape='s')
nx.draw_networkx_edges(g, pos, width=1.0, alpha=0.5)
nx.draw_networkx_labels(g, pos, labels, font_color='w')

plt.show()

# <codecell>

plt.plot(r1, color='r')
plt.plot(r2, color='b')
plt.show()

# <codecell>

nbins = 20
Trange = np.linspace(1,2,nbins)
Srange = np.linspace(-1,0,nbins)
mag1 = np.zeros((nbins, nbins), dtype=np.float)
mag2 = np.zeros((nbins, nbins), dtype=np.float)

i = 0
for S1 in Srange:
    S2 = S1
    j = 0
    for T1 in Trange:
        global payoff, payoff2
        T2 = T1
        
        payoff = np.array(
        [
            [1, S1],
            [T1, 0]
        ]
        , dtype=np.float, ndmin=2)

        payoff2 = np.array(
        [
            [1, S2],
            [T2, 0]
        ]
        , dtype=np.float, ndmin=2)
        
        set_initial_strategy(g)
        simulate()
        
        if np.std(r1[-1000:]) > 0.01 or np.std(r2[-1000:]) > 0.01:
            print("Std grater than 0.1", T1, S1)
        mag1[i][j] = np.mean(r1[-1000:])
        mag2[i][j] = np.mean(r2[-1000:])
        j += 1
    i += 1
    
plt.imshow(mag1, extent=[1, 2, -1, 0], aspect="auto", origin="lower")
plt.colorbar()
plt.title("Population 1")
plt.xlabel("T")
plt.ylabel("S")

# <codecell>

plt.imshow(mag2, extent=[1, 2, -1, 0], aspect="auto", origin="lower")
plt.colorbar()
plt.title("Population 2")
plt.xlabel("T")
plt.ylabel("S")

# <codecell>


