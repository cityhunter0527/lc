/* 
 * http://www.geeksforgeeks.org/quick-sort/
 * 
 * algorithm quicksort(A, lo, hi) is
    if lo < hi then
        p := partition(A, lo, hi)
        quicksort(A, lo, p - 1 )
        quicksort(A, p + 1, hi)

algorithm partition(A, lo, hi) is
    pivot := A[hi]
    i := lo - 1    
    for j := lo to hi - 1 do
        if A[j] < pivot then
            i := i + 1
            swap A[i] with A[j]
    if A[hi] < A[i + 1] then
        swap A[i + 1] with A[hi]
    return i + 1
 *
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void QuickSort(vector<int>& arr, int l, int r) {
        if (l < r) {
            int pi = partition(arr, l, r); // <<< get location of pivot;
            QuickSort(arr, l, pi-1);
            QuickSort(arr, pi+1, r);
        }
    }
private:
    // pick up a pivot and move all elements smaller than pivot to left
    // move all elements larger than pivot to right
    // return the index of pivot
    int partition(vector<int>& arr, int l, int r) {
        int pivot = arr[r];
        int i = l-1; // i points to the last index that arr[i] < pivot
        for (int j = l; j < r; j++) {
            if (arr[j] < pivot) {
                swap(arr[++i], arr[j]);
            }
        }
        // now move pivot to correct position
        swap(arr[i+1], arr[r]);
        return i+1;
    }
};

int main() {
    vector<int> v = {21,3,22,45,67,99,12,5,9,20};
    Solution s;
    s.QuickSort(v, 0, v.size()-1);
    for (auto x:v) cout << x << ",";
    cout << endl;
    return 0;
}
