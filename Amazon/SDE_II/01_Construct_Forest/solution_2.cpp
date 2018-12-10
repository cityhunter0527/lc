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
#include <map>
#include <cassert>
#include <utility>

using namespace std;

struct TreeNode {
    int                         val;
    std::vector<TreeNode*>      c;
    TreeNode(int x): val(x) {c.clear();}
};

//
// Assumptions:
// 1. Each node has unque value, e.g. ther is no two nodes have the same value.
//    Otherwise, the constructed tree won't be unique.
//
// There will be one node and only one node which has never appeared as child before. 
// This node is the root and should be returned;
//
TreeNode* construct_forest_from_edges(std::vector<std::pair<int, int>>& edges) {
    std::unordered_map<int, TreeNode*>  val_to_node_map;
    std::map<int, bool>                 val_visited_as_child; // at the end, only one val has visited as false which is root.

    for (auto& x : edges) {
        val_visited_as_child[x.second] = true;
        
        if (val_visited_as_child.find(x.first) == val_visited_as_child.end()) {
            // if x.first not exists yet, initialize to false;
            val_visited_as_child[x.first] = false;
        }

        // if x.first already exisits in val_visited_as_child, leave as it is;

        auto parent = val_to_node_map[x.first]; 
        auto child = val_to_node_map[x.second];
        if (parent == nullptr && child == nullptr) {
            // both are two new nodes
            parent = new TreeNode(x.first);
            child = new TreeNode(x.second);
            val_to_node_map[x.first] = parent;
            val_to_node_map[x.second] = child;
        } else if (parent == nullptr && child != nullptr) {
            parent = new TreeNode(x.first);
            val_to_node_map[x.first] = parent;
        } else if (parent != nullptr && child == nullptr) {
            child = new TreeNode(x.second);
            val_to_node_map[x.second] = child;
        } 

        // if both nodes already exists, just point parent to child
        parent->c.push_back(child);
    }
    
    TreeNode* root = nullptr;
    for (auto& x : val_visited_as_child) {
        if (x.second == false) {
            // should only enter here once;
            // assert (root == nullptr);
            std::cout << "root: " << x.first << "\n";
            root = val_to_node_map[x.first];
        }
    }

    return root;
}

void traverse_forest(TreeNode* root, vector<int>& res) {
    if(root == nullptr) return;
    res.push_back(root->val);
    for (auto x:root->c) {
        traverse_forest(x, res);
    }
    return;
}


int main() {
    std::vector<std::pair<int, int>> v;

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
    TreeNode* root = construct_forest_from_edges(v);
    vector<int> out;
    traverse_forest(root, out);
    for (auto x:out) 
        cout << x << ", ";
    cout << endl;
    return 1;
}
