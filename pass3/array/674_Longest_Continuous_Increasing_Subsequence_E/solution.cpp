/*
 * 674. Longest Continuous Increasing Subsequence
 *
 * Given an unsorted array of integers, find the length of longest continuous increasing subsequence.
 *
 * Example 1:
 * Input: [1,3,5,4,7]
 * Output: 3
 * Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
 * Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4. 
 * 
 * Example 2:
 * Input: [2,2,2,2,2]
 * Output: 1
 * Explanation: The longest continuous increasing subsequence is [2], its length is 1. 
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int maxLen = 1, curMax = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i-1]) curMax++;
            else {
                maxLen = max(maxLen, curMax);
                curMax = 1;
            }
        }
        maxLen = max(maxLen, curMax);
        return maxLen;
    }
};

int main() {
    vector<int> v = {1,3,5,4,7};
    Solution s;
    cout << s.findLengthOfLCIS(v) << endl;

    v = {2,2,2,2,2};
    cout << s.findLengthOfLCIS(v) << endl;
    v = {2,2,3,2,3,4};
    cout << s.findLengthOfLCIS(v) << endl;
    return 0;
}
