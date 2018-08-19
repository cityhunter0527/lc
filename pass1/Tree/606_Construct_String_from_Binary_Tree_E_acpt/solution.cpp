/* 
 * 606. Construct String from Binary Tree 
 *
 * You need to construct a string consists of parenthesis and integers from a binary 
 * tree with the preorder traversing way. The null node needs to be represented by 
 * empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs 
 * that don't affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output. 
 * */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*** Definition for a binary tree node. ***/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void tree2str(TreeNode* t, ostringstream& o) {
        if (!t) return;
        o << t->val;
        if (!t->left && !t->right) return;
        o << "(";
        tree2str(t->left, o);
        if (t->right) {
            o << ")(";
            tree2str(t->right, o);
            o << ")";
        } else {
            o << ")";
        }
    }
    string tree2str(TreeNode* t) {
        ostringstream o;
        tree2str(t, o);
        return o.str();
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->right= new TreeNode(4);
    Solution s;
    cout << s.tree2str(r) << endl;
    return 1;
}
