/*
 * 15. 3Sum
 *
 * Given an array S of n integers, are there elements a, b, c in S 
 * such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
 *
 * Note: The solution set must not contain duplicate triplets.
 * For example, given array S = [-1, 0, 1, 2, -1, -4],
 *
 * A solution set is:
 * [
 * [-1, 0, 1],
 * [-1, -1, 2]
 * ]
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end()); // sort is a must so that skip of duplicates can be done below.
        int target, n = nums.size();
        for (int i = 0; i < n;){
            // turn 3sum into 2Sum for target;
            target = -nums[i];
            int l = i+1, u = n-1;
            // using two pointers.
            while (l < u) {
                int sum = nums[l] + nums[u];
                if (sum < target)
                    while (nums[++l] == nums[l-1]); // skip duplicates for 2nd number.
                else if (sum > target)
                    while (nums[--u] == nums[u+1]); // skip duplicates for 3rd number.
                else {
                    res.push_back(vector<int>{nums[i], nums[l], nums[u]});
                    while (nums[++l] == nums[l-1]); // skip duplicates for 2nd number.
                    while (nums[--u] == nums[u+1]); // skip duplicates for 3rd number.
                }
            }
            while (nums[++i] == nums[i-1]); // skip duplicates for 1st number.
        }
        return res;
    }
};

int main () {
    //vector<int> v = {-1, 0, 1, 2, -1, -4};
    //vector<int> v = {-1,-2,-3,4,1,3,0,3,-2,1,-2,2,-1,1,-5,4,-3};
    vector<int> v = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
    Solution s;
    vector<vector<int>> res = s.threeSum(v);
    for (auto x:res) {
        for (auto y:x) {
            cout << y << ", ";
        }
        cout << endl;
    }
    return 1;
}
