/*
 *  28. Implement strStr()
 *
 *  Implement strStr().
 *
 *  Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
 * */

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int l1 = haystack.length(), l2 = needle.length();
        if (l1 < l2) return -1;
        int s = 0;
        while (s + l2 <= l1) {
            if (haystack.compare(s, l2, needle) == 0) return s;
            s++;
        }
        return -1;
    }
};

int main() {
    Solution s;
    cout << s.strStr("hello kitty", "kitty") << endl;
    cout << s.strStr("hello kitty", "tty") << endl;
    cout << s.strStr("hello kitty", "llo") << endl;
    return 1;
}

