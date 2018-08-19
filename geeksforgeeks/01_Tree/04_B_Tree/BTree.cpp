#include "BTree.hpp"
#include <queue>
#include <assert.h>


BTreeNode::BTreeNode() {
    keys.clear();
    c.clear();
}

BTreeNode::~BTreeNode() {
       
}

// validate property 4, 5 and 6;
bool BTree::validateProperty(BTreeNode* x, int curDepth, int bDepth) {
    // Property 4,5 and 6 do not apply for root node;
    if (x == mRoot) return true;
    if (numChildren(x) && curDepth >= bDepth) { 
        cout << "Invalid B-Tree node depth: (" << curDepth << ", " << bDepth << ")" << endl;
        return false;
    }
    if (numChildren(x) && curDepth < bDepth) return true;
    // Now x is leaf. 
    // validate B-Tree property;
    if (curDepth != bDepth) {
        cout << endl;
        cout << "Invalid B-Tree with leaf node depth: " << curDepth << endl;
        return false;
    }
    if ((n(x) > 2*mT-1) || (n(x) < mT - 1)) { 
        cout << endl;
        cout << "Invalid B-Tree with num of keys:" << n(x) << "which is not in [" << mT-1 << ", "<< 2*mT-1 << "]" << endl;
        return false;
    }
    return true;
}

// validate property 1 and 3.
bool BTree::isValidBTree() {
    vector<int> v = traverse();
    if (v.size() == 0) return true;
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < v[i-1])
            return false;
    }

    // Now mRoot must not be empty.
    queue<BTreeNode*>  q;
    BTreeNode* nodeSeparator = (BTreeNode*)0xdeadbeaf;
    BTreeNode* parentSeparator = (BTreeNode*)0xdeadabcd;
    q.push(mRoot);
    q.push(nullptr); // end of level
    int lev = 1;
    while (!q.empty()) {
        BTreeNode* p = q.front();
        q.pop();
        if (p == nodeSeparator) {
            continue;    
        } else if (p == parentSeparator) {
            continue;    
        } else if (p == nullptr) {
            if (!q.empty()) {
                lev++;
                q.push(nullptr);
            }
        } else {
            // If this node is leaf, check B-Tree property. 
            if (!numChildren(p) && !validateProperty(p, lev, getDepth())) return false;
            for (int i = 0; i < numChildren(p); i++) {
                q.push(p->c[i]);
                if (i != (numChildren(p) - 1))
                    q.push(nodeSeparator);
            }
            q.push(parentSeparator);
        }
    }
    return true;   
}

// 1. If x is leaf, just go ahead insert k in x->keys[];
// 2. If x is not leaf, find i that x->keys[i] < k and k < x->keys[i+1]
// ....a. Now k should be inserted to x->c[i]. 
// ....b. Check if x->c[i] is full or not, if x->c[i] is full, do split;
// ....c. Compare k with x->keys[i] (stored w/ median of x->c[i]);
// ........1)if k is larger than x->keys[i], insert k to x->c[i+1] whic is non-full.
// ........2)Otherwise, insert k to x->c[i], whic is non-full;
void BTree::insertNonFull(BTreeNode* x, int k) {
    int i = n(x) - 1;
    if (numChildren(x) == 0) { // x is leaf
        if (i < 0 || x->keys[i] < k)  // if there is no keys in x or k is largest one among all keys
            x->keys.push_back(k);     // insert k in the end 
        else { // i >= 0 && k is not the largest
            x->keys.push_back(x->keys[i--]);
            while (x->keys[i] > k && i >= 0) {
                x->keys[i+1] = x->keys[i];
                i--;
            }
            // either i is -1 or x->keys[i] is smaller than k;
            x->keys[i+1] = k; // insert k at pos i+1;
        }
        diskWrite(x);
    } else { // x is not leaf
        while (x->keys[i] > k && i >= 0) i--;
        // i is either -1 or x->keys[i] < k;
        i++;
        diskRead(x->c[i]);
        if (n(x->c[i]) == 2*mT - 1) { // x->c[i] is full
            splitChild(x, i);
            // if k is larger than the newly added median of x->c[i], 
            // k should be inserted to x->c[i+1];
            if (k > x->keys[i])
                i++;
        }
        // now x->c[i] must be non-full;
        insertNonFull(x->c[i], k);
    }
}

