/*
 * 240. Search a 2D Matrix II
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
 *
 * Integers in each row are sorted in ascending from left to right.
 * Integers in each column are sorted in ascending from top to bottom.
 * For example,
 *
 * Consider the following matrix:
 *
 * [
 *   [1,   4,  7, 11, 15],
 *   [2,   5,  8, 12, 19],
 *   [3,   6,  9, 16, 22],
 *   [10, 13, 14, 17, 24],
 *   [18, 21, 23, 26, 30]
 * ]
 * Given target = 5, return true.
 * Given target = 20, return false.
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) return false;
        int row = matrix.size(), col = matrix[0].size();
        int r = 0, c = col-1;
        while (r < row && c >= 0) {
            if (matrix[r][c] == target) return true;
            else if (matrix[r][c] < target) 
                r++;
            else 
                c--;
        }
        return false;
    }
};

int main() {
    vector<vector<int>> matrix;
    vector<int> v = {1,   4,  7, 11, 15};
    matrix.push_back(v);
    v = {2,   5,  8, 12, 19};
    matrix.push_back(v);
    v = {3,   6,  9, 16, 22};
    matrix.push_back(v);
    v = {10, 13, 14, 17, 24};
    matrix.push_back(v);
    v = {18, 21, 23, 26, 30};
    matrix.push_back(v);

    Solution s;
    cout << s.searchMatrix(matrix, 5) << endl; // true
    cout << s.searchMatrix(matrix, 20) << endl; // false
    cout << s.searchMatrix(matrix, 30) << endl; // true
    cout << s.searchMatrix(matrix, 1) << endl;  // true
    cout << s.searchMatrix(matrix, 0) << endl;  // false
    cout << s.searchMatrix(matrix, 34) << endl; // false
    cout << s.searchMatrix(matrix, 18) << endl; // true
    return 0;
}
