/*
 * 4. Median of Two Sorted Arrays
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 *
 * Example 1:
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 * Example 2:
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 * */

#include <iostream>
#include <vector>
using namespace std;
class Solution {
private:
    // 
    // Find k-th smallest element in sorted array: v1 and v2;
    // Every call of kth we identify k/2 elements in v1 or v2 that could be eliminated, 
    // Repeat it until m is 0 or k is 1;
    //
    int kth(int v1[], int m, int v2[], int n, int k) {
        // let m < n, it is necessary to meet edge conditions to only check m == 0;
        if (m > n)
            return kth(v2, n, v1, m, k);
        if (m == 0)
            return v2[k-1];
        if (k == 1)
            return min(v1[0], v2[0]);
        // every time we identify number of "k/2" elements in v1 or v2 that could be eliminated.
        int i = min(m, k/2), j = min(n, k/2);
        if (v1[i-1] < v2[j-1]) 
            return kth(v1+i, m-i, v2, n, k-i);
        else 
            return kth(v1, m, v2+j, n-j, k-j);
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if ((m+n)%2)
            return kth(nums1.data(), m, nums2.data(), n, (m+n+1)/2); // odd
        else 
            return (kth(nums1.data(), m, nums2.data(), n, (m+n+1)/2) + kth(nums1.data(), m, nums2.data(), n, (m+n+2)/2)) / 2.0; // even
    }
};

int main() {
    vector<int> v1 = {1, 3};
    vector<int> v2 = {2};
    Solution s;
    cout << s.findMedianSortedArrays(v1, v2) << endl;

    v1 = {1,2};
    v2 = {3,4};
    cout << s.findMedianSortedArrays(v1, v2) << endl;

    
    
    return 1;
}
