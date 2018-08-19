/*
 * 324. Wiggle Sort II
 * Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
 *
 * Example:
 * (1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6]. 
 * (2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].
 *
 * Note:
 * You may assume all input has valid answer.
 *
 * Follow Up:
 * Can you do it in O(n) time and/or in-place with O(1) extra space?
 * */

#include <iostream>     // std::cout
#include <algorithm>    // std::nth_element, std::random_shuffle
#include <vector>       // std::vector
using namespace std;
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        size_t n = nums.size();
        auto midptr = nums.begin() + (n+1)/2;
        nth_element(nums.begin(), midptr, nums.end());
        int mid = *midptr;

        // Index-rewiring.
#define A(i) nums[(1+2*(i)) % (n|1)]

        // https://discuss.leetcode.com/topic/32929/o-n-o-1-after-median-virtual-indexing
        // Accessing A(0) actually accesses nums[1].
        // Accessing A(1) actually accesses nums[3].
        // Accessing A(2) actually accesses nums[5].
        // Accessing A(3) actually accesses nums[7].
        // Accessing A(4) actually accesses nums[9].
        // Accessing A(5) actually accesses nums[0].
        // Accessing A(6) actually accesses nums[2].
        // Accessing A(7) actually accesses nums[4].
        // Accessing A(8) actually accesses nums[6].
        // Accessing A(9) actually accesses nums[8].

        // 3-way-partition-to-wiggly in O(n) time with O(1) space.
        // https://en.wikipedia.org/wiki/Dutch_national_flag_problem#Pseudocode
        int i = 0, j = 0, k = n - 1;
        while (j <= k) {
            if (A(j) > mid)
                swap(A(i++), A(j++));
            else if (A(j) < mid)
                swap(A(j), A(k--));
            else
                j++;
    } 
     
#if 0 
    // TODO: can't work when there id duplicate elements of midum 
    /* 
     * e.g. 5,5,4,6 or 3,4,5,5,5,6
     * */
        int k = ((n+1)/2);
        for (vector<int>::iterator it = nums.begin() + 1; it < midptr; it += 2, k += 2) {
            if (((n+1)/2)%2) 
                swap(*it, *(nums.begin() + k + 1));
            else 
                swap(*it, *(nums.begin() + k));
        }
#endif
    }
};


int main () {
    Solution s;
    vector<int> v = {4,5,5,6};
    s.wiggleSort(v);
    for (auto x:v) {
        cout << x << ", ";
    }
    cout << endl;

    v = {1,5,1,1,6,4};
    s.wiggleSort(v);
    for (auto x:v) {
        cout << x << ", ";
    }
    cout << endl;

    v = {1,3,2,2,3,1};
    s.wiggleSort(v);
    for (auto x:v) {
        cout << x << ", ";
    }
    cout << endl;

#if 0
    std::vector<int> myvector;

    // set some values:
    srand(time(nullptr));
    for (int i=1; i<10; i++) myvector.push_back(rand()%43);   // 1 2 3 4 5 6 7 8 9

    std::random_shuffle (myvector.begin(), myvector.end());
    cout << "begin() + 5:" << *(myvector.begin()+5) << endl;
    cout << "before nth_element: ";
    for (auto x:myvector) {
        cout << x << ", ";
    }
    cout << endl;
    // using default comparison (operator <):
    std::nth_element (myvector.begin(), myvector.begin()+5, myvector.end());


    // print out content:
    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
        std::cout << *it << ", ";
    std::cout << '\n';

    return 0;
#endif
}

