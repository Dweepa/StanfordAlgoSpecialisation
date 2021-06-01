"""
W1 Kosaraju Algorithm
"""
import sys, threading
import pickle

########################################################
# Data Structures

num_nodes = 9
#875715

gr = [[] for i in range(num_nodes)]
r_gr = [[] for i in range(num_nodes)]

visited = [False] * num_nodes

scc = []

stack = []  # Stack for retaining order of DFS on reversed list

########################################################
# Importing the graphs
file = open("sample.txt", "r")
data = file.readlines()
for line in data:
    items = line.split()
    gr[int(items[0])] += [int(items[1])]
    r_gr[int(items[1])] += [int(items[0])]

print("Read graph from file - Completed")

########################################################
# DFS on reverse graph

def fillOrder(v):
        visited[v]= True
        for i in r_gr[v]:
            if not visited[i]:
                fillOrder(i)
        stack.append(v)

for i in range(num_nodes):
    if visited[i]==False:
        fillOrder(i)

print(stack)
print("Fill DFS order of reversed graph - Completed")

########################################################
# DFS on graph
visited = [False] * len(visited)  # Resetting the visited variable

def DFSUtil(v, lenOfSCC):
        visited[v]= True
        lenOfSCC[0]+=1
        print(v, end=' ')
        for i in gr[v]:
            if not visited[i]:
                DFSUtil(i, lenOfSCC)

while stack:
    node = stack.pop()
    if not node:
        continue
    if not visited[node]:
        len = [0]
        DFSUtil(node, len)
        scc.append(len[0])
        print("")

print("Strongly connected components - Completed")

########################################################
# Getting the five biggest sccs
scc.sort(reverse=True)
print(scc[:5])

# [434821, 968, 459, 313, 211]
