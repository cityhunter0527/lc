#ifndef __SORT_SOLUTIONS_HPP__
#define __SORT__SOLUTIONS_HPP__

#include <iostream>
#include <vector>
using namespace std;

// 
// [start, end)
// Move all elements that pass comp to the left. 
// Move all elements that fail comp to the right. 
// Return the first pos that fails comp, which is the same as std::partition;
//
#if 1
// STL version
template <typename Comp>
vector<int>::iterator myPartition(auto start, auto end, int pivot, Comp comp) {
    if (start == end) return start;
    
    // move first pos which fails comp;
    while (comp(*start, pivot)) 
        if (++start == end) return start;
    
    // start always points to the first element that fails comp;
    auto next = start;
    while (++next != end) { // go find the element that pass comp 
        if (comp(*next, pivot)) { // if found, swap with start;
            swap(*start, *next);
            ++start;
        }
    }
    return start;
}
#endif
#if 0
// My version
template <typename Comp>
vector<int>::iterator myPartition(auto start, auto end, int pivot, Comp comp) {
    if (start == end) return start;
    end--;
    while (start != end) {
        while (comp(*start, pivot) && (start != end)) start++;
        while (!comp(*end, pivot) && (start != end)) end--;
        if (start != end) swap (*start, *end);
    }
    return start;
}
#endif

class Solution {
public:
    // MS: Sort array with two flags. 
    vector<int> partition(vector<int>& arr, int f1, int f2);
};
#endif
