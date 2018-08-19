/*
 * 79. Word Search
 *
 * Given a 2D board and a word, find if the word exists in the grid.
 *
 * The word can be constructed from letters of sequentially adjacent cell, 
 * where "adjacent" cells are those horizontally or vertically neighboring. 
 * The same letter cell may not be used more than once.
 *
 * For example,
 * Given board =
 *
 * [
 * ['A','B','C','E'],
 * ['S','F','C','S'],
 * ['A','D','E','E']
 * ]
 * word = "ABCCED", -> returns true,
 * word = "SEE", -> returns true,
 * word = "ABCB", -> returns false.
 * */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;
class Solution {
public:
    vector<vector<bool>> visited;
    bool res;
    int n;
    int m;
    int dx[4] = {0,0,1,-1};
    int dy[4] = {1,-1,0,0};
    bool exist(vector<vector<char>>& board, string word) {
        // no need to store solution as we only return true, false, not entire path.
        n = board.size();
        m = board[0].size();
        res = false;
        visited.resize(n, vector<bool>(m, false));

        if (n*m < word.size()) return false;
        if (!word.size()) return true;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // start backtracking of position:0 in word
                bt(i, j, 0, board, word);
                if (res)
                    return res;
            }
        }
        return res;
    }

    void bt(int i, int j, int pos, vector<vector<char>>& board, string& word) {
        if (res || board[i][j] != word[pos]) return;
        if (pos+1 == word.size()) { res = true; return; }

        // mark this candidate as visited.
        visited[i][j] = true;
        // generate candidates
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (ni < 0 || nj < 0 || ni >=n || nj >= m || visited[ni][nj]) {
                // not a valid pos, go to next candidate;
                continue;
            }
            bt(ni, nj, pos+1, board, word);
        }
        // we are done with this candidate, and need to back track to previous pos,
        // so mark it as un-visited.
        visited[i][j] = false;
    }
};

int main() {
    vector<vector<char>> board(1, vector<char>(1));
    board[0] = {'A'};

    string w = "A";
    Solution s;
    bool b = s.exist(board, w);
    assert(b);
    
    return 1;
}
