//
// Given two strings X and Y, find the length of the longest common substring.
//
// Examples :
//
// Input : X = "GeeksforGeeks", y = "GeeksQuiz"
// Output : 5
// The longest common substring is "Geeks" and is of
// length 5.
//
// Input : X = "abcdxyz", y = "xyzabcd"
// Output : 4
// The longest common substring is "abcd" and is of
// length 4.
//
// Input : X = "zxabcdezy", y = "yzabcdezx"
// Output : 6
// The longest common substring is "abcdez" and is of
// length 6.
//

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Longest common suffix
// c[i][j] = 0                    if i = 0 or j = 0;
//         = 0                    if x[i] != y[j]
//         = c[i-1][j-1] + 1;     if x[i] == y[j]
//
// Longest common substr
// d = max(c[i][j])             for 1 <= i <= m; 1 <= j <= n;
//
class LongestCommSubstr {
private:
    void init(int m, int n, vector<vector<int>>& c) {
        c.resize(m+1);
        for(auto& x:c) x.resize(n+1, 0);   
    }
public:
    int Compute(string x, string y) {
        int m = x.size(), n = y.size();
        vector<vector<int>> c;
        init(m, n, c);
        int d = INT_MIN;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (x[i-1] == y[j-1]) {
                    c[i][j] = c[i-1][j-1] + 1;
                    if (d < c[i][j]) d = c[i][j];
                }
            }
        }
        return d;
    }
};

int main() {
    LongestCommSubstr lcs;
    cout << lcs.Compute("GeeksforGeeks", "GeeksQuiz") << endl;
    cout << lcs.Compute("abcdxyz", "xyzabcd") << endl;
    cout << lcs.Compute("zxabcdezy", "yzabcdezx") << endl;
    return 0;
}
