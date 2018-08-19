/*
 * 483. Smallest Good Base
 *
 * For an integer n, we call k>=2 a good base of n, if all digits of n base k are 1.
 *
 * Now given a string representing n, you should return the smallest good base of n in string format. 
 *
 * Example 1:
 * Input: "13"
 * Output: "3"
 * Explanation: 13 base 3 is 111.
 *
 * Example 2:
 * Input: "4681"
 * Output: "8"
 * Explanation: 4681 base 8 is 11111.
 *
 * Example 3:
 * Input: "1000000000000000000"
 * Output: "999999999999999999"
 * Explanation: 1000000000000000000 base 999999999999999999 is 11.
 *
 * Note:
 * The range of n is [3, 10^18].
 * The string representing n is always valid and will not have leading zeros.
 * */
#include <iostream>
using namespace std;
class Solution {
public:
    string smallestGoodBase(string n) {
        unsigned long long l = stoull(n);           
        unsigned long long b = 1;
        // l == b^0 + b^1 + b^2 + ... + b^(k-1)
        return n;
    }
};

int main() {
    Solution s;
    cout << s.smallestGoodBase("13") << endl;
    cout << s.smallestGoodBase("4681") << endl;
    cout << s.smallestGoodBase("1000000000000000000") << endl;
    return 1;
}
