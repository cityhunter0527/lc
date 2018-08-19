/*
 * 297. Serialize and Deserialize Binary Tree
 *
 * Serialization is the process of converting a data structure or object into a sequence of bits 
 * so that it can be stored in a file or memory buffer, or transmitted across a network connection 
 * link to be reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. 
 * There is no restriction on how your serialization/deserialization algorithm should work. 
 * You just need to ensure that a binary tree can be serialized to a string and this string can be 
 * deserialized to the original tree structure.
 *
 * For example, you may serialize the following tree
 *
 *     1
 *    / \
 *   2   3
 *      / \
 *     4   5
 * as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. 
 * You do not necessarily need to follow this format, so please be creative and come up 
 * with different approaches yourself.
 * 
 * Note: 
 *     Do not use class member/global/static variables to store states. 
 *     Your serialize and deserialize algorithms should be stateless.
 * */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;
/***  * Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Codec {
public:
/*
 *     1
 *    / \
 *   2   3
 *      / \
 *     4   5
 * 
 * [1 2 # # 3 4 # # 5 # # ]
 **/
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream o;
        serialize(root, o);
        return o.str();
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream i(data);
        return deserialize(i);
    }
private:
    void serialize(TreeNode* root, ostringstream& o) {
        if (root == nullptr) {
            o << "# ";
        } else {
            o << root->val << ' '; // separate each node value so that deserize could know edge of each node value.
            serialize(root->left, o);
            serialize(root->right, o);
        }
        return;
    }

    TreeNode* deserialize(istringstream& i) {
        string val;
        TreeNode* root;
        i >> val;
        if (val == "#") {
            root = nullptr;
        } else {
            root = new TreeNode(stoi(val));
            root->left = deserialize(i);
            root->right = deserialize(i);
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
int main () {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->right->left = new TreeNode(4);
    r->right->right = new TreeNode(5);
    Codec c;
    string s = c.serialize(r);
    cout << s << endl;
    TreeNode* nr = c.deserialize(s);
    string ss = c.serialize(nr);
    cout << ss << endl;
    return 1;
}
