/*
 * 442. Find All Duplicates in an Array
 *
 * Given an array of integers, 1 <= a[i] <= n (n = size of array), some elements appear twice and others appear once.
 * Find all the elements that appear twice in this array.
 *
 * Could you do it without extra space and in O(n) runtime?
 *
 * Example:
 * Input:
 * [4,3,2,7,8,2,3,1]
 *
 * Output:
 * [2,3]
 * */
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        int radix[nums.size()+1];
        fill_n(radix, nums.size()+1, 0);
        for (auto x:nums) {
            radix[x]++;
            if (radix[x] == 2)
                res.push_back(x);
        }
        return res;
    }
};

int main() {
    //vector<int> arr = {4,3,2,7,8,2,3,1};
    vector<int> arr = {2,2};
    Solution s;
    vector<int> res = s.findDuplicates(arr);
    for(auto x:res)
        cout << x <<",";
    cout <<endl;
    return 1;
}
