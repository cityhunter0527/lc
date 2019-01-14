/*
 * 863. All Nodes Distance K in Binary Tree
 * 
 * We are given a binary tree (with root node root), a target node, and an integer value K.
 *
 * Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.
 *
 *  Example 1:
 *
 *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
 *
 *  Output: [7,4,1]
 *
 *  Explanation: 
 *  The nodes that are a distance 2 from the target node (with value 5)
 *  have values 7, 4, and 1.
 *
 *                  3
 *              /      \
 *            5          1
 *         /    \      /   \
 *       6       2    0     8
 *              / \
 *             7   4 
 *
 *  Note that the inputs "root" and "target" are actually TreeNodes.
 *  The descriptions of the inputs above are just serializations of these objects.
 *   
 *
 *  Note:
 *
 *  The given tree is non-empty.
 *  Each node in the tree has unique values 0 <= node.val <= 500.
 *  The target node is a node in the tree.
 *  0 <= K <= 1000.
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    void set_parent(TreeNode* x, std::unordered_map<TreeNode*, TreeNode*> &m) {
        if (x->left) { 
            m[x->left] = x;
            set_parent(x->left, m);
        }
        if (x->right) { 
            m[x->right] = x;
            set_parent(x->right, m);
        }
    }

    // starting from t, move downwards to get all nodes thath has K distance to t;
    void get_downwads_nodes_by_distance(TreeNode* t, int K, std::vector<int> &res) {
        if (t == nullptr) return;
        // do level order traversal;
       std::queue<TreeNode*> q;
       q.push(t);
       q.push(nullptr);
       int cur_level = 0;
       while (!q.empty()) {
            TreeNode* p = q.front();
            q.pop();
            if (p) {
                if (cur_level == K) res.push_back(p->val);
                if (p->left) q.push(p->left);
                if (p->right) q.push(p->right);
            } else {
                // p is nullptr
                if (cur_level == K)  {
                    // no need to keep traversing;
                    return;
                }
                if (!q.empty()) q.push(nullptr);
                cur_level++;
            }
       }
       // Either we've visited the nodes with distance K or either there is no such nodes.
       // If so, we just return;
    }

public:
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        std::vector<int> res;
        if (root == nullptr) return res;
        std::unordered_map<TreeNode*, TreeNode*>  m;   // key: node, value: node's parent

        // 0. set the parent chain for every node; (actually we only need the parent chain from target to root)
        set_parent(root, m);
    
        // 1. firstly, let's get all the nodes starting moving downward from this target;
        get_downwads_nodes_by_distance(target, K, res);

        // 2. next, let's move backward, trace by target's parent chain until we hit root node.
        //    2.a And for each node in the parent chain, we track the steps in k and 
        //    2.b move downwards from each parent to get the nodes with the remaining distances; 
        TreeNode *p = target;
        int k = 0;
        while ((m.find(p) != m.end()) && (k < K)) {
            //assert(m[p] != nullptr);
            k++;
            if (K == k) { 
                // this is the one we need and no need to move right or left child, since moving downward would increase distance k to k+1 which will be > K;
                res.push_back(m[p]->val);
                // the outer while loop will exit since k < K is not true any more;
            } else if (p == m[p]->left) {
                get_downwads_nodes_by_distance(m[p]->right, K-k-1, res);
            } else {
                get_downwads_nodes_by_distance(m[p]->left, K-k-1, res);
            }
            p = m[p];
        }
        return res;
    }
};

void print_vec(std::vector<int>& o) {
    for (auto x : o) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}

int main() {
    /*
     *             3
 *              /      \
 *            5          1
 *         /    \      /   \
 *       6       2    0     8
 *              / \
 *             7   4 
 *
     * */
#if 1
    Solution s;
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(5);
    r->right = new TreeNode(1);
    r->left->left = new TreeNode(6);
    r->left->right = new TreeNode(2);
    r->left->right->left = new TreeNode(7);
    r->left->right->right= new TreeNode(4);
    
    r->right->left = new TreeNode(0);
    r->right->right = new TreeNode(8);
    std::vector<int> o = s.distanceK(r, r->left, 2);
    print_vec(o);
#endif
    /*
    *           0
    *          /
    *         1
    *        / \
    *       3   2
    * */

    TreeNode* r2= new TreeNode(0);
    r2->left = new TreeNode(1);
    r2->left->left = new TreeNode(3);
    r2->left->right = new TreeNode(2);

    o.clear();
    o = s.distanceK(r2, r2->left->right, 1);
    print_vec(o);
    return 0;
}
