/*
 *
 *                 A
 *              /     \
 *             B        C
 *           /  \     / | \
 *          D    E   F  G  H
 *
Input(could be in random sequence): 
(A, B)
(A, C)
(B, D)
(B, E)
(C, F)
(C, G)
(C, H)
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>
using namespace std;

struct TreeNode {
    int val;
    int index; // TODO: try to move index out of TreeNode
    vector<TreeNode*> child;
    TreeNode(int x): val(x), index(-1) {child.clear();}
};

// O(1);
TreeNode* findNode(unordered_map<int, TreeNode*>& m, int val) {
    if (m.find(val) != m.end())
        return m[val];
    else 
        return nullptr;
}
//
// Assumptions:
// 1. Each node has unque value, e.g. ther is no two nodes have the same value.
//    Otherwise, the constructed tree won't be unique.
TreeNode* constructTree(vector<pair<int, int>>& nodeVec) {
    vector<TreeNode*> r;
    unordered_map<int, TreeNode*> m; // every node has only one root;
                                     // key: node's value, value: pointer to this node
    for (auto x:nodeVec) {
        TreeNode* p1 = findNode(m, x.first);
        TreeNode* p2 = findNode(m, x.second);
        if (p1 == nullptr && p2 == nullptr) {
            // case-1: this is a new sub Tree
            TreeNode* tmpRoot = new TreeNode(x.first);
            TreeNode* tmpChild = new TreeNode(x.second);
            tmpRoot->child.push_back(tmpChild);
            r.push_back(tmpRoot);
            tmpRoot->index = r.size()-1;
            m[x.first] = tmpRoot;
            m[x.second] = tmpChild;
        } else if (p1 != nullptr && p2 != nullptr)  {
            // case-2: connect p1 with p2
            p1->child.push_back(p2);    
            // remove p2 from r
            // need to update index of later elements in r before erase p2 from r;
            int s = p2->index;
            for (vector<TreeNode*>::iterator it = r.begin() + p2->index + 1; it != r.end(); it++) {
                (*it)->index = s++;
            }
            r.erase(r.begin() + p2->index); 
            p2->index = -1;
        } else if (p1 != nullptr) {  // <<< p2 is null
            // case-3: just insert this new child to p
            TreeNode* tmpChild = new TreeNode(x.second);
            p1->child.push_back(tmpChild);
            m[x.second] = tmpChild;
            // No need to update r;
        } else {  // <<< p1 is null, p2 is not null
            // case-4: creat a new subRoot and replace p2 with this new Root in r
            TreeNode* tmpRoot = new TreeNode(x.first);
            tmpRoot->child.push_back(p2);
            m[x.first] = tmpRoot;
            // Update r with tmpRoot to replace p2;
            r[p2->index] = tmpRoot;
            tmpRoot->index = p2->index;
            p2->index = -1;
        }
    }
    return r[0];
}

void traverseForest(TreeNode* root, vector<int>& res) {
    if(root == nullptr) return;
    res.push_back(root->val);
    for (auto x:root->child) {
        traverseForest(x, res);
    }
    return;
}

int main() {
    vector<pair<int, int>> v;

#if 0
//
//                1
//           /    |    \
//         2      3          4
//        /      / \   / |   |   |  \
//       5      6   7 8  9  10   11  12   
//
    v.push_back(make_pair(4, 11));
    v.push_back(make_pair(3, 7));
    v.push_back(make_pair(1, 3));
    v.push_back(make_pair(4, 9));
    v.push_back(make_pair(4, 12));
    v.push_back(make_pair(2, 5));
    v.push_back(make_pair(3, 6));
    v.push_back(make_pair(1, 2));
    v.push_back(make_pair(4, 8));
    v.push_back(make_pair(1, 4));
    v.push_back(make_pair(4, 10));
#endif
#if 1
//
//                1
//           /    |    \
//         2      3          4
//        /      / \   / |   |   |  \
//       5      6   7 8  9  10   11  12   
//      / \     |         /  |  \    | \
//     13 14   15       16  17  18   19 20
//
    v.push_back(make_pair(3, 6));
    v.push_back(make_pair(10, 17));
    v.push_back(make_pair(3, 7));
    v.push_back(make_pair(4, 8));
    v.push_back(make_pair(5, 14));
    v.push_back(make_pair(2, 5));
    v.push_back(make_pair(10, 16));
    v.push_back(make_pair(4, 9));
    v.push_back(make_pair(12, 20));
    v.push_back(make_pair(1, 2));
    v.push_back(make_pair(4, 11));
    v.push_back(make_pair(10, 18));
    v.push_back(make_pair(4, 12));
    v.push_back(make_pair(1, 3));
    v.push_back(make_pair(5, 13));
    v.push_back(make_pair(6, 15));
    v.push_back(make_pair(1, 4)); //<<<<<<
    v.push_back(make_pair(12, 19));
    v.push_back(make_pair(4, 10));
#endif
    TreeNode* root = constructTree(v);
    vector<int> out;
    traverseForest(root, out);
    for (auto x:out) 
        cout << x << ", ";
    cout << endl;
    return 1;
}
