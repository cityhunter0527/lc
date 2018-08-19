/*
 * 139. Word Break
 *
 * Given a string s and a dictionary of words dict, determine if s can be segmented 
 * into a space-separated sequence of one or more dictionary words.
 *
 * For example, given
 * s = "leetcode",
 * dict = ["leet", "code"].
 *
 * Return true because "leetcode" can be segmented as "leet code".
 * */
#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

class Solution {
public:
    // DP: 
    // f[i] : s[0, i] is segmented. i >= 0;
    // f[i] = f[j] && s[j+1, i] is segmented. 0 <= j < i
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.size();
        bool f[n];
        fill_n(f, n, false);
        f[0] = wordDict.find(s.substr(0,1)) != wordDict.end();

        for (int i = 1; i < n; i++) {
            if (wordDict.find(s.substr(0, i+1)) != wordDict.end()) {
                f[i] = true;
                continue;
            }
            for (int j = 0; j < i; j++) {
                if (f[j] && wordDict.find(s.substr(j+1, i-j)) != wordDict.end()) {
                    f[i] = true;
                    break;
                }
            }
        }
        return f[n-1];
    }
};

int main () {
    // "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
    // ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
#if 1
    unordered_set<string> dict;
    dict.insert("leet");
    dict.insert("code");
    Solution s;
    bool b = s.wordBreak("leetcode", dict);
    cout << b << endl;
    b = s.wordBreak("leetode", dict);
    cout << b << endl;
#endif

#if 0
    unordered_set<string> dict;
    dict.insert("a");
    dict.insert("aa");
    dict.insert("aaa");
    dict.insert("aaaa");
    dict.insert("aaaaa");
    dict.insert("aaaaaa");
    dict.insert("aaaaaaa");
    dict.insert("aaaaaaaa");
    dict.insert("aaaaaaaaa");
    dict.insert("aaaaaaaaaa");
    Solution s;
    bool b = s.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", dict);
    cout<<b<<endl;
#endif 
    return 1;
}
