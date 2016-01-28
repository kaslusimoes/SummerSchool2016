from pickle import dump, load
import networkx as nx
import os
import matplotlib.pyplot as plt
p = './matrices/'
for _,_,c in os.walk(p):
	for a,x in enumerate(c):
		pp = os.path.join(p,x)
		f = open(pp, 'r')
		g = nx.Graph()
		lines = []
		while True:
			dr = f.readline()
			if dr=='':
				break
			lines.append(dr)
		f.close()
		N = len(lines)
		M = len(lines[0].split())
		for x in range(0, N+M):
			g.add_node(x)
		for i,l in enumerate(lines):
			s = l.split()
			for j, o in enumerate(s):
				if o == '1':
					g.add_edge(i, N+j)
		f = open(os.path.join(p, 'g{0}'.format(a)), 'wb')
		dump(g,f)
		f.close()
