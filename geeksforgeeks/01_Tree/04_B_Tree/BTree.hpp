#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// 
// In most systems, the running time of B-Tree algorithm depends on primarily
// on the number Disk-Read and Disk-Write operations it performs, we typically 
// want each of these operations to read or write as much information as possible. 
// Thus, a B-tree node is usually as large as a whole disk page, and 
// this size limits the number of children a B-bree node can have.
// 
// FOr a large B-tree sotred on a disk, we often see branching factors 
// between 50 and 2000, depending on the size of a key relative to the disk 
// page. For example, a branching factor of 1001 and height 2 can store over 
// one billion keys; nevertheless, since we can keep the root node permanently
// in main memory, we can find any key in this tree by making at most only two
// disk access;
// 
// B-Tree properties:
// 1. Every Node x has keys currently stored in x. The keys are in nondescreasing order;
// ...which is x.keys[0] <= x.keys[1] <= ... <= x.keys[n-1];
// ...x is either a leaf (if no children) or an internal node.
// 2. Each internal node x contains n+1 pointers x->c[0], x->c[1] ... x->c[n] to its children.
// ...Leaf nodes have no children;
// 3. The keys x->keys[i] separate the ranges of keys stored in each child subtree: if k[i] is 
// ...any key stored in subtree with root x->c[i], then
// ... k0 <= x->keys[0] <= k1 <= x->keys[1] <= ... kn-1 <= x->keys[n-1] <= kn
// 4. All leaves have the same depth, which is the tree's height h;
// 5. Every node other than the root must have at least t-1 keys. Every internal node other 
// ...than the root thus has at least t children. If tree is nonempty, root must have at least
// ...one key. 
// 6. Every node may contain at most 2t-1 keys. Every internal node may have at most 2t children. 
// ...We say a node is full if it contains exact 2t-1 keys.
//
class BTreeNode { // << a b-tree node is normall size of file system page, e.g. 8KB;
public:
    vector<int>         keys;   // an array of keys;
    vector<BTreeNode*>  c;      // an array of children pointers;
    BTreeNode();               
    ~BTreeNode();
};

class BTree {
private:
    BTreeNode* mRoot;       // pointer to root node;
    int        mT;          // minimum degree 
protected:
    void traverse(BTreeNode* x, vector<int>& res);
    pair<BTreeNode*, int> search(BTreeNode* x, int k);
    void splitChild(BTreeNode* x, int i);
    void insertNonFull(BTreeNode* x, int k);
    void diskRead(BTreeNode* x);
    void diskWrite(BTreeNode* x);
    int n(BTreeNode* x) {return x->keys.size();}
    int numChildren(BTreeNode* x) {return x->c.size();}
    void remove(int k, BTreeNode* x);
    int getDepth();
    bool validateProperty(BTreeNode* x, int curDepth, int bDepth);
    // get predecessor of x->keys[i]
    int getSucc(BTreeNode* x, int i);
    // get successor of of x->keys[i]
    int getPred(BTreeNode* x, int i);
    
public:
    // _t must be > 1; as _t being 1 is meaningless;
    BTree(int _t):mT(_t), mRoot(nullptr) { mRoot = new BTreeNode(); diskWrite(mRoot);}
    ~BTree() {delete mRoot;}
    pair<BTreeNode*, int> search(int k);
    vector<int> traverse(); // inOrder
    bool levelOrder();
    void insert(int k);
    void remove(int k);
    int getMinDegree(){return mT;}
    bool isValidBTree();
};
