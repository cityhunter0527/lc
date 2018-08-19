/*
 * 48. Rotate Image
 * You are given an n x n 2D matrix representing an image.
 * Rotate the image by 90 degrees (clockwise).
 *
 * Follow up:
 * Could you do this in-place?
 * */

#include <iostream>
#include <vector>
using namespace std;
/*
 *
 * */
class Solution {
public:
    // 
    // In-Place resolution
    // Complexity O(n^2), n is # of rows
    // 1 2 3       7 4 1
    // 4 5 6  ==>  8 5 2
    // 7 8 9       9 6 3
    //
    // n = matrix.size()-1
    // (i, j) -> (j, n-i) -> (n-i, n-j) -> (n-j, i) -> (i, j)
    // (0, 0) -> (0, 2)   -> (2, 2)     -> (2, 0)   -> (0, 0)
    // (0, 1) -> (1, 2)   -> (2, 1)     -> (1, 0)   -> (0, 1)
    //
    // formular: (i,j) --> (j, n-i)
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size()-1;
        for (int i = 0; i <= n>>1; i++) {
            for (int j = i; j < n-i; j++) { 
                // do the switch
                int t = matrix[j][n-i];
                matrix[j][n-i] = matrix[i][j];
                matrix[i][j] = matrix[n-j][i];
                matrix[n-j][i] = matrix[n-i][n-j];
                matrix[n-i][n-j] = t;
            }
        }
    }
};

int main () {
    vector<vector<int>> v = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    Solution s;
    s.rotate(v);
    for(auto x:v) {
        for(auto y:x)
            cout << y << ", ";
        cout << endl;
    }

    return 1;
}
