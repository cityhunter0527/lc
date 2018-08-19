/*
 * 268. Missing Number
 *
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
 *
 * For example,
 * Given nums = [0, 1, 3] return 2.
 *
 * Note:
 * Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
 * */
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    // sum from 0 ~ n, then deduce every element in nums.
    // return sum;
    int missingNumber(vector<int>& nums) {
        int len = nums.size();
        int sum = len;
        for (int i = 0; i < nums.size(); i++)
            sum += i-nums[i];
        return sum;
    }

    // a XOR b XOR b == a;
    // idea: xor all the numbers from 0 ~ n; then xor all the elements in 'nums'
    // return the the final value.
    int missingNumberXOR(vector<int>& nums) {
        int len = nums.size();
        int sum = 0, i;
        for (i = 0; i < len; i++) {
            sum ^= i^nums[i];
        }
        return sum ^ len;
    }
};

int main () {
    vector<int> v = {1,0,3,4,5};
    Solution s;
    int out = s.missingNumberXOR(v);
    cout << out << endl;
    return 1;
}
