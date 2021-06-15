MAX = 1000000

file = open("prims.txt", "r")
data = file.readlines()
vertices = int(data[0].split()[0])
graph = [[MAX for i in range(vertices+1)] for i in range(vertices+1)]
for line in data[1:]:
    left, right, cost = line.split()
    graph[int(left)][int(right)] = int(cost)
    graph[int(right)][int(left)] = int(cost)

visited = [0 for i in range(vertices+1)]
distance_array = [ MAX for i in range(vertices+1) ]
sp_set = [ False for i in range(vertices+1) ]

def findMin(p_set, distance_array):
    # find the minimum of the distance_array
    min_value = MAX
    min_index = 0
    for vertex in range(1, len(distance_array)):
        if((not sp_set[vertex]) and distance_array[vertex]<min_value):
            min_value  = distance_array[vertex];
            min_index = vertex;
    return min_index;



def prims():
    # distance from source to itself is 0
    distance_array[1] = 0

    # run loop for all vertices
    for count in range(vertices):
        # find vertex with the minimum distance to source
        vertex = findMin(sp_set, distance_array)
        sp_set[vertex] = True

        # calculate distance of adjacent vertices
        for adjacent_vertex in range(1,vertices+1):
            if((graph[vertex][adjacent_vertex]!=MAX)
            and (not sp_set[adjacent_vertex])
            and distance_array[vertex]!=MAX):
                distance_array[adjacent_vertex] = min(distance_array[adjacent_vertex],
                graph[vertex][adjacent_vertex])

prims()

print(sum(distance_array[1:])) # -3612829
