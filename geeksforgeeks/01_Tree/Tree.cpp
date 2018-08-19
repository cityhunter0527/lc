#include "Tree.hpp"
#include <unordered_map>
#include <assert.h>
#include <queue>
#include "DisjointSets.hpp"
// 
// Convert Rule:
// 1. for a given node in general tree, its first child should be its left child in the binary tree.
// 2. for any right brother node, it should be its left brother's right child.
//
// Example-1: 
// 
//       1                     1
//   /  / \  \                /
//  2  3   4  5   ====>      2
//    /|\                      \
//   6 7 8                      3
//                             /  \
//                            6     4
//                             \      \
//                              7      5
//                               \
//                                8
//
TreeNode* Solution::GenTreeToBinTree(GenTreeNode* root) {
    if (root == nullptr) return nullptr;
    TreeNode* x = new TreeNode(root->val);

    if (root->c.size() == 0) return x;
    
    x->left = GenTreeToBinTree(root->c[0]);
    TreeNode* tmp = x->left;
   
    for (int i = 1; i < root->c.size(); i++) {
        tmp->right = GenTreeToBinTree(root->c[i]);
        tmp = tmp->right;
    }
    return x;
}

// 
// Given a sequence of <parent, child> elements, construct a general tree;
//
// Example:
// Input(could be in random sequence):
// (C, F) (C, G) (A, B) (B, D) (B, E) (C, H) (A, C)
//
// Construct a general tree as below:
//
//                  A
//               /     \
//              B        C
//             /  \     / | \
//            D    E   F  G  H
//
// Solution: 
// 1. Create a empty map of GenTrees 
// ....unordered_map<int, GenTreeNode*> m;         // mapping from node's value to node's pointer;
// ....unordered_map<int, int>          parerntMP; // mapping between child value to parernt value;
// 2. For each nodePair <parent, child>
//     parerntMP[child] = parent;
// ....2.1 if neither parent nor child could be found in m, create node for both parent/child and 
// ........insert both parent/child to m and push child node into parernt's child list;
// ....2.2 if parernt could be found and child couldn't be found in m,
// ........create a new node for child and push it to parent's child list;
// ........insert child node to m;
// ....2.3 if parent could not be found and child could be found in m, 
// ........create node for parernt and get child node from m and push it to parent node's child list;
// ........Insert parernt node to m;
// ....2.4 if both parent and child could be found in m, 
// ........get parent/child node from m and push child node into parernt node's child list;
// 3. Get the root value and return m[rootVal];
//
GenTreeNode* Solution::ConstructGenTree(vector<pair<int, int>>& edges) {
    // Assumption: all tree nodes have uqnue value;
    // map for Node value to node's pointer 
    unordered_map<int, GenTreeNode*>  m;
    // map for child value to parent value;
    unordered_map<int, int>           parentMap;

    for (int i = 0; i < edges.size(); i++) {
        // Save <parent, child> value in vx/vy 
        int vx = edges[i].first, vy = edges[i].second; 
        auto x = m.find(vx), y = m.find(vy);
        parentMap[vy] = vx;      // track child->parent relationship
        GenTreeNode* t = nullptr;
        if (x != m.end() && y != m.end()) {         //  << 2.4
            x->second->c.push_back(y->second);
        } else if (x == m.end() && y != m.end()) {  //  << 2.3
            t = new GenTreeNode(vx);
            t->c.push_back(y->second);
            m[vx] = t;
        } else if (x != m.end() && y == m.end()) {  //  << 2.2
            t = new GenTreeNode(vy);
            m[vx]->c.push_back(t);
            m[vy] = t;
        } else {                                    //  << 2.1
            t = new GenTreeNode(vx);
            m[vy] = new GenTreeNode(vy);
            t->c.push_back(m[vy]);
            m[vx] = t;
        }
    }

    if (edges.size() == 0) return nullptr;
    // pick up any <parent, child> pair and look it up in parerntMP until
    // we find the root node's value;
    int k = edges[0].first;
    while (parentMap.find(k) != parentMap.end()) {
        k = parentMap[k];
    }

    return m[k];
}


