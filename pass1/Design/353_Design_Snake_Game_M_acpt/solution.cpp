/*
 * 353. Design Snake Game
 *
 * Design a Snake game that is played on a device with screen size = width x height. 
 * Play the game online if you are not familiar with the game.
 *
 * The snake is initially positioned at the top left corner (0,0) with length = 1 unit.
 *
 * You are given a list of food's positions in row-column order. When a snake eats the food, its length and the game's score both increase by 1.
 *
 * Each food appears one by one on the screen. For example, the second food will not appear until the first food was eaten by the snake.
 *
 * When a food does appear on the screen, it is guaranteed that it will not appear on a block occupied by the snake.
 *
 * Example:
 * Given width = 3, height = 2, and food = [[1,2],[0,1]].
 *
 * Snake snake = new Snake(width, height, food);
 *
 * Initially the snake appears at position (0,0) and the food at (1,2).
 *
 * |S| | |
 * | | |F|
 *
 * snake.move("R"); -> Returns 0
 *
 * | |S| |
 * | | |F|
 *
 * snake.move("D"); -> Returns 0
 *
 * | | | |
 * | |S|F|
 *
 * snake.move("R"); -> Returns 1 (Snake eats the first food and right after that, the second food appears at (0,1) )
 *
 * | |F| |
 * | |S|S|
 *
 * snake.move("U"); -> Returns 1
 *
 * | |F|S|
 * | | |S|
 *
 * snake.move("L"); -> Returns 2 (Snake eats the second food)
 *
 * | |S|S|
 * | | |S|
 *
 * snake.move("U"); -> Returns -1 (Game over because snake collides with border)
 * */

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class SnakeGame {
private:
    deque<pair<int, int>> snake;
    int w, h;
    vector<pair<int,int>> mfood;
    int curFood;
public:
    /** Initialize your data structure here.
     *  @param width - screen width
     *  @param height - screen height 
     *  @param food - A list of food positions
     *  E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food) {
        snake.push_back(make_pair(0,0));
        w = width;
        h = height;
        curFood = 0;
        for (int i = 0; i < food.size(); i++) {
            mfood.push_back(food[i]);   
        }
    }

    /** 
     * Complexity: O(n) n is snake length;
     * Moves the snake.
     *  @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
     *  @return The game's score after the move. Return -1 if game over. 
     *  Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        auto x = snake.front();       
        pair<int, int> newX;
        if (direction[0] == 'D') {
            newX.first = x.first+1;
            newX.second = x.second;
        } else if (direction[0] == 'U') {
            newX.first = x.first-1;
            newX.second = x.second;
        } else if (direction[0] == 'R') {
            newX.first = x.first;
            newX.second = x.second+1;
        } else if (direction[0] == 'L') {
            newX.first = x.first;
            newX.second = x.second-1;
        }
        // if the new position is out of screen, return -1
        if (newX.first < 0 || newX.first >= h || newX.second < 0 || newX.second >= w ) {
            return -1;
        }
        
        if ((curFood < mfood.size()) && (newX == mfood[curFood])) {
            // if the new position is the cur food position, eat it.
            curFood++;       
            snake.push_front(newX);
        } else {
            // else snake move to newX
            snake.pop_back();
            snake.push_front(newX);
        }
        auto y = snake.begin();
        // return -1 if the newX crash into existing snake body;
        for (y = y+1; y != snake.end(); y++) {
            if (newX == *y)
                return -1;
        }

        return snake.size()-1;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 * */
int main () {
    vector<pair<int, int>> food;
    food.push_back(make_pair(1,2));
    food.push_back(make_pair(0,1));
    SnakeGame *sg = new SnakeGame(3, 2, food);
    int v = sg->move("R");
    cout << v << endl;
    v =  sg->move("D");
    cout << v << endl;
    v =  sg->move("R");
    cout << v << endl;
    v =  sg->move("U");
    cout << v << endl;
    v =  sg->move("L");
    cout << v << endl;
    v =  sg->move("U");
    cout << v << endl;
    return 1;
}
