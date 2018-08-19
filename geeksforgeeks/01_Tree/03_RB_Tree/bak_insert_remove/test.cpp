#include "rb.hpp"
#include "assert.h"
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;


// isRBTree a RBTree
class RBTreeTest {
protected:
    void printTree(RBTree& t);
    int getBlackHeight(TreeNode* n);
public:
    bool isRBTree(TreeNode*);
    bool inserttc1();
    bool deletetc1();
    // delete all elements w/ level order sequence;
    bool deletetc2();
    // delete all elements w/ inorder sequence;
    bool deletetc3();
    bool mixed();
};
// Validation:
// 1) Every node has a color either red or black.
// 2) Root of tree is always black.
// 3) There are no two adjacent red nodes (A red node cannot have a red parent or red child).
// 4) Every path from root to a NULL node has same number of black nodes.
bool RBTreeTest::isRBTree(TreeNode* root) {
    return getBlackHeight(root) != -1;
}

int RBTreeTest::getBlackHeight(TreeNode* n) {
    if (n == nullptr) return 0;
    int l = getBlackHeight(n->left);
    int r = getBlackHeight(n->right);
    int add = (n->color == BLACK? 1:0);
    if (l == -1 || r == -1 || l != r)
        return -1;
    return l+add;
}
void RBTreeTest::printTree(RBTree& t) {
    vector<vector<string>> res = t.printTree();
    for (auto x:res) {
        for (auto y:x)
            cout << y << ", ";
        cout << endl;
    }
}

// Test steps:
// 1. Insert random keys between [0...1000];
//    Duplicated keys will not be inserted;
// 2. Delete keys from 0 ~ 1000 if the key exists in rb tree;
bool RBTreeTest::mixed() {
    cout << "====== Start " << __FUNCTION__ << "=======" << endl;
    const int numKeys = 1000;
    srand(time(nullptr));
    RBTree t;
    vector<int> rbKeys(numKeys, 0);
    // insert
    cout << "Inserting: ";
    for (int i = 0; i < numKeys; i++) {
        int key = rand()%numKeys;
        if (rbKeys[key]) continue;
        rbKeys[key] = 1;
        cout << key << ", ";
        t.insert(key); 
        assert(isRBTree(t.getRoot()) == 1);
    }
    cout << endl;
    
    // remove
    cout << "Removing: ";
    for (int i = 0; i < numKeys; i++) {
        if (rbKeys[i]) {
            cout << i << ", ";
            t.remove(i);
        }
        assert(isRBTree(t.getRoot()) == 1);
    }
    cout << endl;
    cout << "====== END " <<  __FUNCTION__ << "=======" << endl;
    return true;
}
bool RBTreeTest::deletetc1() {
    RBTree t;
    cout << "====== Start " << __FUNCTION__ << "=======" << endl;
    // insert node 
    t.insert(7);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(18);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(10);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(11);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3); // <<< duplicated key will just be ignored.
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(8);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(22);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(26);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(2);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(6);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(13);  // 2,3,6,7,8,10,11,13,18,22,26
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(9);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(1);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(17);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(19);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(20);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(4);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(5);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(12);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(14);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(15);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(23);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(24);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(16);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(21);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(25);
    assert(isRBTree(t.getRoot()) == 1);

    t.remove(11);
    assert(isRBTree(t.getRoot()) == 1); 
    t.remove(14);
    assert(isRBTree(t.getRoot()) == 1);
    t.remove(18);  
    assert(isRBTree(t.getRoot()) == 1);
    printTree(t);
    t.remove(20);
    assert(isRBTree(t.getRoot()) == 1); 
    printTree(t);

    t.remove(21);
    assert(isRBTree(t.getRoot()) == 1);
    t.remove(19);
    assert(isRBTree(t.getRoot()) == 1);
    printTree(t);
    t.remove(12);
    assert(isRBTree(t.getRoot()) == 1);
    t.remove(122); // remove an non-exist key should just return;
    printTree(t);
    cout << "====== END " <<  __FUNCTION__ << "=======" << endl;
    return true;
}

// delete all elements with level order sequence;
bool RBTreeTest::deletetc2() {
    RBTree t;
    cout << "====== Start " << __FUNCTION__ << "=======" << endl;
    // insert node 
    t.insert(7);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(18);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(10);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(11);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3); // <<< duplicated key will just be ignored.
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(8);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(22);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(26);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(2);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(6);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(13);  // 2,3,6,7,8,10,11,13,18,22,26
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(9);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(1);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(17);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(19);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(20);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(4);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(5);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(12);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(14);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(15);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(23);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(24);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(16);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(21);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(25);
    assert(isRBTree(t.getRoot()) == 1);
    printTree(t);

    vector<int> v = {11, 7, 17, 3, 9, 13, 22, 2, 5, 8, 10, 12, 15, 19, 24, 1, 4, 6, 14, 16, 18, 20, 23, 26, 21, 25};
    for (int i = 0; i < v.size(); i++) {
        t.remove(v[i]);
        assert(isRBTree(t.getRoot()) == 1);
    }

#if 0
    vector<int> v = t.levelOrder();
    for (auto x:v) {
        t.remove(x);
        assert(isRBTree(t.getRoot()) == 1);
        printTree(t);
    }
#endif
    cout << "====== END " <<  __FUNCTION__ << "=======" << endl;
    return true;
}


bool RBTreeTest::deletetc3() {
    RBTree t;
    cout << "====== Start " << __FUNCTION__ << "=======" << endl;
    // insert node 
    t.insert(7);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(18);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(10);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(11);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3); // <<< duplicated key will just be ignored.
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(8);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(22);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(26);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(2);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(6);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(13);  // 2,3,6,7,8,10,11,13,18,22,26
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(9);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(1);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(17);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(19);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(20);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(4);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(5);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(12);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(14);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(15);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(23);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(24);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(16);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(21);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(25);
    assert(isRBTree(t.getRoot()) == 1);

    printTree(t);

    vector<int> v = t.inOrder();
    for (auto x:v) {
        t.remove(x);
        assert(isRBTree(t.getRoot()) == 1);
    }
    cout << "====== END " <<  __FUNCTION__ << "=======" << endl;
    return true;
}

bool RBTreeTest::inserttc1() {
    cout << "====== Start " << __FUNCTION__ << "=======" << endl;
    RBTree t; 
    // insert node test
    t.insert(7);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(18);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(10);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(11);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(3); // <<< duplicated key will just be ignored.
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(8);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(22);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(26);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(2);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(6);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(13);  // 2,3,6,7,8,10,11,13,18,22,26
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(9);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(1);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(17);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(19);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(20);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(4);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(5);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(12);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(14);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(15);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(23);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(24);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(16);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(21);
    assert(isRBTree(t.getRoot()) == 1);
    t.insert(25);
    assert(isRBTree(t.getRoot()) == 1);

    printTree(t);
    
    cout << "====== END " <<  __FUNCTION__ << "=======" << endl;
    return true;
}

int main() {
    RBTreeTest test;
    test.inserttc1();
    test.deletetc1();
    test.deletetc2();
    test.deletetc3();
    test.mixed();
    return 0;
}
