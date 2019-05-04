/*
 * 1026. Maximum Difference Between Node and Ancestor
 *
 * Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B 
 * where V = |A.val - B.val| and A is an ancestor of B.
 * 
 * (A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)


Example 1:
           8
         /   \
        /     \
       3       10
      / \        \
     1   6        14
        / \       /
       4   7     13 


Input: [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7

Explanation:
We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.


Note:
The number of nodes in the tree is between 2 and 5000.
Each node will have value between 0 and 100000.
 * */

#include <iostream>
#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // given value k, return the max diff between all the nodes in binary tree rooted with `n` and k;
    int dfs_r(TreeNode* n, int k) {
        if (n == nullptr) {
            return 0;
        }
        int l = dfs(n->left, k); 
        int r = dfs(n->right, k); 
        return std::max(abs(n->val - k), std::max(l, r));
    }

    int dfs(TreeNode* n, int k) {
        auto max_diff = 0;
        std::stack<TreeNode*>  s;
        TreeNode* p = n;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                // visit p;
                auto d = abs(k - p->val);
                if (d > max_diff) {
                    max_diff = d;
                }
                p = p->right;
            }
        }
        return max_diff;
    }

    int maxAncestorDiff(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int lc = dfs(root->left, root->val);         
        int rc = dfs(root->right, root->val); 

        int lm = maxAncestorDiff(root->left);
        int rm = maxAncestorDiff(root->right);
        return std::max(std::max(lc, rc), std::max(lm, rm));
    }
};

int main() {
    TreeNode* r = new TreeNode(8);
    r->left = new TreeNode(3);
    r->right = new TreeNode(10);
    r->left->left = new TreeNode(1);
    r->left->right = new TreeNode(6);
    r->left->right->left = new TreeNode(4);
    r->left->right->right = new TreeNode(7);
    r->right->right = new TreeNode(14);
    r->right->right->left = new TreeNode(13);

    Solution s;
    std::cout << s.maxAncestorDiff(r) << std::endl;

    return 1;
}
