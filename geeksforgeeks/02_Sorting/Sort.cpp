#include "Sort.hpp"
#include <algorithm>
#include <functional>


// 
// MS: partition array with two flags. 
//
// Given an array and two flags (f1 < f2), move all elements smaller than f1 to left, 
// elements larger than f2 to the right and elements between [f1, f2] between f1 and f2.
//
// 1. The partition must be stable. 
// 2. There can be duplicated elements.
// 3. f1 could be equal or smaller than f2.
// 4. f1, f2 can not exist in the array.
// 
#if 0
vector<int> Solution::partition(vector<int>& arr, int f1, int f2) {
    auto mid = std::partition(arr.begin(), arr.end(), [&](int value){return value <= f1;});       
    mid = std::partition(arr.begin(), mid, [&](int value){return value < f1;});       
    auto mid2 = std::partition(mid, arr.end(), [&](int value){return value <= f2;});
    std::partition(mid, mid2, [&](int value){return value < f2;});
    return arr;
}
#endif

vector<int> Solution::partition(vector<int>& arr, int f1, int f2) {
    auto mid = myPartition(arr.begin(), arr.end(), f1, std::less_equal<int>());
    mid = myPartition(arr.begin(), mid, f1, std::less<int>());
    auto mid2 = myPartition(mid, arr.end(), f2, std::less_equal<int>());
    myPartition(mid, mid2, f2, std::less<int>());
    return arr;
}
