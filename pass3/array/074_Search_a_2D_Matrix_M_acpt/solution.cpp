/*
 * 74. Search a 2D Matrix
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
 *
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of the previous row.
 * For example,
 *
 * Consider the following matrix:
 *
 * [
 * [1,   3,  5,  7],
 * [10, 11, 16, 20],
 * [23, 30, 34, 50]
 * ]
 * Given target = 3, return true.
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // mtrix: n * m
    // matrix[x][y] ==> a[x*m+y]
    // a[x] ==> matrix[x/m][x%m];
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) return false;
        int row = matrix.size(), col = matrix[0].size();
        int start = 0, end = row*col-1;
        while (start <= end) {
            int mid = start + ((end-start) >> 1);
            if (matrix[mid/col][mid%col] < target) {
                start = mid + 1;
            } else if (matrix[mid/col][mid%col] > target) {
                end = mid - 1;
            } else 
                return true;
        }
        return false;
    }
};

int main() {
    vector<vector<int>> matrix;
    vector<int> v = {1,3,5,7};
    matrix.push_back(v);
    v = {10, 11, 16, 20};
    matrix.push_back(v);
    v = {23, 30, 34, 50};
    matrix.push_back(v);
    Solution s;
    cout << s.searchMatrix(matrix, 3) << endl;
    return 0;
}
