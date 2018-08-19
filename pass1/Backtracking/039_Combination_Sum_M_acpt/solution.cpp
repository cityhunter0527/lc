/*
 * 39. Combination Sum
 * 
 * Given a set of candidate numbers (C) and a target number (T), 
 * find all unique combinations in C where the candidate numbers sums to T.
 *
 * The same repeated number may be chosen from C unlimited number of times.
 *
 * Note:
 *     All numbers (including target) will be positive integers.
 *     The solution set must not contain duplicate combinations.
 * 
 * For example, given candidate set [2, 3, 6, 7] and target 7, 
 * A solution set is: 
 * [
 * [7],
 * [2, 2, 3]
 * ]
 * */

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> res;

    vector<vector<int>> combinationSum(vector<int>& v, int t) {
        vector<int> a; // one solution
        bt(a, 0, 0, v, t);
        return res;
    }

    // DFS 
    void bt(vector<int>& a, int k, int sum, const vector<int>& v, const int t) {
        if (sum == t) {
            // get one good solution
            res.push_back(a); 
            return;
        }
        else if (sum > t) 
            return;
        else {
            for (int i = k; i < v.size(); i++) {
                a.push_back(v[i]);
                bt(a, i, sum+v[i], v, t);
                a.pop_back();
            }
        }
    }
};

int main () {
    vector<int> v = {2,3,6,7};
    Solution s;
    vector<vector<int>> res = s.combinationSum(v, 7);
    for (auto x : res) {
        for (auto y : x) {
            cout << y << ", "; 
        }
        cout << endl;
    }
    return 1;
}
