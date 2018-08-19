#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "resMgr.hpp"
using namespace std;

int main() {
    vector<pair<int, int>> tableParam;
    tableParam.push_back(make_pair(10, 2));
    tableParam.push_back(make_pair(10, 4));
    tableParam.push_back(make_pair(10, 10));
    ResvSysMgr res(tableParam);

    TimeSlice s;
    s.start = time(0);
    s.end = s.start + (60*60); // one hour later
    s.t = RECUR_NONE;
    s.numOccur = 1;
    vector<TableID> out = res.listAvailable(4, s);

    res.regist("18612334567", "Tom", "Wise", "Tom.Wise@gmail.com");
    res.regist("13633355678", "Chris", "White", "Chris.White@gmail.com");
    res.reserve(13633355678, 4, s);
    res.unregist(13633355678ULL);

    for (auto x:out) 
        cout << x << ", "; 
    cout << endl;

    return 1;
}
