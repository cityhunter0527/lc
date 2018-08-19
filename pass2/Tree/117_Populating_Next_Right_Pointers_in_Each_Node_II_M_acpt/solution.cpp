/*
 * 117. Populating Next Right Pointers in Each Node II
 * Follow up for problem "Populating Next Right Pointers in Each Node".
 *
 * What if the given tree could be any binary tree? Would your previous solution still work?
 *
 * Note:
 *
 * You may only use constant extra space.
 * For example,
 * Given the following binary tree,
 *          1
 *         /  \
 *        2    3
 *       / \    \
 *      4   5    7
 *  After calling your function, the tree should look like:
 *          1 -> NULL
 *         /  \
 *        2 -> 3 -> NULL
 *       / \    \
 *      4-> 5 -> 7 -> NULL
 * */

#include <iostream>
#include <queue>
using namespace std;
/** Definition for binary tree with next pointer. **/
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
class Solution {
public:
    // level order traversal
    void connect(TreeLinkNode *root) {
        if (root == nullptr) return;
        queue<TreeLinkNode*> q;
        TreeLinkNode* prev = nullptr, *p = nullptr;
        q.push(root);   
        q.push(nullptr);   
        while (!q.empty()) {
            p = q.front();
            q.pop();
            if (prev) 
                prev->next = p;
            prev = p;
            if (p == nullptr && !q.empty()) {
                q.push(nullptr);
            } 
            if (p && p->left) 
                q.push(p->left);
            if (p && p->right) 
                q.push(p->right);
        }
    }
};

int main() {
    TreeLinkNode* r = new TreeLinkNode(1);
    r->left = new TreeLinkNode(2);
    r->right = new TreeLinkNode(3);
    Solution s;
    s.connect(r);
    return 1;
}
