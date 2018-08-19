/*
 * 215. Kth Largest Element in an Array
 *
 * Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
 *
 * For example,
 * Given [3,2,1,5,6,4] and k = 2, return 5.
 *
 * Note: 
 * You may assume k is always valid, 1 <= k <= array's length.
 * */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Solution {
    class mycomp{
    public:
        bool operator() (const int& l, const int& r) {
            return l < r;
        }
    };
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, mycomp> maxHeap;
        for (auto x:nums) {
            maxHeap.push(x);
        }
        for (int i = 0; i < k-1; i++)
            maxHeap.pop();

        return maxHeap.top();
    }
};

int main () {
    vector<int> nums = {3,2,1,5,6,4};
    Solution s;
    int out = s.findKthLargest(nums, 2);
    cout << out << endl;
    return 1;
}
