/*
 * 378. Kth Smallest Element in a Sorted Matrix
 * Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
 *
 * Note that it is the kth smallest element in the sorted order, not the kth distinct element.
 *
 * Example:
 *
 * matrix = [
 *    [ 1,  5,  9],
 *    [10, 11, 13],
 *    [12, 13, 15]
 * ],
 * k = 8,
 *
 * return 13.
 * Note: 
 * You may assume k is always valid, 1 <= k <= n^2.
 * */
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
class Solution {
public:
    // 
    // min Heap
    // Basic Idea:
    //    - Kick out one smallest element once a time, also adding next most possible small element to the candidates.
    //    - Repeat k-1 times.
    //
    // Implementation:
    // Build a minHeap of elements from the first row.
    // Do the following operations k-1 times :
    // 1. Every time when you poll out the root(Top Element in Heap), you need to know the row number and column number of that element(so we can create a tuple class here), 
    // 2. Remove the root element (a minHeap automatically reorg internally to put smallest elememnt on top) 
    // 3. Push the next element from the same column to the minHeap (again, smallest will be on top). 
    //
    // Return current top element in heap.
    // Complexity: O(klogk)
    class mycomp {
    public:
        bool operator() (const tuple<int, int, int>& t1, const tuple<int, int, int>& t2){
            // first elememnt is matrix element value.
            // minHeap: greater than
            return get<0>(t1) > get<0>(t2); 
        }
    };
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // tuple:
        // 0: matrix element value;
        // 1: row of the element
        // 2: col of the element
        priority_queue<tuple<int, int, int>, vector<tuple<int,int, int>>, mycomp> minHeap;
        int n = matrix.size();
        int i = 0;
        for (i = 0; i < n; i++)
            minHeap.push(make_tuple(matrix[0][i], 0, i));
        for (i = 0; i < k-1; i++) {
            // kick out one smallest element 
            auto t = minHeap.top();
            int r = get<1>(t);
            int c = get<2>(t);
            minHeap.pop();
            if (r == n-1) continue;
            minHeap.push(make_tuple(matrix[r+1][c], r+1, c));
        }
        // after kicking out K-1 smallest element, top is the kth smallest element
        return get<0>(minHeap.top());

    }
};

int main () {
    return 1;
}
