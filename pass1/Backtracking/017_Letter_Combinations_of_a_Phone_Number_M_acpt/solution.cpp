/*
 * Given a digit string, return all possible letter combinations that the number could represent.
 *
 * A mapping of digit to letters (just like on the telephone buttons) is given below.
 *
 * 1
 * 2 abc
 * 3 def
 * 4 ghi
 * 5 jkl
 * 6 mno
 * 7 pqrs
 * 8 tuv
 * 9 wxyz
 * 0
 *
 * Input:Digit string "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * Note:
 * Although the above answer is in lexicographical order, your answer could be in any order you want.
 * */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> res;
    vector<string> dict = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

    // Algorithm: DFS Backtracking.
    vector<string> letterCombinations(string digits) {
        if (!digits.size()) return res;
        bt_dfs(digits, "");
        return res;
    }
    void bt_dfs(string s, string w) {
        if (!s.size()) {
            res.push_back(w);
            return;
        }
        int d = s[0] - '0';
        for (auto c : dict[d]) {
            string temp = w+c;
            bt_dfs(s.substr(1, s.size()-1), temp);
        }
    }
};

int main() {
    string digits = "23";
    Solution s;
    vector<string> res = s.letterCombinations(digits);
    for (auto x : res) {
        cout<<x<<", ";
    }
    cout<<endl;
    return 1;
}
