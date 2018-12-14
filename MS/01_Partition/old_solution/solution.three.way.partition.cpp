#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    //
    // Three-way Partitioning
    // https://en.wikipedia.org/wiki/Dutch_national_flag_problem#Pseudocode
    //
    // test caes:
    // vector<int> v {20, 98, 58, 38, 51, 92, 78, 82, 92, 49, 75, 56};
    // int f1 = 75, f2 = 92;
    void partition(vector<int>& arr, int f1) {
        int i = 0, j = 0;
        int n = arr.size()-1;
        while (j <= n) {
            if (arr[j] < f1) 
                swap(arr[i++], arr[j++]);
            else if (arr[j] > f1)
                swap(arr[j], arr[n--]);
            else
                j++;
        }
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
    s.partition(v, f1);
    for (auto x:v)
        cout << x << ", ";
    cout << endl;
}


