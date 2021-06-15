size = 200
MAX = 1000000
graph = [[-1 for i in range(size+1)] for i in range(size+1)]
file = open("input.txt", "r")
data = file.readlines()
for line in data:
    items = line.split()
    node = items[0]
    for item in items[1:]:
        adj, distance = item.split(",")
        graph[int(node)][int(adj)] = int(distance)

distance_array = [ MAX for i in range(size+1) ]
sp_set = [ False for i in range(size+1) ]


def findMin(p_set, distance_array):
    # find the minimum of the distance_array
    min_value = 1000000
    min_index = 0
    for vertex in range(1, len(distance_array)):
        if((not sp_set[vertex]) and distance_array[vertex]<min_value):
            min_value  = distance_array[vertex];
            min_index = vertex;
    return min_index;



def djikstra():
    MAX = 1000000;

    # distance from source to itself is 0
    distance_array[1] = 0

    # run loop for all vertices
    for count in range(size):
        # find vertex with the minimum distance to source
        vertex = findMin(sp_set, distance_array)
        sp_set[vertex] = True

        # calculate distance of adjacent vertices
        for adjacent_vertex in range(1,size+1):
            if((graph[vertex][adjacent_vertex]!=-1)
            and (not sp_set[adjacent_vertex])
            and distance_array[vertex]!=MAX):
                distance_array[adjacent_vertex] = min(distance_array[adjacent_vertex],
                distance_array[vertex] + graph[vertex][adjacent_vertex])

djikstra()

l= [7,37,59,82,99,115,133,165,188,197]
for i in l:
    print(distance_array[i], end=',')
    
# 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
