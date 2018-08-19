/*
 * Using set in STL
 * 1) Create an empty Set in C++ STL (Note that a Set in C++ STL is 
 *    implemented using Self-Balancing Binary Search Tree). And insert
 *    first element of array into the set.
 *
 * 2) Initialize inversion count as 0.
 *
 * 3) Iterate from 1 to n-1 and do following for every element in arr[i]
 *    a) Insert arr[i] into the set.
 *    b) Find the first element greater than arr[i] in set
 *       using upper_bound() defined Set STL.
 *    c) Find distance of above found element from last element in set
 *       and add this distance to inversion count.
 * 
 * 4) Return inversion count.
 * */

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int CountInversions(vector<int>& arr) {
        if (arr.size() == 0) return 0;
        set<int> st;
        int invCnt = 0;
        for (int i = 0; i < arr.size(); i++) {
            st.insert(arr[i]);
            auto x = st.upper_bound(arr[i]); // <<<< first element greater than arr[i]
            invCnt += distance(x, st.end());
        }
        return invCnt;
    }
};

int main() {
    vector<int> v = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    swap(v[0], v[12]);
    for (auto x:v) 
        cout << x << ", ";
    cout << endl;
    Solution s;
    cout << s.CountInversions(v) << endl;
    return 0;
}
