/* 
 * 200. Number of Islands
 * 
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally 
 * or vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 *
 * Input:
 * 11110
 * 11010
 * 11000
 * 00000
 *
 * Output: 1
 * Example 2:
 *
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 *
 * Output: 3
 * */

#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
private:
    void dfs(int i, int j, int row, int col, std::vector<std::vector<char>>& grid) {
        std::vector<std::pair<int, int>> o;
        getNextPos(i, j, row, col, grid, o);
        for (auto& x : o) {
            m_visited[x.first][x.second] = true;
            dfs(x.first, x.second, row, col, grid);
        }
    } 
    void getNextPos(int i, int j, int row, int col, std::vector<std::vector<char>>& grid, std::vector<std::pair<int, int>> &o) {
        if (i-1 >= 0  && grid[i-1][j] == '1' && !m_visited[i-1][j]) o.push_back(std::make_pair(i-1, j));
        if (j+1 < col && grid[i][j+1] == '1' && !m_visited[i][j+1]) o.push_back(std::make_pair(i, j+1));
        if (j-1 >= 0  && grid[i][j-1] == '1' && !m_visited[i][j-1]) o.push_back(std::make_pair(i, j-1));
        if (i+1 < row && grid[i+1][j] == '1' && !m_visited[i+1][j]) o.push_back(std::make_pair(i+1, j));
    }
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.size() == 0) return 0;
        m_visited.resize(grid.size());
        for (size_t i = 0; i < grid.size(); i++) {
            m_visited[i].resize(grid[0].size());
            std::fill(m_visited[i].begin(), m_visited[i].end(), false);
        }

        int row = grid.size(), col = grid[0].size();
        int num_islands = 0;
        for (size_t i = 0; i < row; i++) {
            for (size_t j = 0; j < col; j++) {
                if (grid[i][j] == '1' && !m_visited[i][j]) { 
                    // we've found a new starting point of island;
                    num_islands++;
                    m_visited[i][j] = true;
                    // go dfs to mark all the adjcent points for this island;
                    dfs(i, j, row, col, grid);
                }
            }
        }
        return num_islands;
    }

private:
    std::vector<std::vector<bool>>   m_visited;
};

int main() {
    std::vector<std::vector<char>> grid;
/*
 * 11110
 * 11010
 * 11000
 * 00000
 * */
    std::vector<char>    row;
    row  = {'1', '1', '1', '1', '0'};
    grid.push_back(row);
    row = {'1', '1', '0', '1', '0'};
    grid.push_back(row);
    row = {'1', '1', '0', '0', '0'};
    grid.push_back(row);
    row = {'0', '0', '0', '0', '0'};
    grid.push_back(row);

    Solution s;
    std::cout << s.numIslands(grid) << std::endl;
 /*
 * 11000
 * 11000
 * 00100
 * 00011
 * */
    for (int i = 0; i < grid.size(); i++) 
        grid[i].clear();
    grid.clear();

    row = {'1', '1', '0', '0', '0'};
    grid.push_back(row);
    row = {'1', '1', '0', '0', '0'};
    grid.push_back(row);
    row = {'0', '0', '1', '0', '0'};
    grid.push_back(row);
    row = {'0', '0', '0', '1', '1'};
    grid.push_back(row);
   // Solution s2;
    std::cout << s.numIslands(grid) << std::endl;
    return 0;
}
