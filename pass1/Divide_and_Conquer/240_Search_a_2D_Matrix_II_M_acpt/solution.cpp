/*
 * 240. Search a 2D Matrix II
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix. 
 * This matrix has the following properties:
 *
 * Integers in each row are sorted in ascending from left to right.
 * Integers in each column are sorted in ascending from top to bottom.
 * For example,
 *
 * Consider the following matrix:
 * [
 * [1,   4,  7, 11, 15],
 * [2,   5,  8, 12, 19],
 * [3,   6,  9, 16, 22],
 * [10, 13, 14, 17, 24],
 * [18, 21, 23, 26, 30]
 * ]
 * Given target = 5, return true.
 * Given target = 20, return false.
 * */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
#if 1
    // 
    // From top right to bottom left:
    // 1. if current position is larger than target, remove entire column.
    // 2. if current position is smaller than targer, remove entire row.
    // Complexity: O(m+n);
    //
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) return 0;
        int i = 0, j = matrix[0].size()-1;
        while (i < matrix.size() && j >= 0) {
            if (matrix[i][j] > target)
                j--;
            else if (matrix[i][j] < target)
                i++;
            else
                return true;
        }
        return false;
    }
#endif 
#if 0
    // naive binary search row by row;
    // Complexity: O(mlong(n))
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; i++) {
            //if (binary_search(matrix[i].begin(), matrix[i].end(), target))
            //    return true;
            int mid = 0, low = 0, high = n-1;
            while (!(low > high)) {
                // mid = (high+low)/2 <<< it is not correct as high+low might overflow hence set mid to a negative value;
                mid = low + (high-low)/2;
                if (matrix[i][mid] < target) {
                    low = mid + 1;
                } else if (matrix[i][mid] > target){
                    high = mid - 1;
                } else 
                    return true;
            }
        }
        return false;
    }
#endif
};

int main () {
    vector<vector<int>> m;
    vector<int> v = {1,4,7,11,15};
    m.push_back(v);
    v = {2,   5,  8, 12, 19};
    m.push_back(v);
    v = {3,   6,  9, 16, 22};
    m.push_back(v);
    v = {10, 13, 14, 17, 24};
    m.push_back(v);
    v = {18, 21, 23, 26, 30};
    m.push_back(v);
    Solution s;
    bool b = s.searchMatrix(m, 20);
    cout<<b<<endl;
    b = s.searchMatrix(m, 5);
    cout<<b<<endl;
    return 1;
}
