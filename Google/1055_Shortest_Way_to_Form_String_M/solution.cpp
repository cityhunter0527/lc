/*
 * 1055. Shortest Way to Form String
 * From any string, we can form a subsequence of that string by deleting some number of 
 * characters (possibly no deletions).

Given two strings source and target, return the minimum number of subsequences of source 
such that their concatenation equals target. If the task is impossible, return -1.


Example 1:

Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
Example 2:

Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to 
the character "d" in target string.
Example 3:

Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".
 
Constraints:
Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.
 * */

#include <string>
#include <iostream>
#include <vector>

class Solution {
public:
    int shortestWay(std::string source, std::string target) {
        std::vector<std::vector<int>>  s(26);
        int ind = 0;
        for (auto x : source) {
            s[x-'a'].push_back(ind++);
        }
        int ret = 1;
        char x = target[0];
        if (s[x-'a'].size() == 0) return -1;
        int cur = s[x-'a'][0];
        for (int i = 1; i < target.size(); i++) {
            x = target[i];
            if (s[x-'a'].size() == 0) { return -1; }  // a char never appears in source, return -1;

            bool found = false;
            // try to find x's index that is after cur, so that this can be a subsequence;
            for (int j = 0; j < s[x-'a'].size(); j++) {
                if (s[x-'a'][j] > cur)  {
                    // if we get one, update cur to this index and move on to next char in target;
                    cur = s[x-'a'][j];
                    found = true;
                    break;
                } 
            }

            if (found == false) {
                // if not found, update cur to its first appearens in source, increase ret by one;
                cur = s[x-'a'][0];
                ret++;
            }
        }

        return ret;
    }
};

int main() {
    Solution s;
    std::cout << s.shortestWay("abc", "abcbc") << std::endl;
    std::cout << s.shortestWay("abc", "acdbc") << std::endl;
    std::cout << s.shortestWay("xyz", "xzyxz") << std::endl;
    return 1;
}
