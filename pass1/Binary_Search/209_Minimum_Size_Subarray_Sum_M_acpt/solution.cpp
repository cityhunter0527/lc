/*
 * 209. Minimum Size Subarray Sum
 *
 * Given an array of n positive integers and a positive integer s, 
 * find the minimal length of a contiguous subarray of which the sum >= s. If there isn't one, return 0 instead.
 *
 * For example, given the array [2,3,1,2,4,3] and s = 7,
 * the subarray [4,3] has the minimal length under the problem constraint.
 *
 * More practice:
 * If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
 * */
#include <vector>
#include <iostream>
#include <climits>
using namespace std;

class Solution {
public:
    // every element will be visited twice: O(2n) which means O(n);
    int minSubArrayLen(int s, vector<int>& nums) {
        int sum = 0, i = 0, j = 0, n = nums.size(), minLen = INT_MAX;
        while (j < n) {
            sum += nums[j++];
            while (sum >= s) {
                minLen = min(j-i, minLen);
                sum -= nums[i++];
            }
        }
        return minLen == INT_MAX? 0: minLen;
    }
};

int main() {
    vector<int> v = {2,3,1,2,4,3};
    Solution s;
    cout << s.minSubArrayLen(7, v) << endl;
    return 1;
}
