/*
 * 333. Largest BST Subtree
 * Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.
 *
 * Note:
 * A subtree must include all of its descendants.
 * Here's an example:
 *     10
 *    / \
 *   5  15
 *  / \   \
 * 1   8   7
 * The Largest BST Subtree in this case is the highlighted one. 
 * The return value is the subtree's size, which is 3.
 *
 * Follow up:
 * Can you figure out ways to solve it with O(n) time complexity?
 * */

#include <iostream>
#include <climits>
using namespace std;
/** * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int numBSTNodeMax = 0;
    int largestBSTSubtree(TreeNode* root) {
        if (root!=nullptr)numBSTNodeMax = 1;
        int numNode = 0;
        long minVal = (long)INT_MIN-1, maxVal = (long)INT_MAX+1;
        helper(root, minVal, maxVal, numNode);
        return numBSTNodeMax;
    }

    // Complexity: O(n)
    // bottom-up manner / backtracking
    // Pass min/max value for left/right child from bottom to up. 
    // By checking min/max value of left/right child, we assure a complete BST from bottom to up.
    // numNode means the number of BST node in current subTree.
    // 
    // Globle var numBSTNodeMax will store the overall max number of BST nodes while traversing tree nodes from bottom to up.
    //
    void helper(TreeNode* root, long& minVal, long& maxVal, int& numNode) {
        if (root==nullptr)  {
            // for null node, by setting minVal/maxVal to below value,
            // we always asure parent node's left or right is a BST.
            minVal = (long)INT_MAX+1;
            maxVal = (long)INT_MIN-1;
            numNode = 0;
            return;
        }
        long minL, minR, maxL, maxR;
        int numL, numR;
        helper(root->left, minL, maxL, numL);
        helper(root->right, minR, maxR, numR);
        if (root->val < minR && root->val > maxL) { // <<< this line makes sure we get a complete BST from bottom to up.
            numNode = numL + numR + 1;
            minVal = (root->left == nullptr)? root->val : minL;
            maxVal = (root->right == nullptr)? root->val : maxR;
            if (numBSTNodeMax < numNode)
                numBSTNodeMax = numNode;
        } else {
            // either left or right is not BST. 
            // By setting minVal/maxVal to below value, 
            // we will always end up zero numNode for upper nodes.
            minVal = (long)INT_MIN-1;
            maxVal = (long)INT_MAX+1;
            numNode = 0;
        }
        return;
    }
};

int main () {
#if 1
    // [3,2,4,null,null,1]
    //       3
    //      / \
    //     2   4
    //        /
    //       1 
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(1);
#endif
#if 0
    //     2
    //    / 
    //   3
    //  /
    // 1   
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(1);
#endif
#if 0
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);
#endif
    Solution s;
    int v = s.largestBSTSubtree(root);
    cout << v << endl;
    return 1;
}
