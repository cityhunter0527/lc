/*
 * 367. Valid Perfect Square
 * Given a positive integer num, write a function which returns True if num is a perfect square else False.
 *
 * Note: Do not use any built-in library function such as sqrt.
 *
 * Example 1:
 *
 * Input: 16
 * Returns: True
 * Example 2:
 *
 * Input: 14
 * Returns: False
 * */
#include <iostream>
using namespace std;

class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 1) return true;
        int  start = 1, end = num/2;
        long long l;
        long long mid;
        while (start <= end) {
            mid = start + (end-start)/2;
            l = mid*mid;
            if (l < num) {
                start = mid + 1;
            } else if (l > num) {
                end = mid - 1;
            } else
                return true;
        }
        return false;
    }
};

int main() {
    Solution s;
    cout << s.isPerfectSquare(808201) << endl;
    cout << s.isPerfectSquare(14) << endl;
    cout << s.isPerfectSquare(1) << endl;
    cout << s.isPerfectSquare(4) << endl;
    cout << s.isPerfectSquare(12) << endl;
    cout << s.isPerfectSquare(36) << endl;
    cout << s.isPerfectSquare(81) << endl;
    return 1;
}
