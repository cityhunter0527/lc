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
    void partition(vector<int>& arr, int f1, int f2) {
        // after below call, it will be
        // {20, 56, 58, 38, 51, 75, 49, 82, 92, 78, 92, 98} // << note 49 is on left side of 75 which is not allowed
        // we can not replace val < f1 with val <= f1, because we need to put all the elements equal to f1 to left part.
        auto mid = std::stable_partition(arr.begin(), arr.end(), [&](int val){return val <= f1;});
        // then we call partition again to strictly move all elements smaller than f1 (val < f1) to the left part
        std::stable_partition(arr.begin(), mid, [&](int val){return val < f1;});

        // Do the same as f2;
        auto mid2 = std::stable_partition(mid, arr.end(), [&](int val){return val <= f2;});
        std::stable_partition(mid, mid2, [&](int val){return val < f2;});
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
    while (i++ < 100) {
        test(v, 15, f1, f2);
        Solution s;
        s.partition(v, f1, f2);
        for (auto x:v) 
            cout << x << ", ";
        cout << endl;
    }
#endif
}
