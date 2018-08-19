/*
 * 300. Longest Increasing Subsequence
 *
 * Given an unsorted array of integers, find the length of longest increasing subsequence.
 *
 * For example,
 * Given [10, 9, 2, 5, 3, 7, 101, 18],
 * The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. 
 * Note that there may be more than one LIS combination, it is only necessary for you to return the length.
 *
 * Your algorithm should run in O(n2) complexity.
 * Follow up: Could you improve it to O(n log n) time complexity?
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 
    // binary search 
    // Complexity: O(N*logN)
    // http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
    //
    int lengthOfLIS(vector<int>& nums) {
        vector<int> res; // res contains the longest increasing subsequence,
        for (int i = 0; i < nums.size(); i++){
            auto it = lower_bound(res.begin(), res.end(), nums[i]); // << return the first it whose value is no less than nums[i];
            if (it == res.end()) res.push_back(nums[i]);
            else 
                *it = nums[i]; // any future value larger than *it,will also be larger than num[i]. So replacing *it with nums[i] is safe and correct.
        }
        return res.size();
    }
};

int main () {
    vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
    Solution s;
    int out = s.lengthOfLIS(v);
    cout << out << endl;
    return 1;
}
