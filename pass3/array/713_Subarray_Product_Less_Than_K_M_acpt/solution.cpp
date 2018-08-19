/*
 * 713. Subarray Product Less Than K
 * Your are given an array of positive integers nums.
 * Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.
 *
 * Example 1:
 * Input: nums = [10, 5, 2, 6], k = 100
 * Output: 8
 * Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
 * Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 * Note:
 *
 * 0 < nums.length <= 50000.
 * 0 < nums[i] < 1000.
 * 0 <= k < 10^6.
 * */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Sliding Window
    // left: left index of window
    // right: right index of window
    // for every valid window, while right is moving forward, 
    // the increased num of results is: 
    //      right - left + 1
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        unsigned long long prod = 1;
        int left = 0, right = 0, ans = 0;
        for (; right < nums.size(); right++) {
            prod *= nums[right];
            while (prod >= k) prod /= nums[left++]; // window is invalid, move left until window is valid
            ans += right - left + 1; // accumulate ans by current right;
        }
        return ans;
    }
};

int main () {
    vector<int> v = {10, 5, 2, 6};
    Solution s;
    cout << s.numSubarrayProductLessThanK(v, 100) << endl;
    v = {10,9,10,4,3,8,3,3,6,2,10,10,9,3};
    cout << s.numSubarrayProductLessThanK(v, 19) << endl;
    v = {1,1,1};
    cout << s.numSubarrayProductLessThanK(v, 1) << endl;
    return 1;
}
