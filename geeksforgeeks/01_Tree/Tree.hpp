#ifndef __TREE_SOLUTION_HPP__
#define __TREE_SOLUTION_HPP__

#include <iostream>
#include <vector>
#include <unordered_set>
#include "BSTUtil/BSTUtil.hpp"
using namespace std;

class Solution {
private:
    int cycleNode(vector<int>& vParent, int k, int c = 0); 
    int widthOfBinaryTreeDFS(TreeNode* x, int idx, int d, vector<int>& lefts);
    TreeNode* constructMaximumBinaryTree(auto, auto);
    int pathSumDFS(TreeNode* x, int sum);
public: 
    // MS: General(M-ary) Tree to Binary Tree conversion
    TreeNode* GenTreeToBinTree(GenTreeNode* root);   
    // Amazon: Construct General Tree based on <parent, child> pairs;
    GenTreeNode* ConstructGenTree(vector<pair<int,int>>& nodeVec);
    // 685. Redundant Connection II
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges);
    // 684. Redundant Connection 
    vector<int> findRedundantConnection(vector<vector<int>>& edges);
    // 669. Trim a Binary Search Tree
    TreeNode* trimBST(TreeNode* root, int L, int R);
    // 662. Maximum Width of Binary Tree
    int widthOfBinaryTree(TreeNode* root);
    // 654. Maximum Binary Tree
    TreeNode* constructMaximumBinaryTree(vector<int>& nums);
    // 653. Two Sum IV - Input is a BST
    bool findTarget(TreeNode* root, int k);
    // 437. Path Sum III
    int pathSum(TreeNode* root, int sum); 
    // 124. Binary Tree Maximum Path Sum
    int maxPathSum(TreeNode* root);
};
#endif
