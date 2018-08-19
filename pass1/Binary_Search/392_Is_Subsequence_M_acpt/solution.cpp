/*
 * 392. Is Subsequence
 *
 * Given a string s and a string t, check if s is subsequence of t.
 *
 * You may assume that there is only lower case English letters in both s and t. 
 * t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).
 *
 * A subsequence of a string is a new string which is formed from the original string by 
 * deleting some (can be none) of the characters without disturbing the relative positions 
 * of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).
 *
 * Example 1:
 * s = "abc", t = "ahbgdc"
 * Return true.
 *
 * Example 2:
 * s = "axc", t = "ahbgdc"
 * Return false.
 *
 * Follow up:
 * If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one 
 * by one to see if T has its subsequence. In this scenario, how would you change your code?
 * */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        // for each char in s, find whethere there is a char in t;
        int is, it;
        for (is = 0, it = 0; it < t.size(); it++) {
            if (t[it] == s[is]) is++;
        }
        return is == s.size();
    }

    // 
    // Handling follow up:
    // a little bit slower as we need to process t and save to a helper 2D array.
    //
    bool isSubsequence2(string s, string t) {
        // 1-D: 'a' ~ 'z'
        // 2-D: store indexes of every occurance of 'a' ~ 'z' in "t";
        vector<vector<int>> v(26); 
        for (int i = 0; i < t.size(); i++) {
            v[t[i] - 'a'].push_back(i);
        }
        for (int i = 0, j = -1; i < s.size(); i++) {
            auto x = upper_bound(v[s[i]-'a'].begin(), v[s[i]-'a'].end(), j);
            if (x != v[s[i]-'a'].end()) {
                j = *x;
                continue;
            }
            return false;
        }
        return true;
    }
};

int main() {
    Solution s;
    cout << s.isSubsequence("abc", "ahbgdc") << endl;
    cout << s.isSubsequence("axc", "ahbgdc") << endl;
    return 1;
}
