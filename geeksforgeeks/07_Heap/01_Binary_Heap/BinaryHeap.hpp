#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> mHeap; // array of elements in heap;
    int mCap; // maximum possible size of minHeap
    int mHeapSize; // current number of elements of min Heap;
protected:
    // Fixing a min Heap starting from given index i down to bottom;
    // This function assumes i's subtrees are already heapified.
    void fixDownMinHeap(int i);
    // fixing Min Heap vilations starting from index i to top (bottom-top);
    void fixUpMinHeap(int i);
public:
    // constroctor
    MinHeap(int capacity);
    int left(int i) {return 2*i+1;}
    int right(int i) {return 2*i+2;}
    int parent(int i) {return (i-1)/2;}
    // return the minimum key(which is root) from heap;
    int getMin() {return mHeap[0];}
    // extract the root which is min element
    int extractMin();
    // delete a key stored at index i
    void deleteKey(int i);
    // decrease key index i to a new value 'newVal'
    // fix min Heap violations if there is any;
    void decreaseKey(int i, int newVal);
    // insert a new key 'k'
    bool insert(int k);
    int size() {return mHeapSize;}
    bool empty() {return mHeapSize == 0;}

    // test only;
    int getElement(int i) {
        if (i < mHeapSize) return mHeap[i];
        else return -1;
    } 
};
