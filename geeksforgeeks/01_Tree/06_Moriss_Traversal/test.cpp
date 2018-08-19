#include "BSTUtil.hpp"
#include "Morris.hpp"
#include <algorithm>
void dump(vector<int>& arr, string prefix) {
    cout << prefix << endl;;
    for (auto x:arr)
        cout << x << ", ";
    cout << endl;
}

// keys in b and c should be a;
bool verify(vector<int>& a, vector<int>& b, vector<int>& c) {
    BSTUtil u;
    BinarySearchTree* bBST = u.arrayToBST(b);
    BinarySearchTree* cBST = u.arrayToBST(c);
    for (auto x:a) {
        if (bBST->search(x)) 
            assert(!cBST->search(x));
        else 
            assert(cBST->search(x));
    }
    return true;
}

int main() {
    BSTUtil util;
    vector<int> v = util.getUniqueRandomKeys(100000, 100000);
    BinarySearchTree* bst = util.arrayToBST(v);
    
    vector<int> keysToRemove = util.getUniqueRandomKeys(50000, 50000);
    dump(keysToRemove, "Keys to be removed: ");
    for (auto x:keysToRemove)
        bst->remove(x);

    MorrisTraversal mos(bst->getTree());
    vector<int> keysAfterRemove = mos.inOrder();

    bool ret = verify(v, keysToRemove, keysAfterRemove);
    assert(ret);
    return 0;
}
