/*
 * 117. Populating Next Right Pointers in Each Node II
 *
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
 *        /  \
 *       2    3
 *      / \    \
 *     4   5    7
 * After calling your function, the tree should look like:
 *          1 -> NULL
 *        /  \
 *       2 -> 3 -> NULL
 *      / \    \
 *     4-> 5 -> 7 -> NULL
 * */
#include <iostream>
#include <list>
#include <deque>
using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode* left, *right, *next;
    TreeLinkNode(int x): val(x), left(nullptr), right(nullptr), next(nullptr) {}
};
class Solution {
public:
    // level order traversal
    void connect(TreeLinkNode *root) {
        if (root == nullptr) return;
        deque<TreeLinkNode*> q;
        q.push_back(root);
        q.push_back(nullptr);
        TreeLinkNode* tmp = nullptr;
        while (!q.empty()) {
            TreeLinkNode* t = q.front();
            q.pop_front();
            if (t != nullptr) {
                if (t->left)
                    q.push_back(t->left);
                if (t->right)
                    q.push_back(t->right);
                if (tmp == nullptr)
                    tmp = t;
                else {
                    tmp->next = t;
                    tmp = t;
                }
            } else {
                tmp = nullptr;
                if (!q.empty())
                    q.push_back(nullptr);
            }
        }
    }
};

int main() {
    TreeLinkNode* r = new TreeLinkNode(1);
    r->left = new TreeLinkNode(2);
    r->right = new TreeLinkNode(3);
    r->left->left = new TreeLinkNode(4);
    r->left->right = new TreeLinkNode(5);
    r->right->right = new TreeLinkNode(7);
    Solution s;
    s.connect(r);
    return 1;
}
