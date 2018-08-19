/*
 * http://www.geeksforgeeks.org/counting-inversions/
 * http://www.geeksforgeeks.org/count-inversions-in-an-array-set-2-using-self-balancing-bst/
 * http://www.geeksforgeeks.org/counting-inversions-using-set-in-c-stl/
 * http://www.geeksforgeeks.org/count-inversions-array-set-3-using-bit/
 * */

//
// Inversion Count for an array indicates - how far (or close) the array is from being sorted. 
// If array is already sorted then inversion count is 0. 
// If array is sorted in reverse order that inversion count is the maximum. 
//
// Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j
//
// Example:
// The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
// 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solutoin {
    // [start...mid] and [mid+1, end) are both sorted.
    int Merge(vector<int>& arr, int start, int mid, int end) {
        vector<int> left(mid-start+1), right(end-mid);
        copy(arr.begin()+start, arr.begin()+mid+1, left.begin());
        copy(arr.begin()+mid+1, arr.begin()+end+1, right.begin());
        int i = 0, j = 0, k = start, invCnt = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
                invCnt += end-mid;
            }
        }
        // no need to update invCnt again here 
        if (i < left.size()) { 
            copy(left.begin()+i, left.end(), arr.begin()+k);
        } else if (j < right.size()) {
            copy(right.begin()+j, right.end(), arr.begin()+k);
        }
        return invCnt;
    }
    int MergeSort(vector<int>& arr, int start, int end) {
        int invCnt = 0;
        if (start < end) {
            int mid = start + (end - start)/2;
            invCnt += MergeSort(arr, start, mid);
            invCnt += MergeSort(arr, mid+1, end);
            invCnt += Merge(arr, start, mid, end);
        }
        return invCnt;
    }
public:
    int CountInversions(vector<int>& arr) {
        return MergeSort(arr, 0, arr.size()-1);
    }
};

int main() {
    vector<int> v = {2,4,1,3,5};
    Solutoin s;
    cout << s.CountInversions(v) << endl;
    return 0;
}
