/*
 * 54. Spiral Matrix
 *
 * Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
 *
 * For example,
 * Given the following matrix:
 *
 * [
 * [ 1, 2, 3 ],
 * [ 4, 5, 6 ],
 * [ 7, 8, 9 ]
 * ]
 *
 * You should return [1,2,3,6,9,8,7,4,5].
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.size() == 0) return res;
        int rowLow = -1, rowHigh = matrix.size(), colLow = -1, colHigh = matrix[0].size();
        int direct[4][2] = {0,1, 1,0, 0,-1, -1,0};
        int curDirect = 0;
        int i = 0, j = 0;
        while (j < colHigh && i < rowHigh && j > colLow && i > rowLow) {
            while (j < colHigh && i < rowHigh && j > colLow && i > rowLow) {
                res.push_back(matrix[i][j]);
                i += direct[curDirect][0];
                j += direct[curDirect][1];
            }
            switch (curDirect) {
                case 0: 
                    i++; j--;
                    rowLow++;
                    break;
                case 1:
                    i--; j--;
                    colHigh--;
                    break;
                case 2:
                    i--;j++;
                    rowHigh--;
                    break;
                case 3:
                    i++;j++;
                    colLow++;
                    break;
                default:
                    break;
            }
            curDirect++;
            if (curDirect>=4) curDirect = 0;
        }
        return res; 
    }
};

int main () {
    vector<vector<int>> v = {{1,2,3}};
    Solution s;
    vector<int> out = s.spiralOrder(v);
    for (auto x:out) 
        cout<<x<<", ";
    cout<<endl;
    return 1;
}
