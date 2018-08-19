#include "TestSort.hpp"
#include "Sort.hpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <assert.h> 

bool TestSortPartition::verify(vector<int>& v, int f1, int f2) {
    assert (f1 <= f2);
    int i = 0, n = v.size();
    while (i < n && v[i++] < f1);
    while (i < n && v[i++] == f1);
    if (i < n && v[i] < f1) 
        assert(false);

    while (i < n && v[i++] < f2);
    if (i < n && v[i] <= f1) 
        assert(false);

    while (i < n && v[i++] == f2);
    if (i < n && v[i] < f2) 
        assert(false);

    while (i < n && v[i++] > f2);
    if (i < n && v[i] <= f2) 
        assert (false);
    return true;
}

bool TestSortPartition::tc0() {
    vector<int> v = {12, 19, 8, 3, 9, 18, 14, 15, 8, 8, 10, 17, 18, 4, 6, 8, 2, 15, 12, 10};
    int f1 = 0, f2 = 14;
    cout << f1 << ", " << f2 << endl;
    print(v);
    Solution s;
    v = s.partition(v, f1, f2);
    print(v);
    verify(v, f1, f2);
    return true;
}
bool TestSortPartition::tc1() {
    vector<int> v; 
    Solution s;
    int f1, f2;

    v.clear();
    v = {20, 98, 58, 38, 51, 92, 78, 82, 92, 49, 75, 56};
    f1 = 75; f2 = 92;
    if (f1 > f2) swap(f1, f2);
    cout << f1 << ", " << f2 << endl;
    print (v);
    v = s.partition(v, f1, f2);
    print(v);
    verify(v, f1, f2);

    v.clear();
    f1 = rand()%30; f2 = f1 + 10;
    if (f1 > f2) swap(f1, f2);
    cout << f1 << ", " << f2 << endl;
    v = getUniqueRandomKeys(20, 30);
    print (v);
    v = s.partition(v, f1, f2);
    print(v);
    verify(v, f1, f2);

    f1 = rand()%30; f2 = f1 + 10;
    if (f1 > f2) swap(f1, f2);
    v.clear();
    cout << f1 << ", " << f2 << endl;
    v = getRandomKeys(20, 30);
    print (v);
    v = s.partition(v, f1, f2);
    print(v);
    verify(v, f1, f2);

    f1 = rand()%30; f2 = f1 + 10;
    if (f1 > f2) swap(f1, f2);
    cout << f1 << ", " << f2 << endl;
    v.clear();
    v = getRandomKeys(20, 30);
    print(v);
    v = s.partition(v, f1, f2);
    print(v);
    verify(v, f1, f2);
    return true;
}

bool TestSortPartition::tc2() {
    int cnt = 0, f1, f2;
    int numElem = 100, range = 400, runCnt = 1000000;
    Solution s;
    while (cnt++ < runCnt) {
        vector<int> v = getRandomKeys(numElem, range);
        f1 = rand()%range; 
        f2 = rand()%range;
        if (f1 > f2) swap(f1, f2);
        //cout << f1 << ", " << f2 << endl;
        //print(v);
        vector<int> o = s.partition(v, f1, f2);
        //print(o);
        verify(o, f1, f2);
    }
    return true;
}
