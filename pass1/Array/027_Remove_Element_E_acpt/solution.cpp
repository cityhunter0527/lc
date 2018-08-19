/*
 * 27. Remove Element
 *
 * Given an array and a value, remove all instances of that value in place and return the new length.
 *
 * Do not allocate extra space for another array, you must do this in place with constant memory.
 *
 * The order of elements can be changed. It doesn't matter what you leave beyond the new length.
 *
 * Example:
 * Given input array nums = [3,2,2,3], val = 3
 *
 * Your function should return length = 2, with the first two elements of nums being 2.
 * */
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    // Two pointers
    // 1. l: find the first element equals to val from left to right. 
    // 2. r: find the first element not equal to val from right to left.
    // 3. swap (l, r)
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) return 0;
        auto l = nums.begin(), r = prev(nums.end());                   

        while (l < r) {
            while (*l != val && l < r) l++;
            while (*r == val && r > l) r--;
            if (r == l) return (*l == val)?(l - nums.begin()):(l-nums.begin()+1);
            else {
                swap(*l,*r);
                l++; r--;
            }
        }

        return (*l == val)?(l - nums.begin()):(l-nums.begin()+1);
    }
};

int main() {
    vector<int> nums = {2};
    Solution s;
    cout << s.removeElement(nums, 3) << endl;

    nums = {3,2,2,3};
    cout << s.removeElement(nums, 3) << endl;

    nums = {3};
    cout << s.removeElement(nums, 3) << endl;

    nums = {1,2,3,3,4,5,63,6,1};
    cout << s.removeElement(nums, 3) << endl;
    
    nums = {3,3};
    cout << s.removeElement(nums, 3) << endl;
    nums = {3,5};
    cout << s.removeElement(nums, 3) << endl;
    nums = {4,5};
    cout << s.removeElement(nums, 3) << endl;
    return 1;
}
