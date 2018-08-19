/*
 * http://www.geeksforgeeks.org/heap-sort/
 * Why array based representation for Binary Heap?
 *     Since a Binary Heap is a Complete Binary Tree, it can be easily represented 
 *     as array and array based representation is space efficient. 
 * 
 *     If the parent node is stored at index I, 
 *     the left child can be calculated by 2 * I + 1 and 
 *     right child by 2 * I + 2 (assuming the indexing starts at 0).
 *
 * Heap Sort Algorithm for sorting in increasing order:
 *     1. Build a max heap from the input data.
 *     2. At this point, the largest item is stored at the root of the heap. 
 *        Replace it with the last item of the heap followed by reducing the size of heap by 1. 
 *        Finally, heapify the root of tree.
 *     3. Repeat above steps while size of heap is greater than 1.
 *
 * How to build the heap?
 *     Heapify procedure can be applied to a node only if its children nodes are heapified. 
 *     So the heapification must be performed in the bottom up order.
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    // Precondition: 
    //     Subtrees of parent rooted at index i is already max heap;
    // Recursively heapify a subtree rooted (top-down manner) at index i in arr[]. 
    // n is size of current heap;
    void Heapify(vector<int>& arr, int n, int i) {
        int largest = i;
        int l = 2*i+1, r = 2*i+2; 
        // Compare current root with left and right child.
        // Update as necessary to make sure parent always has largest value;
        if (l < n && arr[l] > arr[largest])
            largest = l;
        if (r < n && arr[r] > arr[largest])
            largest = r;
        // Keep updating subtree if parent index has changed
        if (largest != i) {
            swap(arr[largest], arr[i]);
            // recusively heapify affected subtree
            Heapify(arr, n, largest);
        }
    }

#define iLeftChild(x) ((x)*2+1)
    // Precondition:
    //      subTrees of parent rooted at index i is already max heap;
    // Heapify a subtree rooted at index i in arr[]; n is size of current heap size;
    void HeapifyIterative(vector<int>& arr, int n, int i) {
        int root = i;
        // Go down to heapify its child until out of heap range
        while (iLeftChild(root) < n) {
            int child = iLeftChild(root);
            int largest = root;
            // compare with left and right child and get the max one
            if (arr[largest] < arr[child]) 
                largest = child;
            if (child+1 < n && arr[largest] < arr[child+1])
                largest = child+1;
            if (largest != root) {
                swap(arr[root], arr[largest]);
                root = largest; // <<< keep heapify its child which was affected
            } else 
                return;
        }
    }
public:
    void HeapSort(vector<int>& arr, bool iterative = false) {
        int n = arr.size();
        // construct the heap from back to front, so that a[0] is always the largest element
        for (int i = n/2-1; i >=0; i--)
            iterative? HeapifyIterative(arr, n, i) : Heapify(arr, n, i);
        for (int i = n-1; i >= 0; i--) {
            swap(arr[0], arr[i]);   // <<< move largest element in heap (arr[0]) to end of arr. 
            // <<< adjust heap in top-down manner, since we've updated arr[0]
            iterative? HeapifyIterative(arr, i, 0) : Heapify(arr, i, 0);
        }
    }
};

int main() {
    vector<int> v = {21,3,22,45,67,99,12,5,9,20};
    Solution s;
    s.HeapSort(v, true);
    for (auto x:v) cout << x << ", ";
    cout << endl;
    return 0;
}
