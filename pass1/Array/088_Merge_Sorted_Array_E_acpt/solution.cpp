/*
 * 88. Merge Sorted Array
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
 *
 * Note:
 * You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold 
 * additional elements from nums2. The 
 * number of elements initialized in nums1 and nums2 are m and n respectively.
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = m-1, j = n-1, k = m+n-1; i >=0 || j>=0; k--) {
            if (i < 0 || (j >=0 && nums1[i] < nums2[j])) {
                nums1[k] = nums2[j--];
            } else { // i >=0 &&  (j < 0 || nums1[i] >= nums2[j])
                nums1[k] = nums1[i--];
            }
        }
    }
};

int main() {
    vector<int> nums1;
    vector<int> nums2 = {1};
    nums1.resize(1);
    Solution s;
    s.merge(nums1, 0, nums2, nums2.size());
    for (auto x:nums1)
        cout << x << ",";
    cout << endl;
    return 1;
}

