/*
 * 73. Set Matrix Zeroes
 *
 * Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.size()==0) return;
        int m = matrix.size(), n = matrix[0].size();
        vector<pair<int,int>> zero;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0)    
                    zero.push_back(make_pair(i,j));
            }
        }
        for (auto z : zero) {
            for (int i = 0; i < n; i++)
                matrix[z.first][i] = 0;
            for (int i = 0; i < m; i++)
                matrix[i][z.second] = 0;
        }
    }
};

int main () {
    // 1 1 1 1
    // 1 0 1 1
    // 1 1 1 1
    // 1 1 1 0
    vector<int> v = {1,1,1,1};
    vector<vector<int>> m;
    m.push_back(v);
    v = {1,0,1,1};
    m.push_back(v);
    v = {1,1,1,1};
    m.push_back(v);
    v = {1,1,1,0};
    m.push_back(v);
    Solution s;
    s.setZeroes(m);

    for (auto x:m) {
        for (auto y:x) {
            cout<<y<<", ";
        }
        cout<<endl;
    }

    return 1;
}

