/*
 * 350. Intersection of Two Arrays II
 *
 * Given two arrays, write a function to compute their intersection.
 *
 * Example:
 * Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].
 *
 * Note:
 * Each element in the result should appear as many times as it shows in both arrays.
 * The result can be in any order.
 * Follow up:
 * What if the given array is already sorted? How would you optimize your algorithm?
 * What if nums1's size is small compared to nums2's size? Which algorithm is better?
 * What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int>   res;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        auto j = nums1.begin();
        for (int i = 0; i < nums2.size() && j != nums1.end(); i++) {
            j = lower_bound(j, nums1.end(), nums2[i]);
            if (j != nums1.end() && *j == nums2[i]) {
                res.emplace_back(nums2[i]);
                j++;
            }
        }
        return res;
    }
};

int main() {
    vector<int> v1 = {};
    vector<int> v2 = {};
    Solution s;
    vector<int> o = s.intersect(v1,v2);

    for (auto x:o) 
        cout << x << ",";
    cout << endl;
    return 1;
}
