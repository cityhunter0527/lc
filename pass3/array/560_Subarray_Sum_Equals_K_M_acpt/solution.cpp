/* 
 * 560. Subarray Sum Equals K
 * Given an array of integers and an integer k, you need to find the total 
 * number of continuous subarrays whose sum equals to k.
 *
 * Example 1:
 * Input:nums = [1,1,1], k = 2
 * Output: 2
 * 
 * Note:
 * The length of the array is in range [1, 20,000].
 * The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        int sum = 0, ans = 0;
        m[0] = 1;

        // if m[sum-k] is not 0, it means there is some j that meets:
        // sum - k = nums[0] + ... + nums[j]   where j < i
        // since sum is nums[0] + ... + nums[i], so we have:
        // num[0] + ... + nums[i] - k = nums[0] + ... + nums[j] which dedue to:
        // k = nums[j+1] + ... nums[i]; 
        //
        // The value of m[sum-k] means the occurrence of prefix sum that equals to sum-k;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];  // calculate prefix sum     
            ans += m[sum-k]; // if m[sum-k] doesn't have a match, ans += 0 will still be ans;
            m[sum]++;        // increase occurrence of this sum;
        }
        return ans;
    }
};

int main() {
    vector<int> v = {1,1,1};
    Solution s;
    cout << s.subarraySum(v, 2) << endl;
    return 0;
}
