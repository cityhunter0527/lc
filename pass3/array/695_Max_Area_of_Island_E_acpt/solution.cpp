/* 
 * 695. Max Area of Island
 * Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) 
 * connected 4-directionally (horizontal or vertical.) 
 * You may assume all four edges of the grid are surrounded by water.
 *
 * Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
 *
 * Example 1:
 * [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 *  [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *  [0,1,1,0,1,0,0,0,0,0,0,0,0],
 *  [0,1,0,0,1,1,0,0,1,0,1,0,0],
 *  [0,1,0,0,1,1,0,0,1,1,1,0,0],
 *  [0,0,0,0,0,0,0,0,0,0,1,0,0],
 *  [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *  [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 * 
 * Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
 * 
 * Example 2:
 * [[0,0,0,0,0,0,0,0]]
 * Given the above grid, return 0.
 * 
 * Note: The length of each dimension in the given grid does not exceed 50.
 * */

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.size() == 0) return 0;
        row = grid.size(); 
        col = grid[0].size();                    
        int ans = 0;
        for (int i = 0; i < row; i++) 
            for (int j = 0; j < col; j++) 
                if (grid[i][j]) 
                    ans = max(ans, dfs(grid, i, j));
        return ans;
    }
private:
    int row, col;
    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || i >= row || j < 0 || j >= col || !grid[i][j])
            return 0;
        grid[i][j] = 0; // <<< set to 0 to avoid later dfs to visit and count it again.
        return 1 + 
               dfs(grid, i+1, j) +
               dfs(grid, i, j+1) +
               dfs(grid, i-1, j) +
               dfs(grid, i, j-1);
                   
    }
};

int main() {
    /*
 * [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 *  [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *  [0,1,1,0,1,0,0,0,0,0,0,0,0],
 *  [0,1,0,0,1,1,0,0,1,0,1,0,0],
 *  [0,1,0,0,1,1,0,0,1,1,1,0,0],
 *  [0,0,0,0,0,0,0,0,0,0,1,0,0],
 *  [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *  [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 *  */
    vector<vector<int>> grid;
    vector<int> v = {0,0,1,0,0,0,0,1,0,0,0,0,0};
    grid.push_back(v);
    v = {0,0,0,0,0,0,0,1,1,1,0,0,0};
    grid.push_back(v);
    v = {0,1,1,0,1,0,0,0,0,0,0,0,0};
    grid.push_back(v);
    v = {0,1,0,0,1,1,0,0,1,0,1,0,0};
    grid.push_back(v);
    v = {0,1,0,0,1,1,0,0,1,1,1,0,0};
    grid.push_back(v);
    v = {0,0,0,0,0,0,0,0,0,0,1,0,0};
    grid.push_back(v);
    v = {0,0,0,0,0,0,0,1,1,1,0,0,0};
    grid.push_back(v);
    v = {0,0,0,0,0,0,0,1,1,0,0,0,0};
    grid.push_back(v);
    
    Solution s;
    cout << s.maxAreaOfIsland(grid) << endl;

    grid.clear();
    v = {0,0,0,0,0,0};
    grid.push_back(v);
    cout << s.maxAreaOfIsland(grid) << endl;
    return 1;
}