// 
// 685. Redundant Connection II
// In this problem, a rooted tree is a directed graph such that, there is exactly one node 
// (the root) for which all other nodes are descendants of this node, plus every node has 
// exactly one parent, except for the root node which has no parents.
//
// The given input is a directed graph that started as a rooted tree with N nodes (with 
// distinct values 1, 2, ..., N), with one additional directed edge added. The added edge 
// has two different vertices chosen from 1 to N, and was not an edge that already existed.
//
// The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] 
// that represents a directed edge connecting nodes u and v, where u is a parent of child v.
//
// Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. 
// If there are multiple answers, return the answer that occurs last in the given 2D-array.
//
// Example 1:
// Input: [[1,2], [1,3], [2,3]]
// Output: [2,3]
// Explanation: The given directed graph will be like this:
//   1
//  / \
// v   v
// 2-->3
//
// Example 2:
// Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
// Output: [4,1]
// Explanation: The given directed graph will be like this:
// 5 <- 1 -> 2
//      ^    |
//      |    v
//      4 <- 3
// 
// Note:
// The size of the input 2D-array will be between 3 and 1000.
// Every integer represented in the 2D-array will be between 1 and N, where N is the size 
// of the input array.
//
// Solution:
// 0. For every edge: 
// ....0.a store each child's parent in vParent;
// ....0.b if there is two parent detected for a single node y, record both parent's value in p1/p2;
// ....0.c when twoParent flag is false, it means there is a leaf node pointing back to root node. 
// ........It also means for each child node, it appears once and only once in given edges. 
// ........Store each edge's index  based on child value in childPos, so that we can return the last 
// ........occurence if the edge that is in the cycle.
// 1. If twoParent is false, the loop must starts from the root;
// ....starts from any node, tracing back parent chain, we must be able to find the loop;
// 2. If twoParent is true, the result is either [p1, c] or [p2, c]
// ....Starts from node c, tracing back parent chain (need to track back both c->p1 and c->p2): 
// ....2.a if there is no loop in both chain, then pick the from the two candidates which appears the last;
// ....2.b if there is loop in one chain (the other one must trace back to root that does not have loop), 
// ........then pick the one that leads to the loop;
//
vector<int> Solution::findRedundantDirectedConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    vector<int> vParent(n+1, 0);
    vector<int> childPos(n+1, -1); 
    bool twoParent = false;
    int c, p1, p2; // c will have two parents stored in p1 and p2;
    // step-0
    for (int i = 0; i < n; i++) {
        int x = edges[i][0], y = edges[i][1];
        childPos[y] = i;  // records the last appearence of the pos that have child of y when twoParent is true;
        if (vParent[y]) {
            twoParent = true;  
            c = y;
            p1 = x;
            p2 = vParent[y];
        } else 
            vParent[y] = x;
    }
    if (twoParent) { // step-2
        int k1 = cycleNode(vParent, p1, c);
        int k2 = cycleNode(vParent, p2, c);
        if (!k1 && !k2) 
            // neither has loop detected, return the one that appears the last;
            // childPos[c] already records the last appearence of the edge;
            return edges[childPos[c]];
        else {
            // then one of k1/k2 must be 0, the other must be from [1,n];
            if (k1) 
                return vector<int> {p1, c};
            else
                return vector<int> {p2, c};
        }
    } else { // step-1
        // find the starting node of the cycle
        int k = cycleNode(vParent, edges[0][0]);
        // cycle starts from node k, any node in the cycle could be the root node;
        vector<bool> v(n+1, false);
        fill(v.begin(), v.end(), false);
        int pos = 0;
        // now check for each node in the cycle, find the one that appears the last in the edges;
        while (!v[k]) {
            pos = pos < childPos[k] ? childPos[k] : pos;
            v[k] = true;
            k = vParent[k];
        }
        return edges[pos];
    }
}

// 
// Return the first node that starts with the cycle
// If return value is 0, it means there is no cycle since 0 is not a valid node value;
// Root node's parent is defauted to 0;
//
int Solution::cycleNode(vector<int>& vParent, int k, int c) {
    vector<bool> v(vParent.size()+1, false);
    v[c] = true;
    while (!v[k]) {
        v[k] = true;
        k = vParent[k];
    }
    return k;
}

