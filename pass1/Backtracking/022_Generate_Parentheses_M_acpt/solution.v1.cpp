/* 
 * 22. Generate Parentheses 
 *
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 * For example, given n = 3, a solution set is:
 *
 * [
 * "((()))",
 * "(()())",
 * "(())()",
 * "()(())",
 * "()()()"
 * ]
 * */
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

class Solution {
public:
    vector<string> res;
    int left = 0;
    int right = 0;
    vector<string> generateParenthesis(int n) {
        string s; // one solution
        btdfs(s, 0, n);
        return res;
    }

    bool isSolution(string& s, int k, int n) {
        if (s.size() != n*2) return false;
        int i = 0;
        for (auto c:s) {
            if (c == '(')
                i++;
            else 
                i--;
            if (i < 0)
                return false;
        } 
        return i == 0;
    }

    void getCandidates(string& s, int k, int n, char c[], int& nCandidates) {
        if (k > (n*2)) {nCandidates = 0; return;}
    
        // always return two candidates
        // TODO: how to speed up and only return good/valid candidates?
        nCandidates = 2;
        c[0] = '(';
        c[1] = ')';
        return;
    }

    void btdfs(string& s, int k, int n) {
        char c[2]; // two candidates, each pos can be '(' or ')'
        int nCandidates;

        if (isSolution(s, k, n)) {
            res.push_back(s);
        } else {
            k++;
            getCandidates(s, k, n, c, nCandidates);
            for (int i = 0; i < nCandidates; i++) {
                s.push_back(c[i]);
                btdfs(s, k, n);
                s.pop_back();
            }
        }
    }

};

int main() {
    vector<string> res;
    Solution s;
    res = s.generateParenthesis(0);

    for (auto x : res) {
        cout<<x<<endl;
    }
    return 1;
}
