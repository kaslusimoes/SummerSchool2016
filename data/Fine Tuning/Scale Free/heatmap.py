from pickle import load
import os
import matplotlib.pyplot as plt
import numpy as np

class Data:
  def __init__(self):
    self.m_list1 = []
    self.m_list2 = []

p = './data/'

m1 = []
m2 = []

for _,_,c in os.walk(p):
  for x in c:
    print('\n',x,'\n')
    f = open(os.path.join(p,x), 'r')
    d = load(f)
    lm = [x for _,_,_,_,x in d.m_list1]
    hm = np.sum(lm,0)/10.
    m1.append(hm)
    lm = [x for _,_,_,_,x in d.m_list2]
    hm = np.sum(lm,0)/10. 
    m2.append(hm)

sm1 = np.mean(m1,0)
sm2 = np.mean(m2,0)
plt.imshow(sm1, extent=[1, 2, -1, 0], aspect="auto", origin="lower")
plt.colorbar()
plt.title("Population 1")
plt.xlabel("T")
plt.ylabel("S")
plt.savefig("heatmap1_ft_scalefree.png")

plt.clf()

plt.imshow(sm2, extent=[1, 2, -1, 0], aspect="auto", origin="lower")
plt.colorbar()
plt.title("Population 2")
plt.xlabel("T")
plt.ylabel("S")
plt.savefig("heatmap2_ft_scalefree.png")