// 
// 684. Redundant Connection
// In this problem, a tree is an undirected graph that is connected and has no cycles.
//
// The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), 
// with one additional edge added. The added edge has two different vertices chosen from 1 to N, 
// and was not an edge that already existed.
//
// The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] 
// with u < v, that represents an undirected edge connecting nodes u and v.
//
// Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are 
// multiple answers, return the answer that occurs last in the given 2D-array. 
// The answer edge [u, v] should be in the same format, with u < v.
//
// Example 1:
// Input: [[1,2], [1,3], [2,3]]
// Output: [2,3]
// Explanation: The given undirected graph will be like this:
//   1
//  / \
// 2 - 3
// 
// Example 2:
// Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
// Output: [1,4]
// Explanation: The given undirected graph will be like this:
//    5 - 1 - 2
//        |   |
//        4 - 3
// Note:
// The size of the input 2D-array will be between 3 and 1000.
// Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
//
vector<int> Solution::findRedundantConnection(vector<vector<int>>& edges) {
    // Disjoint Sets (Union Find)
#if 0
    int n = edges.size();
    DisjointSetsArray ds(2*n);
    for (auto x:edges) {
        int u = x[0], v = x[1];
        int s1 = ds.FindSet(u), s2 = ds.FindSet(v);
        if (s1 == s2) 
            return x;
        else 
            ds.Union(s1, s2);
    }
    assert(false);  //  << should not come here
#endif
    DisjointSetsTree ds;
    for (auto x:edges) {
        int u = x[0], v = x[1];
        int s1 = ds.FindSet(u);
        int s2 = ds.FindSet(v);
        if (ds.isValidSetID(s1) && ds.isValidSetID(s2) && s1 == s2) {
            return x;
        }

        if (!ds.isValidSetID(s1)) 
            s1 = ds.MakeSet(u);
        if (!ds.isValidSetID(s2)) 
            s2 = ds.MakeSet(v);
        if (s1 != s2) 
            ds.Union(s1, s2);
        assert (s1 != s2);
    }
}

// 
// Given a binary tree, write a function to get the maximum width of the given tree. 
// The width of a tree is the maximum width among all levels. The binary tree has 
// the same structure as a full binary tree, but some nodes are null.
// 
// The width of one level is defined as the length between the end-nodes (the leftmost 
// and right most non-null nodes in the level, where the null nodes between the 
// end-nodes are also counted into the length calculation.
//
// Example 1:
// Input: 
//            1
//          /   \
//         3     2
//        / \     \
//       5   3     9 
// 
// Output: 4
// Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
//
// Example 2:
// Input: 
//           1
//          /  
//         3    
//        / \
//       5   3     
//
// Output: 2
// Explanation: The maximum width existing in the third level with the length 2 (5,3).
//
// Example 3:
// Input: 
//           1
//          / \
//         3   2 
//        /        
//       5      
// Output: 2
// Explanation: The maximum width existing in the second level with the length 2 (3,2).
//
// Example 4:
// Input: 
//           1
//          / \
//         3   2
//        /     \
//       5       9 
//      /         \
//     6           7
// Output: 8
// Explanation:The maximum width existing in the fourth level with the length 8 
// (6,null,null,null,null,null,null,7).
// Note: Answer will in the range of 32-bit signed integer.
//  
//
// Solution #1: DFS
// Beats: 20%
//
int Solution::widthOfBinaryTree(TreeNode* root) {
    // index is depth of level. 
    // value is idx of left most node in each level;
    // root: 1
    // parent: i, left child: 2*i, right child : 2*i + 1;
    vector<int> lefts; 
    return widthOfBinaryTreeDFS(root, 1, 0, lefts);
}

// 
// For a given node x with its "idx" and depth of level d, return the max width in this level;
//
int Solution::widthOfBinaryTreeDFS(TreeNode* x, int idx, int d, vector<int>& lefts) {
    if (x == nullptr) return 0;
    if (d >= lefts.size())  // meaning x is the first node found in this level, and it is left most node since we are doing DFS visting left node firstly;
        lefts.push_back(idx); 
    int wl = widthOfBinaryTreeDFS(x->left, 2*idx, d+1, lefts);
    int wr = widthOfBinaryTreeDFS(x->right, 2*idx+1, d+1, lefts);
    return max({idx+1 - lefts[d], wl, wr});
}

