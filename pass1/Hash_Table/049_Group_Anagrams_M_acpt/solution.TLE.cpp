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
using namespace std;
class Solution {
private:
    bool isAnagrams (string& s1, string& s2) {
        if (s1.size() != s2.size()) return false;
        int map[26] = {0};
        for (int i = 0; i < s1.size(); i++)
            map[s1[i]-'a']++;

        for (int i = 0; i < s2.size(); i++) {
            if (map[s2[i]-'a'] == 0)
                return false;
            map[s2[i]-'a']--;
        }
        return true;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if (strs.size() == 0) return res;
        vector<string> tmp;
        tmp.push_back(strs[0]);
        res.push_back(tmp);
        bool found = false;
        for (auto it = next(strs.begin()); it != strs.end(); it++) {
            for (auto it2 = res.begin(); it2 != res.end(); it2++) {
                if (isAnagrams(*it, *(it2->begin()))) {
                    it2->push_back(*it);
                    found = true;
                    break;
                } 
            }
            if (!found)
                res.push_back(vector<string>{*it});
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
