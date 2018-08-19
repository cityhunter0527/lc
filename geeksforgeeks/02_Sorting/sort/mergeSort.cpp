/*
 * MergeSort(arr[], l,  r)
   If r > l
     1. Find the middle point to divide the array into two halves:  
             middle m = (l+r)/2
     2. Call mergeSort for first half:   
             Call mergeSort(arr, l, m)
     3. Call mergeSort for second half:
             Call mergeSort(arr, m+1, r)
     4. Merge the two halves sorted in step 2 and 3:
             Call merge(arr, l, m, r)
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
    
class Solution {
private:
    // merge [l..m] and [m+1...r] which are both sorted.
    // Space: O(n);
    // For O(1) Space Complexity, refer to Merge Two Sorted Array with O(1) Space.
    void Merge(vector<int>& arr, int l, int m, int r) {
        vector<int> left(m-l+1), right(r-m);
        copy(arr.begin()+l, arr.begin()+m+1, left.begin()); // <<< according to std::copy, the 2nd parameter should be the last element in source + 1;
        copy(arr.begin()+m+1, arr.begin()+r+1, right.begin());
        int i = 0, j = 0, k = l;
        while (i < left.size() && j < right.size()) {
            if (left[i] > right[j])
                arr[k++] = right[j++];
            else 
                arr[k++] = left[i++];
        }
        if (i < left.size()) 
            copy(left.begin()+i, left.end(), arr.begin()+k);
        else if (j < right.size())
            copy(right.begin()+j, right.end(), arr.begin()+k);
    }
public:
    void MergeSort(vector<int>& arr, int l, int r) {
        if (l < r) {
            int mid = l + (r-l)/2;
            MergeSort(arr, l, mid);
            MergeSort(arr, mid+1, r);
            Merge(arr, l, mid, r);
        }
    }
};
int main() {
    vector<int> v = {21,3,22,45,67,99,12,5,9,20};
    Solution s;
    s.MergeSort(v, 0, v.size()-1);
    for (auto x:v) cout << x << ", ";
    cout << endl;
    return 0;
}
