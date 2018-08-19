#include "BinaryHeap.hpp"
#include <climits>

MinHeap::MinHeap(int cap):mCap(cap), mHeapSize(0) {
    mHeap.reserve(cap);
}

// 
// Assumption:
// ....i's subtrees are already heapified(no min heap property violation).
// 
// Description:
// ....Fixing downward for Min Heap violations;
// ....1. Get the smallest betwee i, i's left and i's right;
// ....2. If i is not the smallest, swap mHeap[i] and mHeap[smallest];
// ....3. Recursively call fixDownMinHeap(smallest);
//
void MinHeap::fixDownMinHeap(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < mHeapSize && mHeap[l] < mHeap[smallest])
        smallest = l;
    if (r < mHeapSize && mHeap[r] < mHeap[smallest])
        smallest = r;
    if (smallest != i) {
        swap(mHeap[smallest], mHeap[i]);
        fixDownMinHeap(smallest);
    }
}

// remove the root element
int MinHeap::extractMin() {
    if (mHeapSize <= 0) return INT_MIN;
    if (mHeapSize == 1) { mHeapSize--; return mHeap[0]; }
    int root = mHeap[0];
    mHeap[0] = mHeap[mHeapSize-1];
    mHeapSize--;
    fixDownMinHeap(0);
    return root;
}

// 
// Assumption:
// ....It is assumed new val is smaller than mHeap[i];
//
// Description:
// ....Descrease mHeap[i] to newVal;
//
void MinHeap::decreaseKey(int i, int newVal) {
    mHeap[i] = newVal;
    fixUpMinHeap(i);
}

// delete the key stored at index i;
void MinHeap::deleteKey(int i) {
    // fist push up this key to root by decraseing this key as IN_MIN;
    decreaseKey(i, INT_MIN);
    // then remove the min;
    extractMin();
}

// Description:
// ....Fix the min Heap violations from index i to root (bottom-top);
void MinHeap::fixUpMinHeap(int i) {
    while(i > 0 && mHeap[parent(i)] > mHeap[i]) {
        swap(mHeap[parent(i)], mHeap[i]);
        i = parent(i);
    }
}

// Description:
// ....Insert a new key: 'key'
//
// Return Val:
// ....false: fail to insert;
// ....true: successfully inserted;
bool MinHeap::insert(int key) {
    if (mHeapSize == mCap) {
        cout << "Overflow Error: Exceeding maximum Heap Size." << endl;
        return false;    
    }

    mHeapSize++;
    mHeap[mHeapSize-1] = key;

    // now fix minHeap if the newly inserted key violates minHeap property;
    fixUpMinHeap(mHeapSize-1);
    return true;
}
