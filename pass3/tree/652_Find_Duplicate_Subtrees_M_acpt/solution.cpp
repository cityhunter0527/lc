/*
 * 652. Find Duplicate Subtrees
 *
 * Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1: 
        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:
      2
     /
    4
and
    4
Therefore, you need to return above trees' root in the form of a list.
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
using namespace std;

/** * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private: 
    void serialize(TreeNode* r, ostringstream& o) {
        if (r == nullptr) 
            o << "# ";
        else {
            o << r->val << ' ';
            serialize(r->left, o);
            serialize(r->right, o);
        }
        return;
    }
    string serialize(TreeNode* r) {
        ostringstream o;
        serialize(r, o);
        return o.str();
    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        // in-order traversal
        vector<TreeNode*> res;
        // Map: Serialized string to root node addr.
        // Multiple same duplicated subTree, so push them in to vector.
        unordered_map<string, vector<TreeNode*>> m; 
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                // visit p;
                string tmp = serialize(p);
                m[tmp].push_back(p);
                p = p->right;
            }
        }

        for (auto x:m) { 
            if (x.second.size() > 1)
                res.push_back(x.second[0]); // Only push first node's address for all the same subTrees
        }
        return res;
    }
};

int main() {

    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->right->left = new TreeNode(2);
    r->right->right = new TreeNode(4);
    r->right->left->left = new TreeNode(4);

    Solution s;
    vector<TreeNode*> res = s.findDuplicateSubtrees(r);
    for (auto x:res) {
        cout << x->val << ", ";
    }
    cout << endl;
    return 1;
}
