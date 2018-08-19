/*
 * 436. Find Right Interval
 *
 * Given a set of intervals, for each of the interval i, check if there exists an interval j 
 * whose start point is bigger than or equal to the end point of the interval i, 
 * which can be called that j is on the "right" of i.
 *
 * For any interval i, you need to store the minimum interval j's index, which means that 
 * the interval j has the minimum start point to build the "right" relationship for interval i. 
 * If the interval j doesn't exist, store -1 for the interval i. 
 * Finally, you need output the stored value of each interval as an array.
 *
 * Note:
 * You may assume the interval's end point is always bigger than its start point.
 * You may assume none of these intervals have the same start point.
 * Example 1:
 * Input: [ [1,2] ]
 *
 * Output: [-1]
 *
 * Explanation: There is only one interval in the collection, so it outputs -1.
 * Example 2:
 * Input: [ [3,4], [2,3], [1,2] ]
 *
 * Output: [-1, 0, 1]
 *
 * Explanation: There is no satisfied "right" interval for [3,4].
 * For [2,3], the interval [3,4] has minimum-"right" start point;
 * For [1,2], the interval [2,3] has minimum-"right" start point.
 * Example 3:
 * Input: [ [1,4], [2,3], [3,4] ]
 *
 * Output: [-1, 2, -1]
 *
 * Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
 * For [2,3], the interval [3,4] has minimum-"right" start point.
 * */
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

/**** Definition for an interval. ****/
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    static bool mycomp(pair<int, int>& l, const int r) {
        return l.first < r;
    }
    vector<int> findRightInterval(vector<Interval>& intervals) {
        vector<int> res;
        vector<pair<int, int>> help(intervals.size());
        for (int i = 0; i < intervals.size(); i++) {
            help[i] = make_pair(intervals[i].start, i);
        }
        sort(help.begin(), help.end());
        for (int i = 0; i < intervals.size(); i++) {
            auto x = lower_bound(help.begin(), help.end(), intervals[i].end, mycomp); // 
            if (x != help.end())
                res.push_back(x->second);
            else
                res.push_back(-1);
        }
        return res;
    }
    
    // 
    // Passed
    // option 1: map with map::lower_bound/upper_bound
    // nlog(n)
    //
    vector<int> findRightInterval2(vector<Interval>& intervals) {
        vector<int> res;
        map<int, int> m;
        for (int i = 0; i < intervals.size(); i++) {
            m[intervals[i].start] = i;
        }
        for (int i = 0; i < intervals.size(); i++) {
            auto x = m.lower_bound(intervals[i].end);
            if (x != m.end())
                res.push_back(x->second);
            else 
                res.push_back(-1);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<Interval> v = {Interval(1,2)};
    vector<int> o; 
    o = s.findRightInterval(v);
    for (auto x:o) {
        cout << x << ",";
    }
    cout << endl;

    v = {Interval(3,4), Interval(2,3), Interval(1,2)};
    o = s.findRightInterval(v);
    for (auto x:o) {
        cout << x << ",";
    }
    cout << endl;

    v = {Interval(1,4), Interval(2,3), Interval(3,4)};
    o = s.findRightInterval(v);
    for (auto x:o) {
        cout << x << ",";
    }
    cout << endl;
    return 1;
}
