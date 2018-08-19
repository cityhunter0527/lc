/*
 * 162. Find Peak Element
 * A peak element is an element that is greater than its neighbors.
 * Given an input array where num[i] != num[i+1], find a peak element and return its index.
 * The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
 * You may imagine that num[-1] = num[n] = INT_MIN-1.
 * For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
 * */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // binary search
    int findPeakElement(vector<int>& nums) {
        int l = 0, h = nums.size()-1;   
        while (l < h) {
            int m = (l+h)/2;
            if (nums[m] < nums[m+1])
                l = m+1;
            else 
                h = m;
        }

        return h;
    }
};

int main() {
    vector<int> v = {1,2,3,4,20,30,2};
    Solution s;
    int out = s.findPeakElement(v);
    cout << out <<endl;
    return 1;
}

