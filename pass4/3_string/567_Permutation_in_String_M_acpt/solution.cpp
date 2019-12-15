// 
// 567. Permutation in String
// Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. 
// In other words, one of the first string's permutations is the substring of the second string.
/*
Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False


Note:

The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].`
*/

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

class Solution {
public:
    void get_occur(std::string& s, size_t start, size_t count, std::vector<int>& o) {

        for (size_t i = start; i < start + count; i++) {
            o[s[i] - 'a']++;
        }
    }

    // sliding window
    bool checkInclusion(std::string s1, std::string s2) {
        auto n = s1.size(), m = s2.size();
        
        if (m < n) { return false; }

        std::vector<int>  perm(26, 0);
        get_occur(s1, 0, n, perm);

        std::vector<int>  flow(26, 0);
        get_occur(s2, 0, n, flow);
        
        int i = n;
        bool success = false;
        do {
            success = std::equal(perm.begin(), perm.end(), flow.begin());
            if (!success && i < m) {
                flow[s2[i] - 'a']++;
                flow[s2[i-n] - 'a']--;
                i++;
            } else {
                break;
            }
        } while (1);

        return success;
    }
};

int main() {
    Solution s;
    std::cout << s.checkInclusion("ab", "eidbaooo") << std::endl;
    std::cout << s.checkInclusion("ab", "eidboaoo") << std::endl;
    return 1;
}
