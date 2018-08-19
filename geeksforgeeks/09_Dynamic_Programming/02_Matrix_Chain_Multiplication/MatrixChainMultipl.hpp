//
// Problem Description: Matrix-Chain Multiplication
// Given a chain <A1*A2*A3*...*An> of n matrices, where for i = 1,2,...,n, matrix A[i] has dimension
// p[i-1]*p[i]. Fully parenthesize the product A1A2...An in a way that minimizes the number of 
// scalar multiplications.
//
// Examaple: Say we have a chain <A1*A2*A3> of three matrices and dimensions of matrices are 
// A1: 10*100, A2: 100*5 and A3: 5*50;
// 
// Solution-1: (A1*A2)*A3 will need to perform 10*100*5 for A1*A2 to compute the 10*5 matrix 
// product A1A2, plus another 10*5*50 = 2500 to myltiply A3, for a total 7500 scalar multiplications.
// Solution-2: A1*(A2*A3) will need to perform 100*5*50 + 10*100*50 = 75000 scalar multiplications 
// which is 10 times bigger than Solution-1;
// 
// Solution:
// Let m[i][j] be the minimum number of scalar multiplications needed to compute the matrix cost of 
// A[i]A[i+1]...A[j],  where 1 <= i <= j <= n;
// We can define m[i][j] recursively as below:
// m[i][j] = 0                                                      if i = j;
//         =   min  { m[i][k] + m[k+1][j] + p[i-1]p[k]p[j] }        if i < j;   ---------------(15.7)
//           i<=k<j
// Prove:
// There must a value k that gives m[i][j] the optimal parenthesize. Because if there is a less costly
// way to parenthesize A[i]A[i+1]...A[k], then we could substitute k with that value that with the less
// cost. We do it bottom-up so that we garunteen m[1][n] always get computed based on optimal parenthesize.
//
// To get the optimial solution (not just the minimal cost), we need to define s[i][j] which equals 
// a value k such that m[i][j] = m[i][k]+m[k+1][j]+p[i-1]p[k]p[j] gives the minimal cost;
// 
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
using namespace std;

class MatrixChainMultipl {
private:
    void initialize(int n, vector<vector<int>>& m, vector<vector<int>>& s) {
        m.resize(n+1);
        for (auto& x:m) x.resize(n+1, INT_MAX);
        s.resize(n+1);
        for (auto& x:s) x.resize(n+1);
    }
public:
    // Given A1: 10*100; A2: 100*5; A3: 5*50;
    // We have p: {10, 100, 5, 50}
    //           Depend                                                      unique
    // m[1][2]:  m[1][1] m[2][2]                                             -
    // m[1][3]:  m[1][1] m[2][3] m[1][2] m[3][3]                             m[2][3] 
    // m[1][4]:  m[1][1] m[2][4] m[1][2] m[3][4] m[1][3] m[4][4]             m[2][4] m[3][4] 
    // m[1][5]:  m[2][5] m[3][5] m[4][5] m[5][5]                             m[2][5] m[3][5] m[4][5]
    // ...
    // m[1][n]:
    //
    int MatrixChainOrder(vector<int>& p, vector<vector<int>>& m, vector<vector<int>>& s) {
        int n = p.size() - 1; // n Matrices
        initialize(n, m, s);
        for (int i = 1; i <= n; i++) 
            m[i][i] = 0;

        // 
        // Compute Sequence:
        // m[1][2]
        // m[2][3] m[1][3]
        // m[3][4] m[2][4] m[1][4]
        // m[4][5] m[3][5] m[2][5] m[1][5]
        // ...
        // m[n-1][n] m[n-1][n] ........... m[2][n] m[1][n]
        //
        for (int j = 2; j <= n; j++) {
            for (int i = j-1; i > 0; i--) {
                for (int k = i; k < j; k++) {
                    assert(m[i][k] != INT_MAX);
                    assert(m[k+1][j] != INT_MAX);
                    int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                    if (m[i][j] > q) {
                        m[i][j] = q;
                        s[i][j] = k;   
                    }
                }
            }
        }
        return m[1][n];
    }

    void PrintOptimalParents(vector<vector<int>>& s, int i, int j) {
        if (i == j) {
            cout << "A" << i;
        } else {
            cout << "(";
            PrintOptimalParents(s, i, s[i][j]);
            PrintOptimalParents(s, s[i][j]+1, j);
            cout << ")";
        }
    }
};


