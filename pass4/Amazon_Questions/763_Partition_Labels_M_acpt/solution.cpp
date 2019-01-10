/*
763. Partition Labels
A string S of lowercase letters is given. We want to partition this string into as many parts as possible so that each letter 
appears in at most one part, and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.
*/
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> partitionLabels(std::string S) {
        std::vector<int> res;
        std::vector<int> t(255, -1); 
        uint32_t i = 0, j = 0, k = 0;
        while (i < S.size()) {
            while (i < S.size()) {
                if ((t[S[i]] != -1) && t[S[i]] <= k) 
                    k = i;
                else 
                    t[S[i]] = i;
                i++;
            }
            k++;
            res.push_back(k - j);
            i = k; 
            j = k;
            std::fill(t.begin(), t.end(), -1);
        }
        return res;
    }

    void dump(std::vector<int>& v) {
        for (auto& x : v) {
            std::cout << x << ", ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::string S = "ababcbacadefegdehijhklij";
    Solution s;
    std::vector<int> res = s.partitionLabels(S);
    std::cout << S << std::endl;
    s.dump(res);

    res.clear();
    S = "aaaa";
    res = s.partitionLabels(S);
    std::cout << S << std::endl;
    s.dump(res);

    return 1;
}
