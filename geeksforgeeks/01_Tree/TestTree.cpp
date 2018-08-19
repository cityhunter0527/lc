#include "TestTree.hpp"
#include "Tree.hpp"

// 
//        1                 1
//    /  / \  \            /
//   2  3   4  5   ====>  2
//     /|\                  \
//    6 7 8                  3
//                          /  \
//                         6     4
//                          \      \
//                           7      5
//                            \
//                             8
//
bool GenTreeToBinTreeTest::tc1() {
    GenTreeNode* r = new GenTreeNode(1);
    r->c.push_back(new GenTreeNode(2));
    r->c.push_back(new GenTreeNode(3));
    r->c.push_back(new GenTreeNode(4));
    r->c.push_back(new GenTreeNode(5));
    r->c[1]->c.push_back(new GenTreeNode(6));
    r->c[1]->c.push_back(new GenTreeNode(7));
    r->c[1]->c.push_back(new GenTreeNode(8));
    
    Solution s;
    TreeNode* x = s.GenTreeToBinTree(r);
    BinarySearchTree t(x);
    t.inOrderPrint();
    return true;
}

//
//         1                         1
//     /   |   \                    /
//   2     3     4     ====>       2
//  /    / | \   / \            /    \
// 11   8  9 10  5  6          11     3
//                 /                /    \
//                7                8       4
//                                  \     / 
//                                   9    5 
//                                    \    \
//                                     10   6
//                                         /
//                                        7 
//
bool GenTreeToBinTreeTest::tc2() {
    GenTreeNode* r = new GenTreeNode(1);
    r->c.push_back(new GenTreeNode(2));
    r->c.push_back(new GenTreeNode(3));
    r->c.push_back(new GenTreeNode(4));
    r->c[0]->c.push_back(new GenTreeNode(11));
    r->c[1]->c.push_back(new GenTreeNode(8));
    r->c[1]->c.push_back(new GenTreeNode(9));
    r->c[1]->c.push_back(new GenTreeNode(10));
    r->c[2]->c.push_back(new GenTreeNode(5));
    r->c[2]->c.push_back(new GenTreeNode(6));
    r->c[2]->c[1]->c.push_back(new GenTreeNode(7));
    Solution s;
    TreeNode* x = s.GenTreeToBinTree(r);
    BinarySearchTree t(x);
    t.inOrderPrint();
    return true;
}

// 
//         1
//      /     \
//     2        3
//   /  \     / | \
//  4    5   6  7  8
//
//
bool ConstructGenTreeTest::tc1() {
    vector<pair<int, int>> v; 
    v.push_back(make_pair(3,7));
    v.push_back(make_pair(1,2));
    v.push_back(make_pair(2,4));
    v.push_back(make_pair(3,8));
    v.push_back(make_pair(2,5));
    v.push_back(make_pair(3,6));
    v.push_back(make_pair(1,3));
    Solution s;
    GenTreeNode* r = s.ConstructGenTree(v);
    GeneralTree  t;
    t.levelOrderPrint(r);
    return true;
}


// 
//         1   
//     /   |    \
//   2     3      4  
//  /    / | \   /  \
// 11   8  9 10  5   6
// |         / \     / 
// 12       13 14   7 
//
bool ConstructGenTreeTest::tc2() {
    vector<pair<int, int>> v; 
    v.push_back(make_pair(1,2));
    v.push_back(make_pair(1,4));
    v.push_back(make_pair(2,11));
    v.push_back(make_pair(3,8));
    v.push_back(make_pair(3,9));
    v.push_back(make_pair(3,10));
    v.push_back(make_pair(4,5));
    v.push_back(make_pair(4,6));
    v.push_back(make_pair(1,3));
    v.push_back(make_pair(6,7));
    v.push_back(make_pair(11,12));
    v.push_back(make_pair(10,13));
    v.push_back(make_pair(10,14));

    Solution s;
    GenTreeNode* r = s.ConstructGenTree(v);
    GeneralTree  t;
    t.levelOrderPrint(r);
    return true;
}

// 
// 1
//  / \
// v   v
// 2-->3
// 
// output: [2,3]
//
bool TestTree685::tc1() {
    vector<vector<int>> v = {{1,2}, {1,3}, {2,3}};
    Solution s;
    vector<int> o = s.findRedundantDirectedConnection(v);
    print(o);
    return true;
}

// 
// 5 <- 1 -> 2
//      ^    |
//      |    v
//      4 <- 3
// output: [4,1]
//
bool TestTree685::tc2() {
    vector<vector<int>> v = {{1,2}, {2,3}, {3,4}, {4,1}, {1,5}};
    Solution s;
    vector<int> o = s.findRedundantDirectedConnection(v);
    print(o);
    return true;
}

//     
//     4-> 2 -> 1 <- 3
//     ^        |
//     |________|
//
//  Output: [2,1]
//
bool TestTree685::tc3() {
    vector<vector<int>> v = {{2,1}, {3,1}, {4,2}, {1,4}};
    Solution s;
    vector<int> o = s.findRedundantDirectedConnection(v);
    print(o);
    return true;
}

