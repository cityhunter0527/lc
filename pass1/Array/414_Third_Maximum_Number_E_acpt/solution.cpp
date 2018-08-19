/*
 * 414. Third Maximum Number
 * Given a non-empty array of integers, return the third maximum number in this array. 
 * If it does not exist, return the maximum number. 
 * The time complexity must be in O(n).
 *
 * Example 1:
 * Input: [3, 2, 1]
 * Output: 1
 * Explanation: The third maximum is 1.
 * 
 * Example 2:
 * Input: [1, 2]
 * Output: 2
 * Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
 *
 * Example 3:
 * Input: [2, 2, 3, 1]
 * Output: 1
 * Explanation: Note that the third maximum here means the third maximum distinct number.
 *
 * Both numbers with value 2 are both considered as second maximum.
 * */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        int n = nums.size();
        long a = INT_MIN - 1L, b = INT_MIN - 1L, c = INT_MIN - 1L;
        for (int i = 0; i < n; i++) {
            if (nums[i] > a) {
                c = b;
                b = a;
                a = nums[i];
            } else if (nums[i] > b && nums[i] != a) {
                c = b;
                b = nums[i];
            } else if (nums[i] > c && nums[i] != b && nums[i] != a) {
                c = nums[i];
            }
        }
        
        return c == (long)(INT_MIN - 1L) ? a:c;
    }
};

int main() {
    vector<int> nums = {INT_MIN, 1, 2};
    Solution s;
    int v = s.thirdMax(nums);
    cout << v << endl;
    return 1;
}
