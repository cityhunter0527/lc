/* 
 * 116. Populating Next Right Pointers in Each Node
 *
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
 * Plus: Can you do it recursively?
 * */
#include <queue>
#include <iostream>

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

// 
// solution-1: level order traversal 
// solution-2: recrusive 
//
class Solution {
public:
    // given the left_most pointer of current layer, 
    // build the 'next' pointer of next layer 
    void build_next(Node* left_most) {
        if (left_most == nullptr) { return; }
        auto p = left_most;
        while (p && p->left) {
            p->left->next = p->right;   
            if (p->next) {
                p->right->next = p->next->left;
            } else {
                p->right->next = nullptr;
            }
            p = p->next;
        }
        build_next(left_most->left);
    }
    
    // recursive
    Node* connect2(Node* root) {
        if (root == nullptr) { return nullptr; }
        build_next(root);
        return root;   
    }

    // level order
    Node* connect(Node* root) {
        if (root == nullptr) { return nullptr; }
        std::queue<Node*>  q;
        q.push(root);
        q.push(nullptr);
        Node* prev = nullptr;
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            if (prev) { 
                prev->next = p; 
            }
            prev = p;
            if (p) {
                if (p->left) { q.push(p->left); }
                if (p->right) { q.push(p->right); }
            } else if (!q.empty()) {
                q.push(nullptr);
            }
        }
        return root;
    }
};

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    Solution s;
    root = s.connect(root);
    return 1;
}
