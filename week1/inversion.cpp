#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

long long countSplitInversions(vector<int> left, vector<int> right, vector<int>& sortedArr){
    int leftLen = left.size();
    int rightLen = right.size();
    int i=0, j=0;
    long long splits=0;
    while(i<leftLen && j<rightLen){
        if(left[i]<=right[j]){
            sortedArr.push_back(left[i]);
            i++;
        }
        else{
            splits+= (leftLen-i);
            sortedArr.push_back(right[i]);
            j++;
        }
    }
    return splits;
}

long long countInversions(vector<int> arr, int start, int end, vector<int>& sortedArr){
    sortedArr = {arr.begin()+start, arr.begin()+end+1};
    sort(sortedArr.begin(), sortedArr.end());

    if(start==end) {
        return 0;
    }

    else if((end-start)==1){
        if(arr[start]>arr[end]) {
            return 1;
        }
    }

    int mid = (start+end)/2;

    vector<int> sortedMerge, sortedLeft, sortedRight;

    long long left = countInversions(arr, start, mid, sortedLeft);
    long long right = countInversions(arr, mid+1, end, sortedRight);
    long long splits = countSplitInversions(sortedLeft, sortedRight, sortedMerge);

    cout<<"Splits between "<<start<<" and "<<end<<" :"<<left+right+splits<<endl;
    return left+right+splits;
}

int main()
{
  vector<int> arr;
	ifstream in("input.txt",ios::in);
	int number;
    while (in >> number) {
		arr.push_back(number);
	}
	in.close();

	cout<<"Length of the input: "<<arr.size()<<endl;

    vector<int> sortedArr;
    long long inversions = countInversions(arr,0,arr.size()-1,sortedArr);
    cout<<"Number of Inversions: "<<inversions<<endl;

    return 0;
}
