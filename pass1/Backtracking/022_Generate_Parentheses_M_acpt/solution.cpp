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
    void getCandidates(string& s, int k, int n, char c[], int& nCandidates) {
        if (k > (n<<1)) {nCandidates = 0; return;}
        // only return good candidates
        if (left == right) {
            nCandidates = 1;
            c[0] = '(';
        } else if (left > right && left <n) {
            nCandidates = 2;
            c[0] = '(';
            c[1] = ')';
        } else if (left > right && left ==n) {
            nCandidates = 1;
            c[0] = ')';
        }
        return;
    }

    void btdfs(string& s, int k, int n) {
        char c[2]; // two candidates, each pos can be '(' or ')'
        int nCandidates;

        if (k == (n<<1)) {
            res.push_back(s);
        } else {
            k++;
            getCandidates(s, k, n, c, nCandidates);
            for (int i = 0; i < nCandidates; i++) {
                if (c[i] == '(') left++;
                if (c[i] == ')') right++;
                s.push_back(c[i]);
                btdfs(s, k, n);
                s.pop_back();
                if (c[i] == '(') left--;
                if (c[i] == ')') right--;
            }
        }
    }

};

int main() {
    vector<string> res;
    Solution s;
    res = s.generateParenthesis(1);

    for (auto x : res) {
        cout<<x<<endl;
    }
    return 1;
}
