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
#if 1
    // only works when x,y are both >= 0;
    // How to get x and y based on value z; 
    // wiki: https://en.wikipedia.org/wiki/Pairing_function#Inverting_the_Cantor_pairing_function
    // z = pi(x,y);
    // w = floor((sqrt(8z+1)-1)/2); // let 'w' equals to x+y;
    // t = ((w+1)*w)/2;
    // y = z - t;
    // x = w - y;
    int pi(int x, int y) {
        return ((x+y)*(x+y+1))/2 +y;
    }
    // works for both negative and non-negative x and y;
    // f(n) = n*2;     n >= 0;
    // f(n) = -n*2 -1; n <  0;
    // 
    // map negative value to odd positive value, 
    // map non-negative value to even positive value, 
    // e.g. -1 to 1, 1 to 2. 
    //      -2 to 3, 2 to 4. 
    //      ...
    int pi2(int x, int y) {
        if (x >= 0)
            x = x<<1;
        else 
            x = ((-x)<<1) - 1; 

        if (y >= 0)
            y = y<<1;
        else 
            y = ((-y)<<1) - 1; 
        return (((x+y)*(x+y+1))>>1) + y;
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int target, n = nums.size();
        unordered_map<int, int> map;
        unordered_set<int> dupKeys;
        for (int i = 0; i < n; i++){
            map[nums[i]] = i;
        }
        for (int i = 0; i < n; i++){
            target = -nums[i];
            // turn 3sum into 2Sum for target;
            for (int j = i+1; j < n; j++) {
                int gap = target-nums[j];
                if (map.find(gap) != map.end() && map[gap] > j) {
                    // 1. nums[i], nums[j], nums[map[gap]] sums to 0;
                    // 2. check whether this is a duplicate
                    int key = pi2(nums[j], nums[map[gap]]);
                    if (dupKeys.find(key) == dupKeys.end()){
                        dupKeys.insert(key);
                        res.push_back(vector<int>{nums[i], nums[j], nums[map[gap]]});
                    }
                }
            }
        }
        return res;
    }
#endif
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
