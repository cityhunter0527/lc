
#include <iostream>
#include <stack>

/**
 *   Example 1:
           8
         /   \
        /     \
       3       10
      / \        \
     1   6        14
        / \       /
       4   7     13 
Note:
The number of nodes in the tree is between 2 and 5000.
Each node will have value between 0 and 100000.
 * */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // pre-order traversal
    int maxAncestorDiff(TreeNode* root) {
        if (root == nullptr) { 
            return 0;
        }

        // tuple: <node, max_val, min_val>
        std::stack<std::tuple<TreeNode*, int, int>> s; 
        s.push(std::make_tuple(root, root->val, root->val));
        int max_diff = 0, cur_max = 0, cur_min = 0;
    
        // pre-order traversal:
        // 1. Pass down parent's node's <max, min> so that when we reach leaf node, 
        // 2. we have all the informatino to get the "max diff" for this root->leaf chain;
        // 3. The return value should be the max of "max diff" in all the root->leaf chains;
        while (!s.empty()) {
            auto t = s.top();
            s.pop();
            TreeNode* p = std::get<0>(t);
            cur_max = std::get<1>(t);
            cur_min = std::get<2>(t);
            if (p->left) { 
                s.push(std::make_tuple(p->left, std::max(p->left->val, cur_max), std::min(p->left->val, cur_min)));
            }
            if (p->right) {
                s.push(std::make_tuple(p->right, std::max(p->right->val, cur_max), std::min(p->right->val, cur_min)));
            }

            if (p->left == nullptr && p->right == nullptr) {
                if (max_diff < (cur_max - cur_min)) {
                    max_diff = cur_max - cur_min;
                }
            }
        }
        return max_diff;
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
