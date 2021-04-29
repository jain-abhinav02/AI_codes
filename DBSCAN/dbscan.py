import math
import matplotlib.pyplot as plt
import numpy as np
def next_unvisited(vis):
    for i in range(len(vis)):
        if vis[i]==0: return i
    return -1

def dis(x1,y1,x2,y2):
    delta_x = x1-x2
    delta_y = y1-y2
    return math.sqrt(delta_x**2 + delta_y**2)
 
n = int(input("Number of points:"))
print(n)
print("Enter the points")
x = []
y = []
for i in range(n):
    x_i, y_i = input().split(" ")
    x.append(float(x_i))
    y.append(float(y_i))
eps = float(input("Enter epsilon:"))
minPts = int(input("Minimum number of points:"))
vis = [0]*n
cur = 0
while True:
    idx = next_unvisited(vis)
    if idx == -1:
        break
    cur += 1
    vis[idx] = cur
    cluster = [idx]   
    for pt in cluster:
        N = []
        for i in range(n):
            if i==pt:
                continue
            if dis(x[pt],y[pt],x[i],y[i]) < eps:
                N.append(i)
        if len(N) < minPts-1 :
            if pt == idx:
                vis[idx]=-1
                cur -= 1
            continue
        for i in N:
            if vis[i]==0:
                vis[i]=cur
                cluster.append(i)
            elif vis[i]==-1:
                vis[i]=cur
print("Cluster number for each of the above points")
for i in range(n):
    if vis[i] == -1:
        vis[i] = 0
    print(vis[i],end=" ")
color_map = np.array([np.random.rand(3,) for i in range(cur+1)])
color_map[0]=[0,0,0]
plt.figure("Clusters")
plt.scatter(x,y,c=color_map[vis])
plt.savefig("Clusters.png")
#plt.show()