//
// 669. Trim a Binary Search Tree
// Given a binary search tree and the lowest and highest boundaries as L and R, 
// trim the tree so that all its elements lies in [L, R] (R >= L). You might need to 
// change the root of the tree, so the result should return the new root of the trimmed 
// binary search tree.
//
// Example 1:
// Input: 
//    1
//   / \
//  0   2
//
//  L = 1
//  R = 2
//
// Output: 
//    1
//      \
//       2
//
// Example 2:
// Input: 
//    3
//   / \
//  0   4
//   \
//    2
//   /
//  1
//
//  L = 1
//  R = 3
//
//Output: 
//      3
//     / 
//   2   
//  /
// 1
//  
TreeNode* Solution::trimBST(TreeNode* root, int L, int R) {
    if (root == nullptr) return root;
    if (root->val < L) {
        return trimBST(root->right, L, R);
    } else if (root->val > R) {
        return trimBST(root->left, L, R);
    } else {
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
    }
}

// 
// Given an integer array with no duplicates. A maximum tree building on this array is 
// defined as follow:
//
// The root is the maximum number in the array.
// The left subtree is the maximum tree constructed from left part subarray divided by 
// the maximum number.
// The right subtree is the maximum tree constructed from right part subarray divided 
// by the maximum number.
// Construct the maximum tree by the given array and output the root node of this tree.
//
// Example 1:
// Input: [3,2,1,6,0,5]
// Output: return the tree root node representing the following tree:
//
//       6
//     /   \
//    3     5
//     \    / 
//      2  0   
//       \
//        1
// Note:
// The size of the given array will be in the range [1,1000].
//
// Beats 60%
//
TreeNode* Solution::constructMaximumBinaryTree(vector<int>& nums) {
    return constructMaximumBinaryTree(nums.begin(), nums.end());
}

// 
// [first, last)
//
TreeNode* Solution::constructMaximumBinaryTree(auto first, auto last) {
    TreeNode* x = nullptr;
    if (first < last) {
        auto max = max_element(first, last);
        x = new TreeNode(*max);
        x->left = constructMaximumBinaryTree(first, max);
        x->right = constructMaximumBinaryTree(next(max), last);
    }
    return x;
}

// 
// 653. Two Sum IV - Input is a BST
// Given a Binary Search Tree and a target number, return true if there exist two elements 
// in the BST such that their sum is equal to the given target.
//  
//
//  Solution: Inorder traversal with unordered_set;
//  beats: 28%
//
bool Solution::findTarget(TreeNode* root, int k) {
    unordered_set<int>  s;
    queue<TreeNode*> q;
    TreeNode* p = root; 
    while (!q.empty() || p) {
        if (p) {
            q.push(p);
            p = p->left;
        } else {
            p = q.front();
            q.pop();
            // visit p
            if (s.count(k - p->val)) 
                return true;
            else 
                s.insert(p->val);
            p = p->right;
        }
    }
    return false;
}

// 
// 437. Path Sum III
// You are given a binary tree in which each node contains an integer value.
//
// Find the number of paths that sum to a given value.
//
// The path does not need to start or end at the root or a leaf, but it must 
// go downwards (traveling only from parent nodes to child nodes).
//
// The tree has no more than 1,000 nodes and the values are in the range 
// -1,000,000 to 1,000,000.
//
// Example:
//
// root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
//
//       10
//      /  \
//     5   -3
//    / \    \
//   3   2   11
//  / \   \
// 3  -2   1
//
// Return 3. The paths that sum to 8 are:
//
// 1.  5 -> 3
// 2.  5 -> 2 -> 1
// 3. -3 -> 11
//
int Solution::pathSum(TreeNode* root, int sum) {
    if (root == nullptr) return 0;
    return pathSumDFS(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}

int Solution::pathSumDFS(TreeNode* x, int sum) {
    if (x == nullptr) return 0;
    return x->val==sum?1:0 + pathSumDFS(x->left, sum - x->val) + pathSumDFS(x->right, sum - x->val);
}

// 
// 124. Binary Tree Maximum Path Sum
// 
// Given a binary tree, find the maximum path sum.
//
// For this problem, a path is defined as any sequence of nodes from some 
// starting node to any node in the tree along the parent-child connections. 
// The path must contain at least one node and does not need to go through 
// the root.
//
// For example:
// Given the below binary tree,
//
//        1
//       / \
//      2   3
// Return 6.
//
int Solution::int maxPathSum(TreeNode* root) {
    
}
