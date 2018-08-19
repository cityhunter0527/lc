/*
 * 373. Find K Pairs with Smallest Sums
 *
 * You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
 *
 * Define a pair (u,v) which consists of one element from the first array and one element from the second array.
 *
 * Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.
 *
 * Example 1:
 * Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3
 *
 * Return: [1,2],[1,4],[1,6]
 *
 * The first 3 pairs are returned from the sequence:
 * [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
 * Example 2:
 * Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2
 *
 * Return: [1,1],[1,1]
 *
 * The first 2 pairs are returned from the sequence:
 * [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
 * Example 3:
 * Given nums1 = [1,2], nums2 = [3],  k = 3 
 *
 * Return: [1,3],[2,3]
 *
 * All possible pairs are returned from the sequence:
 * [1,3],[2,3]
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
class Solution {
public:
    class mycomp {
    public:
        bool operator() (const tuple<int, int, int>& p1, const tuple<int, int, int>& p2) {
            return get<0>(p1) > get<0>(p2);
        }
    };

    // 
    // minHeap with tuple (sum, index_of_nums1, index_of_nums2):
    // 1. Init minHeap with first element in nums1, and all the elements in nums2;
    //    (nums1[0]+nums2[0], 0, 0), (nums1[0]+nums2[1], 0, 1) ... (nums1[0]+nums2[m-1], 0, m-1);
    // 2. Pick up the root and add this element (x, y) to result;
    // 3. Add the next element (x+1, y) in to minHeap.
    //    if x+1 > n-1, continue from step 2;
    // 4. Repeat k-1 times of step 2~3;
    //
    vector<pair<int, int>> kSmallestPairs (vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> res;
        int n = nums1.size(), m = nums2.size();
        if (n == 0 || m == 0) return res;
        // 0: sum
        // 1: index of nums1
        // 2: index of nums2
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, mycomp> minHeap;
        
        // init minHeap with (0, 0), (0, 1) ... (0, m-1);
        for (int i = 0; i < m; i++) 
            minHeap.push(make_tuple(nums1[0] + nums2[i], 0, i));

        for (int i = 0; i < min(k, m*n); i++) {
            // pick up the smallest pair once a time;
            auto t =  minHeap.top();
            minHeap.pop();
            int x = get<1>(t), y = get<2>(t);
            res.push_back(make_pair(nums1[x], nums2[y]));
            if (x + 1 > n - 1) continue; // move to next if we hit last element of nums1
            minHeap.push(make_tuple(nums1[x+1] + nums2[y], x+1, y));
        }
        return res;
    }
};

int main () {
    vector<int> v1 = {1, 1, 2};
    vector<int> v2 = {1, 2, 3};
    Solution s;
    vector<pair<int, int>> out = s.kSmallestPairs(v1, v2, 10);
    for (auto x:out) {
        cout << x.first << ", " << x.second << endl;
    }
    
    return 1;
}

