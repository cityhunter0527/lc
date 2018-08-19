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
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        vector<int> res;
        for (int i = 0; i < nums1.size(); i++)
            m[nums1[i]]++;
        for (int i = 0; i < nums2.size(); i++) {
            if (m[nums2[i]]) {
                res.push_back(nums2[i]);
                m[nums2[i]]--;
            }
        }
        return res;

    }
#if 0
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int>::iterator j;
        vector<int>* v1,*v2;
        vector<int> res;
        if (nums1.size() < nums2.size()) {
            j = nums2.begin();
            v1 = &nums1;
            v2 = &nums2;
        } else {
            j = nums1.begin();
            v1 = &nums2;
            v2 = &nums1;
        }

        for (int i = 0; i < v1->size(); i++) {
            j = lower_bound(j, v2->end(), (*v1)[i]);
            if (j != v2->end() && *j == (*v1)[i]) {
                res.push_back(*j);
                j++;
            }
        }
        return res;
    }
#endif
};

int main() {
    vector<int> nums1 = {1,2,2,1};
    vector<int> nums2 = {2,2};
    Solution s;
    vector<int> o = s.intersect(nums1, nums2);
    for (auto x:o)
        cout << x << ", ";
    cout << endl;
    return 1;
}
