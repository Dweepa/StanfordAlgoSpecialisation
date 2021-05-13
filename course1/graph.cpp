#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <cstdlib>
using namespace std;

vector<vector<int>> initiliseGraphFromFile(string filename){
  //Initialise file pointer
  vector<vector<int>> graph;
  ifstream input(filename);
	string line;
	if (input.is_open()){
		while (input.good()){
      int vertex, node;
      getline(input,line);
      stringstream ss(line);
      if(!ss.eof()){
        ss >> node; // we don't need the node value
        vector<int> vertices;
        while(ss >> vertex){
          vertices.push_back(vertex);
        }
        graph.push_back(vertices);
      }
    }
	}
  graph.pop_back(); //Delete the last empty line
  return graph;
}

void printGraph(vector<vector<int>> graph){
  cout<<endl;
  for(int i=0; i<graph.size(); i++){
    cout<<i+1<<": ";
    for(int j=0; j<graph[i].size(); j++){
      cout<<graph[i][j]<<" ";
    }
    cout<<endl;
  }
}

vector<int> fuse(vector<int>& node1, vector<int>& node2, int node1index, int node2index){
  // Delete self loops from nodes 1 and 2
  for (int i = 0; i < node1.size(); i++) {
		if (node1[i] == node2index + 1) {
			node1.erase(node1.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < node2.size(); i++) {
		if (node2[i] == node1index + 1) {
			node2.erase(node2.begin() + i);
			i--;
		}
	}
  //concatenate the two nodes to create the fused node
  node1.insert(node1.end(), node2.begin(), node2.end());

  return node1;
}

void updateGraph(vector<vector<int>>& graph, int node1Index, int node2Index){
  for (int i = 0; i < graph.size(); i++){
		for (int j = 0; j < graph[i].size(); j++){
			//node is the one of the fused nodes
			if (graph[i][j] == node1Index + 1 || graph[i][j] == node2Index + 1){
				graph[i][j] = graph.size(); // fused node is the last node
			}
			//node is between the chosen two, decrement by 1
			else if ((graph[i][j] > node1Index + 1 && graph[i][j] < node2Index + 1) ||
      (graph[i][j] > node2Index + 1 && graph[i][j] < node1Index + 1)){
				graph[i][j] --;
			}
			//node is after chosen two, decrement by 2
			else if (graph[i][j] > node1Index + 1 && graph[i][j] > node2Index + 1){
				graph[i][j] = graph[i][j] - 2;
			}
		}
	}
}

int findMinCut(vector<vector<int>>& graph){
  while(graph.size()>2){ // min cut not reached
    int node1index = rand() % graph.size(); // randomly select index for node 1
    vector<int> node1 = graph[node1index];

    int node2index = rand() % node1.size(); // randomly select adjacent index for node 2
    node2index = graph[node1index][node2index] - 1; // indices start from 0 but adjacency list representation starts from 1
    vector<int> node2 = graph[node2index];

    if(node1index > node2index){
      graph.erase(graph.begin()+node1index); // erase the grater index first
      graph.erase(graph.begin()+node2index);
    }
    else{
      graph.erase(graph.begin()+node2index);
      graph.erase(graph.begin()+node1index);
    }
    vector<int> fusedNode = fuse(node1, node2, node1index, node2index);
    graph.push_back(fusedNode); // add new fused node to the end of the graph
    updateGraph(graph, node1index, node2index);
  }
  return graph[0].size(); // return the number of edges between the 2 remaining nodes
}

/* Main */
int main()
{
  /* initilise graph data structure (adjacency list)
  graph[0] -> [v1, v2, v3, v4...] (list of vertices for node 1) */
  vector<vector<int>> graph = initiliseGraphFromFile("input.txt");
  vector<vector<int>> copyOfGraph(graph); // make a copy for iterations > 1

  int minCut=INT_MAX;
  for(int i=0; i<graph.size(); i++){
    cout<<"Iteration: "<<i<<" ";
    int currMinCut = findMinCut(graph);
    minCut = min(minCut, currMinCut);

    //reset graph
    graph.clear();
    graph.insert(graph.begin(), copyOfGraph.begin(), copyOfGraph.end());

  }
  cout<<endl<<"min cut: "<<minCut<<endl;

  return 0;

}
