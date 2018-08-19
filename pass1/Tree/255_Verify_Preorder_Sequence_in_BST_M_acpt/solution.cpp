/*
 * 255. Verify Preorder Sequence in Binary Search Tree
 *
 * Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.
 *
 * You may assume each number in the sequence is unique.
 *
 * Follow up:
 * Could you do it using only constant space complexity?
 *
 * */
#include <iostream>
#include <vector>
#include <climits>
#include <stack>
#include <cassert>
using namespace std;

class Solution {
    // preOrder:
    //   visit root
    //   visit root->left
    //   visit root->right
public:
    // iterative: 
    // This iterative way is the same way as recursive when comparing root with right child's value that root should be larger than all the right node. 
    //
    // 0. set lower_bound to INT_MIN;
    // 1. For each element in preorder vector:
    //    a. Push all the left child to stack, and if the element is smaller than lower_bound, return false;
    //    b. If reaches one elemnt E larger than previous one, 
    //       pop all the elemnts in stack until the one larger than E.
    //       set low_bound to the element that was poped.
    //    c. push E to stack.
    bool verifyPreorder(vector<int>& preorder) {
        if (preorder.size() == 0) return true;
        stack<int> s;
        int low_bound = INT_MIN;
        s.push(preorder[0]);
        for (int i = 1; i < preorder.size(); i++) {
            if (preorder[i] < preorder[i-1]) { // left child
                // right child should always be larger than current low_bound
                if(low_bound >= preorder[i]) 
                    return false;
            } 
            while (!s.empty() && s.top() < preorder[i]) { // right child
                // update low_bound until the parent of preorder[i];
                low_bound = s.top();
                s.pop();
            }
            s.push(preorder[i]);
        }
        return true;
    }
};

int main () {
    vector<int> v = {10, 3, 1, 6, 4, 5};
    Solution s;
    bool b = true;
    b = s.verifyPreorder(v);
    assert(b);
#if 1
    v = {4, 2,3,1};
    b =  s.verifyPreorder(v);
    assert(!b);
    v = {6,2,1,4,3,5,7,9,8};
    b =  s.verifyPreorder(v);
    assert(b);
#endif
    return 1;
}
