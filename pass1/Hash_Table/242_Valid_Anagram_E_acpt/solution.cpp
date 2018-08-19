/*
 * 242. Valid Anagram
 * Given two strings s and t, write a function to determine if t is an anagram of s.
 *
 * For example,
 * s = "anagram", t = "nagaram", return true.
 * s = "rat", t = "car", return false.
 *
 * Note:
 * You may assume the string contains only lowercase alphabets.
 *
 * Follow up:
 * What if the inputs contain unicode characters? How would you adapt your solution to such case?
 * */
#include <string>
#include <iostream>
using namespace std;
class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s==t;
    }
#if 0
    // Good one, but can't handle unicode
    bool isAnagram(string s, string t) {
        if (s.size()!=t.size()) return false;
        int map[26] = {0};                   
        for (int i = 0; i < s.size(); i++) {
            map[s[i]-'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            if (map[t[i]-'a'] == 0) return false;
            map[t[i]-'a']--;
        }
        return true;
    }
#endif
};

int main(){
    Solution s;
    cout << s.isAnagram("anagram", "nagaram") << endl;
    cout << s.isAnagram("rat", "car") << endl;
    return 1;
}
