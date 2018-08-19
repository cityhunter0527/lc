//
// Problem: Longest Common Subsequence (LCS)
// 
// Subsequence:
// Given a sequence X=<x[1],x[2],...,x[m]>, another sequence Z=<z[1],z[2],...,z[k]> is a subsequence 
// of X if there exists a strickly increasing sequence <i[1],i[2],...i[k]> of indeices of X such that 
// for all j = 1,2,...k, we have X[i[j]] = Z[j];
// 
// Example: 
// Z=<B,C,D,B> is a subsequence of X=<A,B,C,B,D,A,B> which correspoinding index sequence <2,3,5,7>
// 
// Common Subsequence:
// Given two sequences X and Y, we say sequence Z is a common subsequence of X and Y if Z is a subsequence
// of both X and Y.
// 
// We define "Xi" as i-th "prefix" of X, as Xi=<x[1],x[2],...,x[i]> for i = 0,1,...,m; ---------- Define-1
// 
// Optimal substructure of an LCS (unsurprisingly Bottom-Up way):
// Let X=<x[1],x[2],...,x[m]> and Y=<y[1],y[2],...,y[n]> be sequences and let Z=<z[1],z[2],...z[k]> be any LCS 
// of X and Y.
// 1. If x[m] == y[n], then let z[k] be x[m](or y[n]) and Zk-1 is an LCS of Xm-1 and Yn-1; 
// ....(refer to Define-1 for Xm-1 and Yn-1);
// 2. If x[m] != y[n], 
// ....2.a then z[k] != x[m] implies Z is an LCS of Xm-1 and Y. 
// ....2.b then z[k] != y[n] implies Z is an LCS of X and Yn-1.
// ....Need to get the larger one between 2.a and 2.b as either one could contain the LCS.
//
// Let's define c[i][j] to be the length of an LCS of the sequences Xi and Yj. 
// If i=0 or j=0, one of the sequences has length 0, so the LCS has length 0.
// c[i][j] = 0                              if i = 0 or j = 0;
//         = c[i-1][j-1] + 1                if i,j > 0 and x[i] == y[j]
//         = max(c[i][j-1], c[i-1][j])      if i,j > 0 and x]i] != y[j]
//
#include <iostream>
#include <vector>
#include <cassert>
#include <climits>
using namespace std;

class LongestComSubseq {
private:
    void initialize(int n, int m, vector<vector<int>>& c) {
        c.resize(n+1);
        for (auto& x:c) x.resize(m+1, INT_MAX);
        for (int i = 1; i <= n; i++) c[i][0] = 0;
        for (int j = 1; j <= m; j++) c[0][j] = 0;
    }
private: 
    void GetLCS(vector<int>& x, vector<int>& y, vector<vector<int>>& c, vector<int>& lcs) {
        int i = x.size();
        int j = y.size();
        int k = c[i][j];
        lcs.resize(k);
        while (k >= 0) {
            if (x[i-1] == y[j-1]) {
                lcs[--k] = x[i-1];
                i--; j--;
            } else {
                if (c[i-1][j] >= c[i][j-1]) {
                    i--;
                } else 
                    j--;
            }
        }
    }
public:
    int Compute(vector<int>& x, vector<int>& y, vector<int>& lcs) {
        vector<vector<int>> c;
        int n = x.size(), m = y.size();
        initialize(n, m, c);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // 
                // index for x, y should be i-1, j-1, because
                // i represents the i-th "prefix" of x, instead i-th element of x and y;
                // i = 0,1, ..., n;  
                //
                // For example:
                // 0th prefix of x means there is no element in x, 
                // 1st prefix of x means there is only 1 element i x, whic is x[0];
                //
                if (x[i-1] == y[j-1])
                    c[i][j] = c[i-1][j-1]+1;
                else 
                    c[i][j] = max(c[i][j-1], c[i-1][j]);
            }
        }
        GetLCS(x, y, c, lcs);
        return c[n][m];
    }
};

int main() {
    LongestComSubseq lcs;
    vector<int> x = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
    vector<int> y = {'B', 'D', 'C', 'A', 'B', 'A'};  
    vector<int> ss;
    cout << lcs.Compute(x, y, ss) << endl;
    
    for (auto a:ss)
        cout << a << ", ";
    cout << endl;
    
    return 0;
}
