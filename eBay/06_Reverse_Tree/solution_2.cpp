/*
Before reverse:
    A  --> I --> J --> null
    |            |
    |            K --> L --> null
    |
    B -----> C -----> D ----->null            
             |           
             E ---> F ---> G -> null
             |
             H --> M -->null       

After reverse:
    
    J -- > I -- > A --> null
    |             |
    |             D --> C --> B --> null
    L -> K -> null      |
                        G --> F --> E --> null
                                    |
                                    M --> H --> null
New root should be Node "J".

Write a function Node* reverse_tree(Node*) to revert this tree:
    a. The right link of the node should be reversed.
    b. Do this for all the sub node.
Return new root of this tree.
 * */

#include <iostream>
using namespace std;

class TreeNode {                  
public:
    int         val;
    TreeNode*   left;
    TreeNode*   right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class solution {
public:
    TreeNode* reverse_tree(TreeNode* x) {
        TreeNode dummy(1);
        dummy.right = nullptr;
        // for each node in the node->right chain, reverse it;
        // and for each node being visited, reverse it's left child;
        while (x) {
            TreeNode* tmp = x->right;
            x->right = dummy.right;
            dummy.right = x;
            x->left = reverse_tree(x->left);
            x = tmp;
        }
        return dummy.right;
    } 
};

int main() {
    TreeNode* r = new TreeNode('A');
    r->right = new TreeNode('I');
    r->right->right = new TreeNode('J');
    r->right->right->left = new TreeNode('K');
    r->right->right->left->right = new TreeNode('L');

    r->left = new TreeNode('B');
    r->left->right = new TreeNode('C');
    r->left->right->right = new TreeNode('D');

    r->left->right->left = new TreeNode('E');
    r->left->right->left->right = new TreeNode('F');
    r->left->right->left->right->right = new TreeNode('G');
    
    r->left->right->left->left = new TreeNode('H');
    r->left->right->left->left->right = new TreeNode('M');

    solution s;
    TreeNode* x = s.reverse_tree(r);
    return 0;
}
