/*
 * 697. Degree of an Array
 *
 * Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
 *
 * Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.
 *
 * Example 1:
 * Input: [1, 2, 2, 3, 1]
 * Output: 2
 * Explanation: 
 * The input array has a degree of 2 because both elements 1 and 2 appear twice.
 * Of the subarrays that have the same degree:
 * [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
 * The shortest length is 2. So return 2.
 * 
 * Example 2:
 * Input: [1,2,2,3,1,4,2]
 * Output: 6
 * 
 * Note:
 *      nums.length will be between 1 and 50,000.
 *      nums[i] will be an integer between 0 and 49,999.
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    struct Info {
        int freq;
        int startId;
        int endId;
        Info(): freq(0), startId(0), endId(0) {}
    };
    // replace map with an int array: vector<int> m(50000, 0); since nums[i] is between 0 and 49,999
    int findShortestSubArray(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<Info> m(50000);
        // degree to smallest length. e.g. there could be degree as 5, 
        // but two subArray with different length, we should only track the smaller one.
        vector<int> degreeLen(nums.size()+1, INT_MAX); // <<< degree could be as large as nums.size()
        unsigned int degree = 1, ans = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (m[nums[i]].freq == 0) {
                m[nums[i]].freq = 1;
                m[nums[i]].startId = i;
                if (degree < 1) { degree = 1; ans = 1; }
            } else {
                m[nums[i]].freq++;
                m[nums[i]].endId = i;
                if (degree <= m[nums[i]].freq) {
                    degree = m[nums[i]].freq;
                    int len = m[nums[i]].endId - m[nums[i]].startId + 1;
                    if (degreeLen[degree] > len) {
                        ans = len;
                        degreeLen[degree] = len; 
                    }
                }
            }
        }
        return ans;
    }
    int findShortestSubArrayV2(vector<int>& nums) {
        unordered_map<int, tuple<int, int, int>> m; // first: frequency, second: start index, third: end index
        vector<int> d(nums.size()+1, INT_MAX); // need to keep track of same degree with different length
        unsigned int degree = 0;
        unsigned int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (m.find(nums[i]) != m.end()) {
                get<0>(m[nums[i]]) += 1;
                get<2>(m[nums[i]]) = i;
                if (degree <= get<0>(m[nums[i]])) {
                    degree = get<0>(m[nums[i]]);
                    int len = get<2>(m[nums[i]]) - get<1>(m[nums[i]]) + 1;
                    if (d[degree] > len) {  // <<< need to update ans if same degree with smaller len
                        ans = len;
                        d[degree] = len;
                    }
                }
            } else {
                get<0>(m[nums[i]]) = 1;
                get<1>(m[nums[i]]) = i;
                if (degree < 1) degree = 1;
                if (ans < 1) ans = 1;
            }
        }
        return ans;
    }
};

int main() {
    vector<int> v0 = {1,1};
    vector<int> v1 = {1,2,2,3,1};
    vector<int> v2 = {1,2,2,3,1,4,2};
    vector<int> v3 = {2,1,1,2,1,3,3,3,1,3,1,3,2}; // 1, 3 have Same degree, but 3 has smaller len

    Solution s;
    cout << s.findShortestSubArray(v0) << endl;
    cout << s.findShortestSubArray(v1) << endl;
    cout << s.findShortestSubArray(v2) << endl;
    cout << s.findShortestSubArray(v3) << endl;
    return 1;
}
