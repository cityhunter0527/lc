/*
 * 215_Kth_Largest_Element_in_an_Array_M
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
#if 0
private:
    class mycomp {
        bool operator() (const TrerNode* &l, const TrerNode* &r){
            return l->val < r->val;
        }
    };
#endif
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, less<int>> pq;
        for (auto x:nums)
            pq.push(x);
        for (int i = 0; i < k-1; i++)
            pq.pop();
        return pq.top();
    }
};

int main() {
    Solution s;
    vector<int> v = {3,2,1,5,6,4};
    cout << s.findKthLargest(v, 2) << endl;
    v = {-1, 2, 0};
    cout << s.findKthLargest(v, 2) << endl;
    return 1;
}
