/* 
 * 374. Guess Number Higher or Lower
 * We are playing the Guess Game. The game is as follows:
 * I pick a number from 1 to n. You have to guess which number I picked.
 * Every time you guess wrong, I'll tell you whether the number is higher or lower.
 *
 * You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):
 *
 * -1 : My number is lower
 *  1 : My number is higher
 *  0 : Congrats! You got it!
 * Example:
 * n = 10, I pick 6.
 * Return 6.
 * */

#include <iostream>
using namespace std;
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int number = 6;
int guess(int num) {
    if (num < number)
        return 1;
    else if (num > number)
        return -1;
    else
        return 0;
}

class Solution {
public:
    int guessNumber(int n) {
        int ret, start = 1, end = n, mid;       
        while (start <= end) {
            mid = start +(end-start)/2;
            ret = guess(mid);
            if (ret > 0) {
                start = mid + 1;
            } else if (ret < 0) {
                end = mid - 1;   
            } else
                return mid;
        }
        return mid;
    }
};

int main() {
    Solution s;
    cout << s.guessNumber(200) << endl;
    number = 234;
    cout << s.guessNumber(1000) << endl;
    number = 20000;
    cout << s.guessNumber(20000) << endl;
    number = 1;
    cout << s.guessNumber(1) << endl;
    return 1;
}
