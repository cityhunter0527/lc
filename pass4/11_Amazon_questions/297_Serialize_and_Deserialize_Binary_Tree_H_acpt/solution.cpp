/* 
 * 297. Serialize and Deserialize Binary Tree
 * Serialization is the process of converting a data structure or object into a sequence of bits so that it can be 
 * stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in 
 * the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization 
 * algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be 
 * deserialized to the original tree structure.
 *
 * Example: 
 *
 * You may serialize the following tree:
 *
 *     1
 *    / \
 *   2   3
 *      / \
 *     4   5
 *
 * as "[1,2,3,null,null,4,5]"
 * 
 * Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this 
 * format, so please be creative and come up with different approaches yourself.
 *
 * Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
 * */

#include <iostream>
#include <sstream>
#include <string>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::ostringstream  o;       
        serialize(root, o);
        return o.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        std::istringstream i(data);
        return deserialize(i);
    }

private:
    // pre-order traversal
    void serialize(TreeNode* x, std::ostringstream &o) {
        if (x) {
            o << x->val << ' ';
            serialize(x->left, o);
            serialize(x->right, o);
        } else {
            o << "# ";
        }
    }

    TreeNode* deserialize(std::istringstream &i) {
        std::string v;
        i >> v;
        if (v == "#") return nullptr;
        TreeNode* r = new TreeNode(std::stoi(v));
        r->left = deserialize(i);
        r->right = deserialize(i);
        return r;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->right->left = new TreeNode(4);
    r->right->right = new TreeNode(5);

    Codec c;
    std::string s = c.serialize(r);
    std::cout << s << std::endl;
    return 1;
}
