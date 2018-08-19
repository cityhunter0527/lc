/** 
 * 95. Unique Binary Search Trees II
 * Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.
 *
 * For example,
 * Given n = 3, your program should return all 5 unique BST's shown below.
 *
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 *
 * */

/** Definition for a binary tree node.  */

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n==0) return vector<TreeNode*>();
        return generate (1, n);
    }

private:
    // Generate all the BST with number from [start, end]
    vector<TreeNode*> generate(int start, int end) {
        vector<TreeNode*> res;
        // if no more subTrees, just push NULL as its child.
        if (end < start) {
            res.push_back(nullptr);
            return res;
        }
        for (int k = start; k <= end; k++) {
            vector<TreeNode *> l = generate(start, k-1);
            vector<TreeNode *> r = generate(k+1, end);
            // For a given k, we've got all the subTrees from [start, k-1] and [k+1, end].
            // Now constrcut all the BST with root equals "k".
            for (auto i : l) {
                // Each subTree in l could combine with any other subTree in r to construct a BST rooted as value k.
                for (auto j: r) {
                    TreeNode* p = new TreeNode (k);
                    p->left = i;
                    p->right = j;
                    res.push_back(p);
                }
            }
        }
        return res;
    }
};

int main () {
    return 1;
}
