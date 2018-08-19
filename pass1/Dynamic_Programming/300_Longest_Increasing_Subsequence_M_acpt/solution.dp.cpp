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
    // Dynamic Programming:
    // state : 
    //     f(i) means the max number of subsequence from the begin to i
    // function :
    //     f(i) = max(f(j))+1 when nums[j] < nums[i]
    // initialize : 
    //     f(0) = 1
    // answer: 
    //     max(f(0)->f(n-1));
    // Complexity: 
    //     O(n^2)
    //
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size == 0) return 0;
        int n = nums.size();
        int f[n];
        f[0] = 1;
        int maxLIS = f[0];
        for (int i = 1; i < n; i++) {
            int tmpMax = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i])
                    tmpMax = max(tmpMax, f[j]);
            }
            f[i] = tmpMax + 1;
            maxLIS = max(maxLIS, f[i]);
        }
        return maxLIS;
    }
#if 0
    // binary search 
    int lengthOfLIS(vector<int>& nums) {
                        
    }
#endif
};

int main () {
    vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
    Solution s;
    int out = s.lengthOfLIS(v);
    cout << out << endl;
    return 1;
}