void BTree::insert(int k) {
    BTreeNode* r = mRoot;
    // if r is already full
    if (n(r) == (2*mT -1)) {
        // create a new empty node as new root;
        // split existing root and have s->c[0] pointint to left part and 
        // s->c[1] pointing to right part;
        BTreeNode* s = new BTreeNode();
        mRoot = s;
        // s->c[0] will be pointing to r;
        s->c.push_back(r);
        // r's median S will be moved up to s->keys[0];
        // s->c[0] will be still pointing to r;
        splitChild(s, 0); 
        // Now insert k to non-full node s;
        insertNonFull(s, k);
    } else {
        // just go ahead to insert k to non-full node r;
        insertNonFull(r, k); 
    }
}

//
// Description:  
// ....1. x->c[i] is full with 2t-1 keys;
// ....2. Move median of x->c[i] up to x.key[i]; 
// ....3. Split x->c[i] into two nodes y and z each w/ t-1 elements;
//
// Note: 
// ....x->c[i] must have 2t-1 elements which is full;
//                i-1  i                                  i-1   i   i+1
//     x.k[i]  ... N   W ...                   x.k[i]  ... N    S    W ...          
//                   |                                    ___/     \___
//                   |                ========>          /             \
//       P   Q   R   S   T   U   V                  P   Q   R          T   U   V 
//     |   |   |   |   |   |   |   |              |   |   |   |      |   |   |   |
//     T1  T2  T3  T4  T5  T6  T7  T8             T1  T2  T3  T4     T5  T6  T7  T8
//       y = x.c[i]                                y = x.c[i]         z = x.c[i+1]
//
// Steps:
// ....1. The left side of S (t-1) elements stays in y and 
// .......the right side of S (t-1) elements will be put to new node z;
// ....2. For all elements from x->c[i+1] to last element, move x->c[i+1] 
// .......to right to make room for newly created node z, which will be saved in x->c[i+1]; 
// ....3. For all elements from x->keys[i] to last element, 
// .......move x->keys[i] to right to make room for the Median S, which will be saved in 
// .......x->keys[i]; 
//
void BTree::splitChild(BTreeNode* x, int i) {
    BTreeNode* z = new BTreeNode();
    BTreeNode* y = x->c[i];
    int t = mT;

    // Step-1: Copy the right t-1 keys to z->keys[];
    for (int j = 0; j < t-1; j++) {
        z->keys.push_back(y->keys[j+t]);
    }

    // if y is not leaf, copy y->c[t] ... y->c[2t-1] to z->c[];
    if (numChildren(y)) {
        for (int j = 0; j < t; j++) {
            z->c.push_back(y->c[j+t]);
        }
        // remove the right t of y->c;
        y->c.resize(t); 
    }
    
    // Step-2: Update x->c[]:
    x->c.push_back(x->c[numChildren(x)-1]);
    for (int j = numChildren(x)-2; j >= i+1; j--)
        x->c[j+1] = x->c[j];
    x->c[i+1] = z;

    // Step-3: Update x->keys[]: 
    if (n(x))  // x has at least one key
        x->keys.push_back(x->keys[n(x)-1]);
    for (int j = n(x)-2; j >= i; j--)
        x->keys[j+1] = x->keys[j];

    if (n(x) == 0) // if there is no key in x yet;
        x->keys.push_back(y->keys[t-1]);
    else 
        x->keys[i] = y->keys[t-1];
    
    // remove the right t(including the median S) elements of y->keys;
    y->keys.resize(t-1);

    diskWrite(x);
    diskWrite(y);
    diskWrite(z);
}

pair<BTreeNode*, int> BTree::search(int k) {
    return search(mRoot, k);
}

pair<BTreeNode*, int> BTree::search(BTreeNode* x, int k) {
    int i = 0;
    while (i < n(x) && k > x->keys[i]) 
        i++;
    if (i < n(x) && k == x->keys[i])
        return make_pair(x, i);
    else if (numChildren(x) == 0) // x is leaf
        return make_pair(nullptr, 0);
    else { 
        // read x->c[i] into memory
        diskRead(x->c[i]);
        return search(x->c[i], k);
    }
}

