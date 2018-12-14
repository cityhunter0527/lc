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
    // 1. not stable. 
    // 2. elements < f1 can be on the left side of f1 and right side of f2, which is a violation.
    int partition(vector<int>& arr, int start, int end, int f) {
        while (start < end) {
            // find first elem that is larger than f;
            while (arr[start] <= f && start < end) start++;
            // find first elem that is smaller than f;
            while (arr[end] > f && end > start) end--;
            swap(arr[start], arr[end]);
        }
        return start;
    }
    
    // TODO: Need to call partition twice for f1:
    // - first call with compare function as not larger than.
    // - second call with compare function as smaller than.
    //
    // Do the same for f2
    void partition(vector<int>& arr, int f1, int f2) {
        int bound = partition(arr, 0, arr.size()-1, f1); 
        partition(arr, bound, arr.size()-1, f2);
        return;
    }
};

void test(vector<int>& arr, int n, int& f1, int& f2) {
    int i = 0;
    arr.clear();
    while (i++ < n)
        arr.push_back(rand()%100);

    f1 = min(arr[n/2], arr[n-1]);
    f2 = max(arr[n/2], arr[n-1]); 
    cout << "f1: " << f1 << ", f2: " << f2 << endl;
    for (auto x:arr)
        cout << x << ", ";
    cout << endl;
}

int main() {
    vector<int> v {20, 98, 58, 38, 51, 92, 78, 82, 92, 49, 75, 56};
    int f1 = 75, f2 = 92;
    Solution s;
    s.partition(v, f1, f2);
    for (auto x:v) 
        cout << x << ", ";
    cout << endl;
#if 0
    int i = 0;
    srand(time(NULL));
    while (i++ < 10) {
        test(v, 15, f1, f2);
        Solution s;
        s.partition(v, f1, f2);
        for (auto x:v) 
            cout << x << ", ";
        cout << endl;
    }
#endif
}
