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
    // another version with map: Passed, but not fast enough
    // 1. Push array element into a map.
    // 2. if the element already exists, increase the # of occurence.
    // 3. Every time get rid of the element:
    //    a. if this is the last element in map, erase.
    //    b. otherwise, only decrease the occurence by 1.
    // 4. Get the lagest element from map's last entry's key (map garnteens entries can be iterated by order).
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.size() == 0) return res;
        map<int, int> m; // key: nums[i], value: # of occurence
        for (int i = 0; i < k; i++){
            if (m.find(nums[i]) == m.end())
                m[nums[i]] = 1;
            else 
                m[nums[i]]++;
        }
        res.push_back(prev(m.end())->first);
        for (int i = k; i < nums.size(); i++) {
            // remove the element outside the window
            m[nums[i-k]]--;
            if(m[nums[i-k]] == 0)
                m.erase(nums[i-k]);
            if (m.find(nums[i]) == m.end())
                m[nums[i]] = 1;
            else 
                m[nums[i]]++;
            res.push_back(prev(m.end())->first); // largest element could always be got from back entry (garunteed by map)
        }
        return res;
    }
};

int main() {
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    Solution s;
    vector<int> o = s.maxSlidingWindow(nums, 3);
    for (auto x:o)
        cout << x <<",";
    cout << endl;
    return 1;
}
