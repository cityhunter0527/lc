/*
You're given strings J representing the types of stones that are jewels, and S representing the stones you have.  Each character in S is a type of stone you have.  You want to know how many of the stones you have are also jewels.

The letters in J are guaranteed distinct, and all characters in J and S are letters. Letters are case sensitive, so "a" is considered a different type of stone from "A".

Example 1:

Input: J = "aA", S = "aAAbbbb"
Output: 3
Example 2:

Input: J = "z", S = "ZZ"
Output: 0
Note:

S and J will consist of letters and have length at most 50.
The characters in J are distinct.
*/

#include <string>
#include <iostream>

class Solution {
public:
    int numJewelsInStones(std::string J, std::string S) {
        uint32_t cnt = 0;
        bool t[255] = {false};
        for(size_t i = 0; i < J.size(); i++) {
            t[J[i]] = true;
        }

        for (size_t i = 0; i < S.size(); i++) {
            if (t[S[i]]) cnt++;
        }

        return cnt;
    }
};

int main() {
    std::string J = "aA", S = "aAAbbbb";
    Solution s;
    std::cout << s.numJewelsInStones(J, S) << std::endl;
    J = "z"; S = "ZZ";
    std::cout << s.numJewelsInStones(J, S) << std::endl;
    return 1;
}
