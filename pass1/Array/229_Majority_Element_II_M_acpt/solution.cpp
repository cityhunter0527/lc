/*
 * 229. Majority Element II
 * Given an integer array of size n, find all elements that appear more than n/3(lower bound) times. 
 * The algorithm should run in linear time and in O(1) space.
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Boyer-Moore Majority Vote Algorithm
    // Note: There should no more than 2 candidates that appear > n/3.
    //       So keep two candidate and count;
    vector<int> majorityElement(vector<int>& nums) {
        int cnt1 = 0, cnt2 = 0;
        int candidate1, candidate2;
        int n = nums.size();
        vector<int> res;
        // 1st scan: pick up the possible two candidates
        for (int i = 0; i < n; i++) {
            if (nums[i] == candidate1) cnt1++;
            else if (nums[i] == candidate2) cnt2++;
            else if (cnt1 == 0) {
                candidate1 = nums[i]; cnt1 = 1;
            } 
            else if (cnt2 == 0) {
                candidate2 = nums[i]; cnt2 = 1;
            } 
            else { 
                cnt1--; cnt2--;
            }
        }
        // 2nd scan:
        // verify the number of two candidates are really > n/3.
        cnt1 = 0; cnt2 = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == candidate1) cnt1++;
            else if (nums[i] == candidate2) cnt2++;
        }

        if (cnt1 > n/3) res.push_back(candidate1);
        if (cnt2 > n/3) res.push_back(candidate2);
        return res;
    }
};

int main() {
    vector<int> nums = {1,1,1,3,4,3,3,3};
    Solution s;
    vector<int> out = s.majorityElement(nums);
    for (auto x:out) {
        cout << x << ",";
    }
    cout << endl;
    return 1;
}
