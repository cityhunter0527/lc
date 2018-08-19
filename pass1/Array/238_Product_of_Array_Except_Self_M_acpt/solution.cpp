/*
 * 238. Product of Array Except Self
 * Given an array of n integers where n > 1, nums, return an array output such that output[i] is 
 * equal to the product of all the elements of nums except nums[i].
 *
 * Solve it without division and in O(n).
 *
 * For example, given [1,2,3,4], return [24,12,8,6].
 *
 * Follow up:
 * Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
 * */
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    // Run time Complexity: O(n)
    // Space complexity: O(1)
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res;
        long tpro = 1;
        int one;
        bool oneZero = false, twoZero = false;
        // check wither there is only one zero occurred or more than two Zeros occurred.
        for (int i = 0; i < nums.size(); i++) {
            res.push_back(0);
            if (nums[i] == 0) {
                if (!oneZero)  {
                    oneZero = true;
                    one = i;
                } else { 
                    twoZero = true;
                }
                continue;
            }
            tpro *= nums[i];
        }

        if (twoZero) 
            return res;
        else if (oneZero) 
            res[one] = tpro;
        else {
            for (int i = 0; i < nums.size(); i++) {
                res[i] = tpro/nums[i];
            }
        }
        
        return res;
    }
};

int main () {
    vector<int> v = {1,0,0,4};
    Solution s;
    vector<int> out = s.productExceptSelf(v);
    for(auto x:out)
        cout<<x<<", ";
    cout<<endl;
    return 1;
}
