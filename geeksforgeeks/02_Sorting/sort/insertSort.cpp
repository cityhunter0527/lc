// http://www.geeksforgeeks.org/insertion-sort/
// http://www.geeksforgeeks.org/binary-insertion-sort/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Loop from i = 1 to n-1.
    // a) Pick element arr[i] and insert it into sorted sequence arr[0...i-1] with binary search
    void BinaryInsertionSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            auto x = upper_bound(nums.begin(), nums.begin() + i-1, nums[i]);
            int pivot = nums[i];
            if (*x < pivot) continue; // upper_bound will return last element if there is no element larger than nums[i];
                                      // lower_bound will return last element if there is no element no less than numsi];
            for (auto y = nums.begin()+i-1; y >= x; y--) {
                *next(y) = *y;
            }
            *x = pivot;
        }
    }
    
    // return the position in which pivot should be inserted
    int binarySearch(vector<int>& nums, int start, int end, int pivot) {
        if (start < end) { // <<< should not be <= here... 
            int mid = start + (end-start)/2;
            if (nums[mid] > pivot)
                return binarySearch(nums, start, mid-1, pivot);
            else if (nums[mid] < pivot)
                return binarySearch(nums, mid+1, end, pivot);
            else
                return mid+1;
        }

        // Reach here because start >= end. 
        return pivot > nums[start]? (start+1) : start;
    }

    void BinaryInsertionSortV2(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            int loc = binarySearch(nums, 0, i-1, nums[i]); // find the location where pivot should be inserted
            int j, pivot = nums[i];
            for (j = i-1; j >= loc; j--) {
                nums[j+1] = nums[j];
            }
            nums[loc] = pivot;
        }
    }
    // Loop from i = 1 to n-1.
    // a) Pick element arr[i] and insert it into sorted sequence arr[0...i-1]
    void InsertionSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            int j, pivot = nums[i];
            for (j = i-1; j >=0 && nums[j] > pivot ; j--) {
                    nums[j+1] = nums[j];
            }
            nums[j+1] = pivot;
        }
    }
};

int main() {
#if 1
    vector<int> v = {21,3,22,45,67,99,12,5,9,20};
    Solution s;
    s.BinaryInsertionSortV2(v);  
    for (auto x:v) cout << x << ", "; 
    cout << endl;
#endif
    return 0;
}
