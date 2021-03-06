/*
 * 441. Arranging Coins
 *
 * You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.
 *
 * Given n, find the total number of full staircase rows that can be formed.
 *
 * n is a non-negative integer and fits within the range of a 32-bit signed integer.
 *
 * Example 1:
 *
 * n = 5
 *
 * The coins can form the following rows:
 * ¤
 * ¤ ¤
 * ¤ ¤
 *
 * Because the 3rd row is incomplete, we return 2.
 * Example 2:
 *
 * n = 8
 *
 * The coins can form the following rows:
 * ¤
 * ¤ ¤
 * ¤ ¤ ¤
 * ¤ ¤
 *
 * Because the 4th row is incomplete, we return 3.
 * */

#include <iostream>
using namespace std;
class Solution {
public:
    // Find maximum x that satisfy:
    // 1 + 2 + 3 + 4 + ... + x <= n  
    // Simplified to:
    //      x(x+1) <= 2*n
    int arrangeCoins(int n) {
        int start = 0, end = n/2+1, mid = 0;
        while (start <= end) {
            mid = start + (end - start)/2;
            if ((0.5*mid*mid + 0.5*mid) <= n) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return start - 1;
    }
};

int main() {
    Solution s;
    cout << s.arrangeCoins(0) << endl;
    cout << s.arrangeCoins(1) << endl;
    cout << s.arrangeCoins(5) << endl;
    cout << s.arrangeCoins(8) << endl;
    cout << s.arrangeCoins(2147483647) << endl;
    return 1;
}
