/*
 * 523. Continuous Subarray Sum
 * Given a list of non-negative numbers and a target integer k, write a function to check if the 
 * array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is, 
 * sums up to n*k where n is also an integer.
 *
 * Example 1:
 * Input: [23, 2, 4, 6, 7],  k=6
 * Output: True
 * Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
 *
 * Example 2:
 * Input: [23, 2, 6, 4, 7],  k=6
 * Output: True
 * Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
 *
 * Note:
 * The length of the array won't exceed 10,000.
 * You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
 * */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (k == 0) {
            // if there is two continous 0, return true
            for (int i = 0; i < nums.size() - 1; i++) {
                if (nums[i] == 0 && nums[i+1] == 0)
                    return true;
            }
            return false;
        }
        // if k is not 0
        unordered_set<int> s;
        s.insert(0);
        for (int i = 0, sum = 0; i < nums.size(); i++) {
            sum += nums[i];
            sum %= k;
            if(s.find(sum) != s.end() && i > 0)
                return true;
            s.insert(sum);
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> v = {23,2,4,6,7};
    cout << s.checkSubarraySum(v, 0) << endl;
    v = {0,0};
    cout << s.checkSubarraySum(v, 0) << endl;
    v = {0,1,0};
    cout << s.checkSubarraySum(v, 0) << endl;
    v = {0};
    cout << s.checkSubarraySum(v, -1) << endl; 
    return 1;
}
