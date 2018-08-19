/*
 * 387. First Unique Character in a String
 *
 * Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.
 *
 * Examples:
 *
 * s = "leetcode"
 * return 0.
 *
 * s = "loveleetcode",
 * return 2.
 * Note: You may assume the string contain only lowercase letters.
 * */

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        int map[255];
        fill_n(map, 255, -1);
        for (int i = 0; i < s.size(); i++) {
            map[s[i]]++;
        }
        for (int i = 0; i < s.size(); i++) {
            if (map[s[i]] == 0)
                return i;
        }
        return -1;
    }
};

int main() {
    Solution s;
    int v = s.firstUniqChar("leetcode");
    cout << v<< endl;
    v = s.firstUniqChar("loveleetcode");
    cout << v<< endl;
    return 1;
}
