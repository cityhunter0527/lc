/* 
 * 348. Design Tic-Tac-Toe
 *
 * Design a Tic-tac-toe game that is played between two players on a n x n grid.
 *
 * You may assume the following rules:
 *
 * 1. A move is guaranteed to be valid and is placed on an empty block.
 * 2. Once a winning condition is reached, no more moves is allowed.
 * 3. A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
 *
 * Example:
 * Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.
 *
 * TicTacToe toe = new TicTacToe(3);
 *
 * toe.move(0, 0, 1); -> Returns 0 (no one wins)
 * |X| | |
 * | | | |    // Player 1 makes a move at (0, 0).
 * | | | |
 *
 * toe.move(0, 2, 2); -> Returns 0 (no one wins)
 * |X| |O|
 * | | | |    // Player 2 makes a move at (0, 2).
 * | | | |
 *
 * toe.move(2, 2, 1); -> Returns 0 (no one wins)
 * |X| |O|
 * | | | |    // Player 1 makes a move at (2, 2).
 * | | |X|
 *
 * toe.move(1, 1, 2); -> Returns 0 (no one wins)
 * |X| |O|
 * | |O| |    // Player 2 makes a move at (1, 1).
 * | | |X|
 *
 * toe.move(2, 0, 1); -> Returns 0 (no one wins)
 * |X| |O|
 * | |O| |    // Player 1 makes a move at (2, 0).
 * |X| |X|
 *
 * toe.move(1, 0, 2); -> Returns 0 (no one wins)
 * |X| |O|
 * |O|O| |    // Player 2 makes a move at (1, 0).
 * |X| |X|
 *
 * toe.move(2, 1, 1); -> Returns 1 (player 1 wins)
 * |X| |O|
 * |O|O| |    // Player 1 makes a move at (2, 1).
 * |X|X|X|
 *
 * Follow up:
 * Could you do better than O(n2) per move() operation?
 *
 * */
#include <iostream>
#include <unordered_set>
#include <cassert>
using namespace std;
class TicTacToe {
public:
    /** Initialize your data structure here. */
    TicTacToe(int n) {
        board_len = n;
    }
                
    /** Player {player} makes a move at ({row}, {col}).
     *  @param row The row of the board.
     *  @param col The column of the board.
     *  @param player The player, can be either 1 or 2.
     *  @return The current winning condition, can be either:
     *  0: No one wins.
     *  1: Player 1 wins.
     *  2: Player 2 wins. */
     int move(int row, int col, int player) {
         int key = pi(row, col);
         board[player].insert(key);
         bool win = true;
         int i;
         for (i = 0, win = true; i < board_len; i++) {
            if (board[player].find(pi(row,i)) == board[player].end()) {
                win = false;
                break;
            }
         }
         if (win) return player;
         for (i = 0, win = true; i < board_len; i++) {
            if (board[player].find(pi(i,col)) == board[player].end()) {
                win = false;
                break;
            }
         }
         if (win) return player;

         if (row == col) {
             for (i = 0, win = true; i < board_len; i++) {
                if (board[player].find(pi(i,i)) == board[player].end()) {
                    win = false;
                    break;
                }
             }
         }
         if (win) return player;

         if (row+col == board_len-1) {
            for (i = 0, win = true; i < board_len; i++) {
                if (board[player].find(pi(i, board_len-1-i)) == board[player].end()) {
                    win = false;
                    break;
                }
            }
         }
         if (win) return player;
             
         return 0;
     }
     
     int pi(int x, int y) {
        return ((x+y)*(x+y+1))/2 +y;
     }
     /*
      *  pi(k1, k2) = 1/2(k1 + k2)(k1 + k2 + 1) + k2
      * */
     unordered_set<int> board[4];
     int board_len;
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 * */
int main() {
    TicTacToe *s = new TicTacToe(2);
    int v = s->move(0,0,2);
    v = s->move(0,1,1);
    v = s->move(1,1,2);
    cout << v << endl;
    return 1;
}
