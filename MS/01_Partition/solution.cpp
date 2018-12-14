/*
 * 
 * [3,5,12,44,1,44,56,123,5,76,989]
 *      |             |
 *      |             |
 *      f1            f2
 * f1: 55, f2: 102
 *
 * move all elems smaller than f1 to left, move all elements bigger than f2 to right.
 * put all elems between [f1,f2] in the middle.
 *
 * PLUS:
 * * make sure the partition is stable, e.g. the elem's sequence stay the same if they are both <f1, >f2 or between [f1,f2].  
 * * what if there are duplicate elems in the array?
 * 
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 
    // http://stackoverflow.com/questions/37769227/partitioning-a-vector-using-stdpartition
    //
    // test caes:
    // vector<int> v {20, 98, 58, 38, 51, 92, 78, 82, 92, 49, 75, 56};
    // int f1 = 75, f2 = 92;
    //
    void partition(vector<int>& arr, int f1, int f2) {
        auto mid = std::partition(arr.begin(), arr.end(), [&](int i) { return i <= f1; });      
        std::partition(arr.begin(), mid, [&](int i) { return i < f1; });      
        auto mid2 = std::partition(mid, arr.end(), [&](int i) { return i <= f2; });      
        std::partition(mid, mid2, [&](int i) { return i < f2; });      
    }

    void stable_partition(vector<int>& arr, int f1, int f2) {
        auto mid = std::stable_partition(arr.begin(), arr.end(), [&](int i) { return i <= f1; });      
        std::stable_partition(arr.begin(), mid, [&](int i) { return i < f1; });      
        auto mid2 = std::stable_partition(mid, arr.end(), [&](int i) { return i <= f2; });      
        std::stable_partition(mid, mid2, [&](int i) { return i < f2; });      
    }
};

void test(vector<int>& arr, int n, int& f1, int& f2) {
    int i = 0;
    arr.clear();
    while (i++ < n)
        arr.push_back(rand()%100);

    f1 = min(arr[n/2], arr[n-1]);
    f2 = max(arr[n/2], arr[n-1]); 
}

void dump(vector<int>& v) {
    for (auto x:v) 
        std::cout << x << ", ";
    std::cout << "\n";
}

int main() {
    vector<int> v {20, 98, 58, 38, 51, 92, 78, 82, 92, 49, 75, 56};
    std::cout << "Before parition: \n";
    dump(v);

    int f1 = 75, f2 = 92;
    Solution s;
    s.stable_partition(v, f1, f2);

    std::cout << "After Partition: f1: " << f1 << ", f2: " << f2 << "\n";
    dump(v);

    int i = 0;
    srand(time(NULL));
    while (i++ < 100) {
        std::cout << "\n============== Test " << i << "=================\n";
        test(v, 15, f1, f2);
        std::cout << "Before parition: \n";
        dump(v);

        Solution s;
        s.stable_partition(v, f1, f2);
        std::cout << "After Partition: f1: " << f1 << ", f2: " << f2 << "\n";
        dump(v);
    }
}
