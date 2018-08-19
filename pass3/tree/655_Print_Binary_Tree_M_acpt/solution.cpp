/*
 * 655. Print Binary Tree
   Print a binary tree in an m*n 2D string array following these rules:
   1. The row number m should be equal to the height of the given binary tree.
   2. The column number n should always be an odd number.
   3. The root node's value (in string format) should be put in the exactly middle 
      of the first row it can be put. The column and the row where the root node 
      belongs will separate the rest space into two parts (left-bottom part and 
      right-bottom part). You should print the left subtree in the left-bottom part 
      and print the right subtree in the right-bottom part. The left-bottom part and 
      the right-bottom part should have the same size. Even if one subtree is none 
      while the other is not, you don't need to print anything for the none subtree 
      but still need to leave the space as large as that for the other subtree. 
      However, if two subtrees are none, then you don't need to leave space for both of them.
   4. Each unused space should contain an empty string "".
   5. Print the subtrees following the same rules.

Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   / 
  3 
 / 
4 
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]

Note: The height of binary tree is in the range of [1, 10].
 * */

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <unordered_map>
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
    // 
    // 1. Get height of this true by level order traversal.
    // 2. Do another level order traversal and for each node, it should be in the middle of its subtree's 2D array.
    //
    vector<vector<string>> printTree(TreeNode* root) {
        vector<vector<string>> res;
        if (!root) return res;
        deque<TreeNode*> q;
        q.push_back(root);
        q.push_back(nullptr);
        int depth = 0;
        // 1. Get height of this tree by level order traversal;
        while (!q.empty()) {
            TreeNode* t = q.front(); q.pop_front();
            if (t == nullptr) {
                depth++;
                if (!q.empty()) q.push_back(nullptr);
                continue;
            } 
            if (t->left)
                q.push_back(t->left);
            if (t->right)
                q.push_back(t->right);
        }

        //
        // init 2D array based on depth, default value to ""
        // numer of colums should be 2^depth-1.
        //
        res.resize(depth, vector<string>(pow(2, depth)-1, ""));

        // 
        // do another level order traversal and for each node, set its value into 2D array
        //
        q.push_back(root);
        q.push_back(nullptr);
        int curDepth = 0;
        unordered_map<TreeNode*, int> m; // node's address to its id in its row (row is curDepth)
        m[root] = pow(2, depth-1) - 1;
        res[curDepth][m[root]] = to_string(root->val);
        curDepth++;
        while(!q.empty()) {
            TreeNode* t = q.front(); q.pop_front();
            int id;
            if(t == nullptr) {
                curDepth++;
                if (!q.empty()) q.push_back(nullptr);
                continue;
            }
            if (t->left) {
                q.push_back(t->left);
                // left child's id is:
                //      parent's id - (total subTree's nodes (complete subTree) / 2) 
                // Total subTree's nodes is 2^(depth-curDepth)
                id = m[t] - pow(2, depth-curDepth)/2;  
                res[curDepth][id] = to_string(t->left->val);
                m[t->left] = id;
            } 
            if (t->right) {
                q.push_back(t->right);
                // right child's id is: 
                //      parent's id + (total subTree's nodes (complete subTree) / 2)
                // Total subTree's nodes is 2^(depth-curDepth)
                id = m[t] + pow(2, depth-curDepth)/2;
                res[curDepth][id] = to_string(t->right->val);
                m[t->right] = id;
            }
        }
        return res;
    }

    void print2DArray(vector<vector<string>>& res) {
        for (auto x:res) {
            for (auto y:x) {
                cout << y << ", ";
            }
            cout << endl;
        }
    }
};



int main() {
    Solution s;
    vector<vector<string>> res; 
#if 1
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    res = s.printTree(r);
    s.print2DArray(res);
    
    cout << "=====================================" << endl;

    TreeNode* r1 = new TreeNode(1);
    r1->left = new TreeNode(2);
    r1->right = new TreeNode(3);
    r1->left->right = new TreeNode(4);
    res = s.printTree(r1);
    s.print2DArray(res);
    
    cout << "=====================================" << endl;
    TreeNode* r2 = new TreeNode(1);
    r2->left = new TreeNode(2);
    r2->right = new TreeNode(5);
    r2->left->left = new TreeNode(3);
    r2->left->left->left = new TreeNode(4);
    res = s.printTree(r2);
    s.print2DArray(res);
#endif
    cout << "=====================================" << endl;
    TreeNode* r3 = new TreeNode(5);
    r3->left = new TreeNode(3);
    r3->right = new TreeNode(6);
    r3->left->left = new TreeNode(2);
    r3->left->right = new TreeNode(4);
    r3->right->right = new TreeNode(7);
    res = s.printTree(r3);
    s.print2DArray(res);
    return 1;
}
