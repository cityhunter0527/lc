/*
 * 3. Longest Substring Without Repeating Characters
 * Given a string, find the length of the longest substring without repeating characters.
 *
 * Examples:
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 * Given "bbbbb", the answer is "b", with the length of 1.
 * Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 * */

#include <iostream>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int cnt = 0, maxCnt = 0, n = s.size();
        int radix[255]; // index: s[i]; val: i
        fill_n(radix, 255, -1);
        int i, i0;
        for (i = 0, i0 = 0; i < n; i++) {
            if (!(radix[s[i]] < i0)) {
                maxCnt = max(maxCnt, i - i0);
                i0 = radix[s[i]]+1;
            }
            radix[s[i]] = i;
        }
        maxCnt = max(maxCnt, i - i0); // for last element;
        return maxCnt;
    }
};

int main() {
    Solution s;
    int n = s.lengthOfLongestSubstring("qwnfenpglqdq");
    cout << n << endl;
    n = s.lengthOfLongestSubstring("abcabcbb");
    cout << n << endl;
    n = s.lengthOfLongestSubstring("bbbbb");
    cout << n << endl;
    n = s.lengthOfLongestSubstring("pwwkew");
    cout << n << endl;
    n = s.lengthOfLongestSubstring("c");
    cout << n << endl;
    n = s.lengthOfLongestSubstring("dvdf");
    cout << n << endl;
    n = s.lengthOfLongestSubstring("cdvdf");
    cout << n << endl;
    return 1;
}