void BTree::traverse(BTreeNode* x, vector<int>& res) {
    int i;
    for (i = 0; i < n(x); i++) {
        if (numChildren(x)) 
            traverse(x->c[i], res);
        res.push_back(x->keys[i]);
    }
    // i is now n(x), if x is not leaf, need to visit the last child of x;
    if (numChildren(x))
        traverse(x->c[i], res);
}

vector<int> BTree::traverse() {
    vector<int> res;
    traverse(mRoot, res);
    return res;
}

int BTree::getDepth() {
    int depth = 0;
    BTreeNode* p = mRoot;
    if (n(p) != 0) depth++;
    while (numChildren(p)) {
        depth++;
        p = p->c[0];
    }
    return depth;
}

// 
// node separator:   | 
// parent separator: #, nodes within same # belongs to same parent in above level;
// Example:
//                  
//      root  (4,      9,      16)                    <<<<< Level 0
//          /       |       |       \
//         /        |       |        \
//        /         |       |         \
//  (1, 2, 3) (5,6,7,8)     |         (17,18,19,20)   <<<<< Level 1
//                    (10,11,12,13,14,15)
//
// Output:
//  Level: 0 >> (4, 9, 16)
//  Level: 1 >> (1, 2, 3) | (5, 6, 7, 8) | (10, 11, 12, 13, 14, 15) | (17, 18, 19, 20) #
//  Level: 2 >>  #  #  #  #
//  
//  Here in Level 2, level 1 are all leaves, so just print #, no keys printed;
//
//
bool BTree::levelOrder() {
    queue<BTreeNode*>  q;
    BTreeNode* nodeSeparator = (BTreeNode*)0xdeadbeaf;
    BTreeNode* parentSeparator = (BTreeNode*)0xdeadabcd;
    q.push(mRoot);
    q.push(nullptr); // end of level
    int lev = 0;
    cout << "Level: "  << lev++ << " >> ";
    while (!q.empty()) {
        BTreeNode* p = q.front();
        q.pop();
        if (p == nodeSeparator) {
            cout << " | ";
            continue;    
        } else if (p == parentSeparator) {
            cout << " # ";
            continue;    
        } else if (p == nullptr) {
            if (!q.empty()) {
                q.push(nullptr);
                cout << endl;
                cout << "Level: "  << lev++ << " >> ";
            }
        } else {
            // visit keys in this node;
            cout << "(";
            for (int i = 0; i < n(p); i++) {
                cout << p->keys[i];
                if (i != n(p) - 1)
                    cout << ", ";
            }
            cout << ")";
            for (int i = 0; i < numChildren(p); i++) {
                q.push(p->c[i]);
                if (i != (numChildren(p) - 1))
                    q.push(nodeSeparator);
            }
            q.push(parentSeparator);
        }
    }
    cout << endl;
    return true;
}


void BTree::remove(int k) {
    // if k doesn't exist in BTree, just return;
    if (search(k).first == nullptr) return;
    remove(k, mRoot);
}

// get Predecessor of x->keys[i]
int BTree::getPred(BTreeNode* x, int i) {
    // get right most node of subTree x->c[i]
    x = x->c[i];
    while (numChildren(x)) // while x is not leaf
        x = x->c[n(x)];    // keep moving to right most child
    return x->keys[n(x)-1];
}

// get successor of x->keys[i]
int BTree::getSucc(BTreeNode* x, int i) {
    // get left most node of x->c[i+1]
    x = x->c[i+1];
    while (numChildren(x))  // while x is not leaf
       x = x->c[0];         // keep moving to left most child
    return x->keys[0];
}

