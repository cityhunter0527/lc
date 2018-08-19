/*
 * 116. Populating Next Right Pointers in Each Node 
 *
 * Given a binary tree
 *
 * struct TreeLinkNode {
 *     TreeLinkNode *left;
 *     TreeLinkNode *right;
 *     TreeLinkNode *next;
 * }
 * Populate each next pointer to point to its next right node. 
 * If there is no next right node, the next pointer should be set to NULL.
 *
 * Initially, all next pointers are set to NULL.
 *
 * Note:
 *     You may only use constant extra space.
 *     You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
 * 
 * For example,
 * Given the following perfect binary tree,
 *           1
 *         /  \
 *        2    3
 *       / \  / \
 *      4  5  6  7
 * After calling your function, the tree should look like:
 *           1 -> NULL
 *         /  \
 *        2 -> 3 -> NULL
 *       / \  / \
 *      4->5->6->7 -> NULL 
 * */

#include <iostream>
#include <queue>
using namespace std;
/** *  * Definition for binary tree with next pointer. */
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:

    // Solution-1: Using queue, timeout
#if 0
    // level order traversal
    // Note this B-Tree is always complete
    void connect(TreeLinkNode *root) {
        if (root == nullptr) return;
        queue<TreeLinkNode*> q; // FIFO
        q.push(root);
        TreeLinkNode* nextp = nullptr;
        int i = 1, j = i;
        while (!q.empty()) {
            TreeLinkNode* p = q.front();
            q.pop();
            // visit p; 
            if (p->right)
                q.push(p->right);
            if (p->left)
                q.push(p->left);
            p->next = nextp;
            nextp = p;
            j--;
            if (j == 0) {
                i = i << 1 ;
                j == i;
                nextp = nullptr;
            }
        }
    }
#endif 

    void connect(TreeLinkNode *root) {
        if (root == nullptr) return;
        TreeLinkNode dummy(-1);
        for (TreeLinkNode *curr = root, *prev = &dummy; curr; curr = curr->next) {
            if (curr->left != nullptr){
                prev->next = curr->left;
                prev = prev->next;
            }
            if (curr->right != nullptr){
                prev->next = curr->right;
                prev = prev->next;
            }
        }
        connect(dummy.next);
    }
};

int main () {
    TreeLinkNode* root = new TreeLinkNode(0);
    root->left = new TreeLinkNode(1);
    root->right = new TreeLinkNode(2);
    root->left->left = new TreeLinkNode(3);
    root->left->right = new TreeLinkNode(4);
    root->right->left = new TreeLinkNode(5);
    root->right->right = new TreeLinkNode(6);

    Solution s;
    s.connect(root);

    return 1;
}
