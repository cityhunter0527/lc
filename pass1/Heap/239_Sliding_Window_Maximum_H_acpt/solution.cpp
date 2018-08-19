/*
 * 239. Sliding Window Maximum
 * Given an array nums, there is a sliding window of size k which is moving from the 
 * very left of the array to the very right. You can only see the k numbers in the window. 
 * Each time the sliding window moves right by one position.
 *
 * For example,
 * Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
 *
 * Window position                Max
 * ---------------               -----
 * [1  3  -1] -3 5  3  6  7        3
 * 1 [3  -1  -3] 5  3  6  7        3
 * 1  3 [-1  -3  5] 3  6  7        5
 * 1  3  -1 [-3  5  3] 6  7        5
 * 1  3  -1  -3 [5  3  6] 7        6
 * 1  3  -1  -3  5 [3  6  7]       7
 * Therefore, return the max sliding window as [3,3,5,5,6,7].
 *
 * Note: 
 * You may assume k is always valid, ie: 1 <= k <= input array's size for non-empty array.
 *
 * Follow up:
 * Could you solve it in linear time?
 *
 * Hint:
 *
 * How about using a data structure such as deque (double-ended queue)?
 * The queue size need not be the same as the window's size.
 * Remove redundant elements and the queue should store only elements that need to be considered.
 * */

#include <iostream>
#include <vector>
#include <map>
#include <deque>
using namespace std;

class Solution {
public:
    // Algorithm: Monotonic Queue (desending from front to back, so that always get biggest in window from front);
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> q; // store index
        for (int i = 0; i < k; i++) {
            while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
            q.push_back(i);
        }
        res.push_back(nums[q.front()]);
        for (int i = k; i < nums.size(); i++) {
            if (!q.empty() && q.front() == (i-k)) 
                q.pop_front();
            while (!q.empty() && nums[q.back()] < nums[i]) 
                q.pop_back();
            q.push_back(i);
            res.push_back(nums[q.front()]);
        }
        return res;
    }

};

int main() {
    //vector<int> nums = {1,3,-1,-3,5,3,6,7};
    vector<int> nums = {1,3,1,2,0,5};
    Solution s;
    vector<int> o = s.maxSlidingWindow(nums, 3);
    for (auto x:o)
        cout << x <<",";
    cout << endl;
    return 1;
}
