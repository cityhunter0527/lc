/*
 * 49. Group Anagrams
 * Given an array of strings, group anagrams together.
 *
 * For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
 * Return:
 * [
 * ["ate", "eat","tea"],
 * ["nat","tan"],
 * ["bat"]
 * ]
 * Note: All inputs will be in lower-case.
 * */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if (strs.size() == 0) return res;
        unordered_map<string, int> m;
        for (auto s:strs) {
            string s1 = s;
            sort(s1.begin(), s1.end());
            if (m.find(s1) == m.end()) {
                res.push_back(vector<string>{s});
                m[s1] = res.size()-1;
            } else {
                res[m[s1]].push_back(s);
            }
        }
        return res;
    }
};

int main() {
    vector<string> s = {"eat", "tea", "tan", "ate", "nat", "bat"};
    Solution ss;
    vector<vector<string>> out = ss.groupAnagrams(s);
    for (auto x:out)  {
        for (auto y:x) {
            cout << y << ",";
        }
        cout << endl;
    }
    return 1;
}
