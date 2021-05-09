#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

void swap(vector<int>& arr, int a, int b)
{
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

/* quicksortFirst */
int partitionAroundPivotFirst(vector<int>& arr, int left, int right){
  int pivot = arr[left];
  int i = left + 1;
  for(int j=left+1; j<=right; j++){
    if(arr[j]<pivot){
      swap(arr,i,j);
      i++;
    }
  }
  swap(arr,left,i-1);

  // for(int i: arr) cout<<i<<" ";
  // cout<<"comparisons: "<<right-left<<endl;

  return i-1;
}

int quicksortFirst(vector<int>& arr, int left, int right){
  if(left<right){
    int partition = partitionAroundPivotFirst(arr, left, right);
    int comparisonsLeft = quicksortFirst(arr, left, partition-1);
    int comparisonsRight = quicksortFirst(arr, partition+1, right);
    return (right-left) + comparisonsLeft + comparisonsRight;
  }
  return 0;
}

/* quicksortLast */
int partitionAroundPivotLast(vector<int>& arr, int left, int right){
  int pivot = arr[right];
  swap(arr,right,left);
  int i = left + 1;
  for(int j=left+1; j<=right; j++){
    if(arr[j]<pivot){
      swap(arr,i,j);
      i++;
    }
  }
  swap(arr,left,i-1);

  // for(int i: arr) cout<<i<<" ";
  // cout<<"comparisons: "<<right-left<<endl;

  return i-1;
}

int quicksortLast(vector<int>& arr, int left, int right){
  if(left<right){
    int partition = partitionAroundPivotLast(arr, left, right);
    int comparisonsLeft = quicksortLast(arr, left, partition-1);
    int comparisonsRight = quicksortLast(arr, partition+1, right);
    return (right-left) + comparisonsLeft + comparisonsRight;
  }
  return 0;
}

/* quicksortMedianOf3 */
int findMedian(int a, int b, int c){
  if ((a < b && b < c) || (c < b && b < a)) return 1;
  else if ((b < a && a < c) || (c < a && a < b)) return 0;
  else return 2;
}

int medianOf3(vector<int> arr, int left, int right)
{
  int mid = (left + right)/2;
  int median = findMedian(arr[left], arr[mid], arr[right]);
  switch(median){
    case 0: return left;
    case 1: return mid;
    case 2: return right;
  }
  return 0;
}

int partitionAroundPivotMedianOf3(vector<int>& arr, int left, int right){
  int pivotIndex = medianOf3(arr, left, right);
  int pivot = arr[pivotIndex];
  swap(arr,pivotIndex,left);
  int i = left + 1;
  for(int j=left+1; j<=right; j++){
    if(arr[j]<pivot){
      swap(arr,i,j);
      i++;
    }
  }
  swap(arr,left,i-1);

  // for(int i: arr) cout<<i<<" ";
  // cout<<"comparisons: "<<right-left<<endl;

  return i-1;
}

int quicksortMedianOf3(vector<int>& arr, int left, int right){
  if(left<right){
    int partition = partitionAroundPivotMedianOf3(arr, left, right);
    int comparisonsLeft = quicksortMedianOf3(arr, left, partition-1);
    int comparisonsRight = quicksortMedianOf3(arr, partition+1, right);
    return (right-left) + comparisonsLeft + comparisonsRight;
  }
  return 0;
}

/* Main */
int main()
{
  vector<int> arr;
	ifstream in("input.txt",ios::in);
	int number;
    while (in >> number) {
		arr.push_back(number);
	}
	in.close();

  // for(int i: arr) cout<<i<<" ";
  // cout<<endl;

  vector<int> copyArr1(arr);
  int numberOfComparisons = quicksortFirst(copyArr1,0,copyArr1.size()-1);
  // for(int i: copyArr1) cout<<i<<" ";
  cout << "Number of comparisons (first): " << numberOfComparisons << endl;

  vector<int> copyArr2(arr);
  numberOfComparisons = quicksortLast(copyArr2,0,copyArr2.size()-1);
  // for(int i: copyArr2) cout<<i<<" ";
  cout << "Number of comparisons (last): " << numberOfComparisons << endl;

  vector<int> copyArr3(arr);
  numberOfComparisons = quicksortMedianOf3(copyArr3,0,copyArr3.size()-1);
  // for(int i: copyArr3) cout<<i<<" ";
  cout << "Number of comparisons (medianOf3): " << numberOfComparisons << endl;


  sort(arr.begin(), arr.end());
  string sorted = ((copyArr1==arr) && (copyArr2==arr) && (copyArr3==arr)) ? "yes": "no";
  cout <<"Sorted: " << sorted << endl;

  return 0;
}
