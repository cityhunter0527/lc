/*
 *  449. Serialize and Deserialize BST
 *  Serialization is the process of converting a data structure or object into a sequence of 
 *  bits so that it can be stored in a file or memory buffer, or transmitted across a network 
 *  connection link to be reconstructed later in the same or another computer environment.
 *
 *  Design an algorithm to serialize and deserialize a binary search tree. 
 *  There is no restriction on how your serialization/deserialization algorithm should work. 
 *  You just need to ensure that a binary search tree can be serialized to a string and this 
 *  string can be deserialized to the original tree structure.
 *
 *  The encoded string should be as compact as possible.
 *
 *  Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
 * */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
};
struct Codec {
public:
    //
    //          10
    //       /      \
    //      6         50
    //     / \      /    \
    //    3   8    34     88
    //              \     / 
    //              42   66
    //  output:
    //  pre-order: [10 6 3 # # 8 # # 50 34 # 42 # # 88 66 # # #]
    string serialize(TreeNode* root) {
        ostringstream o;   
        serialize(root, o);
        return o.str();
    }

    void serialize(TreeNode* root, ostringstream& o) {
        if (root) { 
            o << root->val << " "; // << can't use ",", only " " works with istringstream to skip " " to get next value
            serialize(root->left, o);
            serialize(root->right, o);
        } else
            o << "# ";
    }

    TreeNode* deserialize(string data) {
        istringstream i(data);
        TreeNode* root = deserialize(i);
        return root;
    }

    TreeNode* deserialize(istringstream& i) {
        string val;
        TreeNode* root = nullptr;
        i >> val;
        if (val == "#") root = nullptr;
        else {
            root = new TreeNode(stoi(val));
            root->left = deserialize(i);
            root->right = deserialize(i);
        }
        return root;
    }
};

int main() {
    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(6);
    r->right = new TreeNode(50);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(8);
    r->right->left = new TreeNode(34);
    r->right->right = new TreeNode(88);
    r->right->left->right = new TreeNode(42);
    r->right->right->left = new TreeNode(66);

    Codec c;
    string s = c.serialize(r);

    cout << s << endl;

    TreeNode* r2 = c.deserialize(s);

    string s2 = c.serialize(r2);
    cout << s2 << endl;

    return 1;
}