// 
// Top-down manner: 
// We design this procedure to garuntee that whenever it calls itself recursively on a node x, 
// the number of keys in x is at least the minimum degree t. Note this condition is one more 
// key than the minimum required by usual B-tree condidions, so that sometimes a key may have 
// to be moved in to a child node before recusion descends to that child. This strengthened 
// condition allows us to delete a key from the tree in downward pass w/o having to "back up" 
// parent for adjustment.
//
// 1. If k is in node x and and x is leaf, delete the key k from x;
// 2. If k is in node x and x is an internal node, do following:
// ....a. If the child y that preceds k in node x has at least t keys, then find the predecessor k'
// .......of k in the subtree rooted at y. Recursively delete k', and replace k by k' in x (we can
// .......find k' and delete it in a single downward pass.)
// ....b. If y has fewer than t keys, then, symmetrically examine the child z that follows k in 
// .......node x. If z has at least t keys, then find the successor k' of k in the subtree rooted 
// .......at z. Recusively delete k', and replace k by k' in x. (We can find k' and delete it in 
// .......a single downward pass.)
// ....c. Otherwise, if both y and z have only t-1 keys, merge k and all of z into y, so that x 
// .......loses both k and the pointer to z, and y now contains 2t-1 keys. Then free z and 
// .......recursively delete k from y. 
// .......1. If x becomes empty, set root to y and delete root;
// 3. If k is not present in internal node x, determine the root x->c[i] of the appropriate 
// ....subtree that must contain k, if k is in the tree at all. If x->c[i] has only t-1 keys, 
// ....execute step 3.a or 3.b as necessary to guarantee that we descend to a node containing 
// ....at least t keys. Then finish by recusing on the appropriate child of x.
// ....a. If x->c[i] has only t-1 keys but has an immediate sibling with at least t keys, 
// .......1. Give x->c[i] an extra key by moving a key from x down into x->c[i], 
// .......2. moving a key from x->c[i]'s immediate sibling up into x, 
// .......3. and moving the appropriate child pointer from the 
// .......sibling into x->c[i].
// ....b. If x->c[i] and both of x->c[i]'s immediate siblings have t-1 keys, 
// .......1. move down a key from x down to new merged node to become the median key for that node; 
// .......2. merge x->c[i] with one sibling (delete the sibling after merge); 
// .......3. If x becomes empty because of 3.b.1, set new root to new merged node (x->c[i]) and delete the old root;
//
void BTree::remove(int k, BTreeNode* x) {
    bool foundInNode = false;
    int i;
    // check whether k is in node x;
    for (i = 0; i < n(x); i++) {
        if (x->keys[i] == k) { 
            foundInNode = true;
            break;
        }
    }
    if (foundInNode) {
        if (numChildren(x) == 0) {              // <<< Case-1: x is leaf
            // remove k in x->keys;
            x->keys.erase(begin(x->keys)+i);    // no need to update x->c[] since x is leaf;
        } else {                                // Case-2: x is not leaf
            // y is the child preceds k since x->keys[i] equals to k;
            BTreeNode* y = x->c[i];   
            // z is the symmetric child of y that succeedes k; 
            // Note z is always valid in x->c since x->keys[i] is a valid key;
            BTreeNode* z = x->c[i+1]; 
            int kx; // predecessor or successor of k;
            if (n(y) >= mT) {           // <<< Case-2.a
                kx = getPred(x, i);     // Predecessor
                remove(kx, y);          // remove k' from y: ensured y's keys >= t;
                x->keys[i] = kx;  
            } else if (n(z) >= mT) {    // <<< Case-2.b
                kx = getSucc(x, i);     // Successor
                remove(kx, z);          // remove k' from z: ensured z's keys >= t;
                x->keys[i] = kx;
            } else {                    // <<< Case-2.c
                // both y and z have only t-1 keys, since node in B-Tree can't have keys smaller than t-1;
                // remove k from x 
                x->keys.erase(begin(x->keys)+i);
                // remove the pointer from x to z;
                x->c.erase(begin(x->c)+i+1); 
                // <<< 2.c.1 x 
                // x must be root, as only root can have less than t-1 keys; 
                // an internal node will have t keys in this algorithm;
                if (!n(x)) { 
                    mRoot = y;
                    delete x;
                }
                // merge k and z to y
                y->keys.push_back(k);
                y->keys.insert(end(y->keys), begin(z->keys), end(z->keys));
                y->c.insert(end(y->c), begin(z->c), end(z->c));
                delete z;
                remove(k, y);
            }
        }
    } else  {   // <<< Case-3
        i = n(x) - 1;
        while (i >= 0 && x->keys[i] > k) i--;
        // i is either -1 or x->keys[i] < k
        i++;
        BTreeNode* saved = x->c[i]; // save x->c[i] in case x will be deleted (3.b.3) 
        // subtree x->c[i] should contain k;
        if (n(x->c[i]) == mT-1) {   // <<< Case-3.a
            int id = -1;            // id of child in x that has keys >= t;
            // get the sibling with at least t keys;
            if (i == 0) 
                id = n(x->c[i+1]) >= mT? i+1 : -1;
            else if (i == n(x)) 
                id = n(x->c[i-1]) >= mT? i-1 : -1;
            else if (n(x->c[i-1]) >= mT) id = i-1;
            else if (n(x->c[i+1]) >= mT) id = i+1;
            
            if (id != -1) {
                int down; // id of key in x that needs to be moved down to x->c[i];
                int up;   // id of key in sibling that needs to be moved up to x;
                // whether the key in x should be added to head of x->c[i], if false, add to tail;
                bool addtoHead = true; 
                if (id > i) { // sibling is on the right
                    down = i; 
                    up = 0; 
                    addtoHead = false; 
                } else {      // sibling is on the left 
                    down = id; 
                    up = n(x->c[id])-1;
                }
                // Now push down x->keys[down] to x->c[i] so that child i of x could have t children;
                if (addtoHead) { 
                    x->c[i]->keys.insert(begin(x->c[i]->keys), x->keys[down]);  // 3.a.1 move down to head 
                    if (numChildren(x->c[i])) {                                 // 3.a.3 only need to update child link of x->c[i] when it is not leaf
                        x->c[i]->c.insert(begin(x->c[i]->c), 
                                x->c[id]->c[numChildren(x->c[id])-1]);          // copy sibling's last child link to x->c[i]'s head
                        x->c[id]->c.erase(prev(x->c[id]->c.end()));             // remove it from sibling's child
                    }
                }
                else {
                    x->c[i]->keys.push_back(x->keys[down]);     // 3.a.1 move down to tail
                    if (numChildren(x->c[i])) {                 // 3.a.3 only need to child link when it is not leaf
                        x->c[i]->c.push_back(x->c[id]->c[0]);   // copy sibling's first child to x->c[i]'s tail
                        x->c[id]->c.erase(begin(x->c[id]->c));  // remove it from sibling's child
                    }
                }
                // 3.a.2 replace the key moved down with a key in the sibling(c[id]) whose children is >= t;
                x->keys[down] = x->c[id]->keys[up];
                // remove the key in sib that is moved up to x;
                x->c[id]->keys.erase(begin(x->c[id]->keys) + up);
            } else {  // <<<< Case-3.b
                // no siblings have keys >= t;
                // Get one of the immediate sibling and merge down to x->c[i]
                if (i == 0) { 
                    // sibling is x->c[i+1];
                    // 3.b.1 move down key i from x to x->c[i];
                    x->c[i]->keys.push_back(x->keys[i]);
                    
                    // 3.b.2 merge right sibling to x->c[i];
                    x->c[i]->keys.insert(end(x->c[i]->keys), begin(x->c[i+1]->keys), end(x->c[i+1]->keys));
                    x->c[i]->c.insert(end(x->c[i]->c), begin(x->c[i+1]->c), end(x->c[i+1]->c));

                    // remove key i from x;
                    x->keys.erase(begin(x->keys)+i);
                    // delete the right sibling node;
                    delete x->c[i+1];
                    // remove link to child c[i+1]
                    x->c.erase(begin(x->c)+i+1);
                } else { 
                    // let sibling be x->c[i-1];
                    // 3.b.1 move down key i-1 from x to x->c[i]
                    x->c[i]->keys.insert(begin(x->c[i]->keys), x->keys[i-1]);
                    
                    // 3.b.2 merge left sibling to x->c[i];
                    x->c[i]->keys.insert(begin(x->c[i]->keys), begin(x->c[i-1]->keys), end(x->c[i-1]->keys));
                    x->c[i]->c.insert(begin(x->c[i]->c), begin(x->c[i-1]->c), end(x->c[i-1]->c));

                    // remove key i-1 from x
                    x->keys.erase(begin(x->keys)+i-1);
                    // delete the left sibling node
                    delete x->c[i-1];
                    // remove child c[i-1]
                    x->c.erase(begin(x->c)+i-1);
                }
                // 3.b.3 if x becomes empty, set mRoot to x->c[i]; x must be old root;
                if (!n(x)) { 
                    mRoot = x->c[i];
                    saved = mRoot;
                    delete x;
                }
            }
        }
        // now x->c[i] has at least t keys;
        // recusively call remove on x->c[i] to remove k in downward subtree
        remove(k, saved);
    }
}

void BTree::diskRead(BTreeNode* x) {
    // if x is already in memory, return;
    // if not, read disk;
}

void BTree::diskWrite(BTreeNode* x) {
    // cached write with background flush;
}
