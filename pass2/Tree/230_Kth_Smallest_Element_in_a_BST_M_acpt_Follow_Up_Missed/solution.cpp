/*
 * 230. Kth Smallest Element in a BST
 *
 * Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
 *
 * Note: 
 * You may assume k is always valid, 1 <= k <= BST's total elements.
 *
 * Follow up:
 * What if the BST is modified (insert/delete operations) often and you need to find the 
 * kth smallest frequently? How would you optimize the kthSmallest routine?
 * 
 * Hint:
 *  1. Try to utilize the property of a BST.
 *  2. What if you could modify the BST node's structure?
 *  3. The optimal runtime complexity is O(height of BST).
 * */

#include <iostream>
#include <stack>
using namespace std;
/** *  * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:

    // in-Order traversal to return kth element;
    // Iterative solution using stack
    int kthSmallest(TreeNode* root, int k) {
        // since 1 <= k <= BST's total nodes, no need to check null for root;
        stack<TreeNode*> s; 
        TreeNode* p = root;
        int cnt = 1;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);   
                p = p->left;
            } else {
                // visit p
                p = s.top();
                s.pop();
                if (cnt++ == k)
                    return p->val;
                p = p->right;
            }
        }
    }

    // Follow up:
    // Option-1: O(logk)
    // 1. Build up a minheap (O(n)), only need one time build.
    // 2. K is a parameter that could be differenct every time it called.
    //    2.a Insert/delete a node will also update the minheap (O(logn));
    //    2.b Find kth in minHeap will also be O(logk) ???
};
// 
//                  10
//                /    \
//               6      40
//              / \    /  \
//             2   8  21  62
//                        /
//                       54
//  
int main() {
    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(6);
    r->right = new TreeNode(40);
    r->left->left = new TreeNode(2);
    r->left->right = new TreeNode(8);
    r->right->left = new TreeNode(21);
    r->right->right= new TreeNode(62);
    r->right->right->left= new TreeNode(54);

    Solution s;
    cout << s.kthSmallest(r, 3) << endl;
    cout << s.kthSmallest(r, 4) << endl;
    cout << s.kthSmallest(r, 5) << endl;
    cout << s.kthSmallest(r, 7) << endl;
    return 1;
}