//
//       1
//      /
//     5
//    / \
//   2   3
//  / \
//  \ /
//   4
//  Output: [4,2]
// 
bool TestTree685::tc4() {
    vector<vector<int>> v = {{4,2}, {1,5}, {5,2}, {5,3}, {2,4}};
    Solution s;
    vector<int> o = s.findRedundantDirectedConnection(v);
    print(o);
    return true;
}

// 
// 5 - 1 - 2
//     |   |
//     4 - 3
//
bool TestTree684::tc1() {
    vector<vector<int>> v = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    Solution s;
    vector<int> o = s.findRedundantConnection(v);
    print(o);
    return true;
}

// 
// [[3,7],[1,4],[2,8],[1,6],[7,9],[6,10],[1,7],[2,3],[8,9],[5,9]]
//
//    3 - 2 - 8
//     \     /
//      7 - 9 - 5
//      |
//      1 - 4
//      |
//      6 - 10
//
bool TestTree684::tc2() {
    vector<vector<int>> v = {{3,7}, {1,4}, {2,8}, {1,6}, {7,9}, {6,10}, {1,7}, {2,3}, {8,9}, {5,9}};
    Solution s;
    vector<int> o = s.findRedundantConnection(v);
    print(o);
    return true;
}


//            1
//          /   \
//         3     2
//        / \     \
//       5   4     9 
// 
// Output: 4
//
bool TestTree662::tc1() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(3);
    r->right= new TreeNode(2);
    r->left->left = new TreeNode(5);
    r->left->right = new TreeNode(4);
    r->right->right = new TreeNode(9);
    Solution s;
    assert(4 == s.widthOfBinaryTree(r));
    return true;
}


// 
//           1
//          /  
//         3    
//        / \
//       5   3     
//
// Output: 2
//
bool TestTree662::tc2() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(3);
    r->left->left = new TreeNode(5); 
    r->left->right = new TreeNode(3); 
    Solution s;
    assert(2 == s.widthOfBinaryTree(r));
    return true;
}


// 
//           1
//          / \
//         3   2 
//        /        
//       5      
// Output: 2
//
bool TestTree662::tc3() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(3);
    r->right = new TreeNode(2);
    r->left->left = new TreeNode(5);
    Solution s;
    assert(2 == s.widthOfBinaryTree(r));
    return true;
}

//
//           1
//          / \
//         3   2
//        /     \
//       5       9 
//      /         \
//     6           7
// Output: 8
//
bool TestTree662::tc4() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(3);
    r->right = new TreeNode(2);
    r->left->left = new TreeNode(5);
    r->left->left->left = new TreeNode(6);

    r->right->right = new TreeNode(9);
    r->right->right->right = new TreeNode(7);

    Solution s;
    assert(8 == s.widthOfBinaryTree(r));
    return true;
}

bool TestTree669::tc1() {
    BSTUtil util;
    vector<int> v = util.getUniqueRandomKeys(30, 30);
    sort(v.begin(), v.end());
    BinarySearchTree* pbst = util.sortedArrayToBST(v);
    TreeNode* r = pbst->getTree();
    Solution s;
    r = s.trimBST(r, 10, 20);
    BinarySearchTree bst(r);
    bst.inOrderPrint();
    return true;
}

bool TestTree654::tc0() {
    vector<int> v = {4, 8, 5, 1, 7, 6, 2, 3, 0, 9};
    print(v);
    Solution s;
    TreeNode* r = s.constructMaximumBinaryTree(v);
    BSTUtil u;
    vector<vector<string>> o = u.printTree(r);
    print(o);
    return true;
}

bool TestTree654::tc1() {
    BSTUtil u;
    vector<int> v = u.getUniqueRandomKeys(10, 10);
    print(v);
    Solution s;
    TreeNode* r = s.constructMaximumBinaryTree(v);
    vector<vector<string>> o = u.printTree(r);
    print(o);
    return true;
}

// 
//    2
//   / \
//  1   3
//
bool TestTree653::tc0() {
    Solution s;
    TreeNode* r = new TreeNode(2);
    r->left = new TreeNode(1);
    r->right = new TreeNode(3);
    assert(s.findTarget(r, 4));
    return true;
}

// Input: 
//     5
//    / \
//   3   6
//  / \   \
// 2   4   7
bool TestTree653::tc1() {
    Solution s;
    TreeNode* r = new TreeNode(5);
    r->left = new TreeNode(3);
    r->right = new TreeNode(6);
    r->left->left = new TreeNode(2);
    r->left->right = new TreeNode(4);
    r->right->right = new TreeNode(7);
    assert(s.findTarget(r, 9));
    assert(s.findTarget(r, 28) == false);
    assert(s.findTarget(r, 5));
    assert(s.findTarget(r, 13));
    assert(s.findTarget(r, 14) == false);
    assert(s.findTarget(r, 7));
    return true;
}

//       10
//      /  \
//     5   -3
//    / \    \
//   3   2   11
//  / \   \
// 3  -2   1
bool TestTree437::tc1() {
    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(5);
    r->right = new TreeNode(-3);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(2);
    r->left->right->right = new TreeNode(1);
    r->left->left->left = new TreeNode(3);
    r->left->left->right = new TreeNode(-2);
    r->right->right = new TreeNode(11);
    Solution s;
    int k = s.pathSum(r, 8);
    cout << k << endl;
    assert(k == 3);
    return true;
}
