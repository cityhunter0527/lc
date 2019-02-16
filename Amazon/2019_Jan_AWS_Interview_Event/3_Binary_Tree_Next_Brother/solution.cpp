/*
 * Given a binary tree, link the nodes in same level. 
 *
 * Example, Input 
 *
 *       1
 *    /     \
 *   2       3
 *  / \     / \
 * 4   5   6   7 
 * 
 * Output: 
 *
 *       1 -> null
 *    /     \
 *   2  ---> 3 -> null
 *  / \     / \
 * 4 ->5-> 6-> 7 -> null
 *
 * Assumption: the binary tree is a full tree;
 *
 * Plus: Can you solve it if the tree is not a full binary tree?
 * */

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* next;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

class solution {
public:
    TreeNode* convert(TreeNode* root) {
        return nullptr;
    }
}

int main() {
    return 1;
}
