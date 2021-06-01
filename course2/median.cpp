/*
Your task is to code up the algorithm from the video lectures for computing strongly connected components
(SCCs), and to run this algorithm on the given graph.

Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in decreasing order of
sizes, separated by commas (avoid any spaces). So if your algorithm computes the sizes of the five largest
SCCs to be 500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100" (without the quotes).
 If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms. Thus, if your algorithm
 computes only 3 SCCs whose sizes are 400, 300, and 100, then your answer should be "400,300,100,0,0"
 (without the quotes).  (Note also that your answer should not have any spaces in it.)

WARNING: This is the most challenging programming assignment of the course. Because of the size of the graph
you may have to manage memory carefully. The best way to do this depends on your programming language and
environment, and we strongly suggest that you exchange tips for doing this on the discussion forums.*/

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <cstdlib>
#include <queue>
using namespace std;

vector<int> initiliseArrayFromFile(string filename){
  //Initialise file pointer
  vector<int> array;
  ifstream input(filename);
	string line;
	if (input.is_open()){
		while (input.good()){
      getline(input,line);
      stringstream ss(line);
      if(!ss.eof()){
        int num;
        ss >> num; // node number
        array.push_back(num);
      }
    }
	}
  array.pop_back(); //Delete the last empty line
  return array;
}

void printVector(vector<int> vec){
  for(int v: vec) cout<<v<<" ";
  cout<<endl;
}

int negative(int a){
  return a * -1;
}

void showpq(priority_queue<int> gq)
{
    priority_queue<int> g = gq;
    while (!g.empty()) {
        cout <<g.top()<<" ";
        g.pop();
    }
    cout << endl;
}

int findMedian(int index,
  priority_queue<int>& left_heap,
  priority_queue<int>& right_heap) {
    int left = left_heap.size();
    int right = right_heap.size();
    int median;

    if(left==0 && right==0){
      left_heap.push(index);
      return index;
    }

    if(left < right)
      median = negative(right_heap.top());
    else
      median = left_heap.top();

    if(left > right) {
      if(index < median){
        right_heap.push(negative(left_heap.top()));
        left_heap.pop();
        left_heap.push(index);
      }
      else{
        right_heap.push(negative(index));
      }
    }
    else if(left < right){
      if(index > median){
        left_heap.push(negative(right_heap.top()));
        right_heap.pop();
        right_heap.push(negative(index));
      }
      else{
        left_heap.push(index);
      }
    }
    else {
      if(index < median){
        left_heap.push(index);
      }
      else{
        right_heap.push(negative(index));
      }
    }

    if(right_heap.size() > left_heap.size())
      return negative(right_heap.top());
    else
      return left_heap.top();

}
/* Main */
int main()
{
  vector<int> array = initiliseArrayFromFile("input.txt");
  printVector(array);
  int sumOfMedians=0;

  priority_queue<int> left_heap; // max heap
  priority_queue<int> right_heap; // min heap

  for(int element : array){
    int median = findMedian(element, left_heap, right_heap);
    sumOfMedians+=median;
    cout<<"sum - "<<sumOfMedians<<endl;
  }
  cout<<sumOfMedians%10000<<endl;
  return 0;

}
