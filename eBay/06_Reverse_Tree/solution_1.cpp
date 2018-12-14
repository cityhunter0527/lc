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

Write a function Node* reverseTree(Node*) to revert this tree:
    a. The right link of the node should be reversed.
    b. Do this for all the sub node.
Return new root of this tree.
 * */

#include <iostream>
using namespace std;

class TreeNode {                  
public:
    int         val;
    TreeNode*   child;
    TreeNode*   right;
    TreeNode(int x) : val(x), child(nullptr), right(nullptr) {}
};

class solution {
private:
    TreeNode* reverseList(TreeNode* x) {
        TreeNode dummy(0), *tmp = nullptr;
        while (x) {
            tmp = x->right;
            x->right = dummy.right;
            dummy.right = x;
            x = tmp;
        }
        return dummy.right;
    }
    TreeNode* reverseTreeAux(TreeNode* x) {
        if (x == nullptr) return nullptr;
        x->child = reverseList(x->child);
        TreeNode* p = x->child;
        while (p) {
            reverseTreeAux(p);
            p = p->right;
        }
        return x;
    }
public:
    TreeNode* reverseTree(TreeNode* x) {
        TreeNode dummy(0);
        dummy.child = x;
        reverseTreeAux(&dummy);
        return dummy.child;
    } 
};

int main() {
    TreeNode* r = new TreeNode('A');
    r->right = new TreeNode('I');
    r->right->right = new TreeNode('J');
    r->right->right->child = new TreeNode('K');
    r->right->right->child->right = new TreeNode('L');

    r->child = new TreeNode('B');
    r->child->right = new TreeNode('C');
    r->child->right->right = new TreeNode('D');

    r->child->right->child = new TreeNode('E');
    r->child->right->child->right = new TreeNode('F');
    r->child->right->child->right->right = new TreeNode('G');
    
    r->child->right->child->child = new TreeNode('H');
    r->child->right->child->child->right = new TreeNode('M');

    solution s;
    TreeNode* x = s.reverseTree(r);
    return 0;
}
