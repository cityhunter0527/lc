/*
 * 9 Palindrome Number
 * Determine whether an integer is a palindrome. Do this without extra space.
 *
 * Some hints:
 * Could negative integers be palindromes? (ie, -1)
 *
 * If you are thinking of converting the integer to string, note the restriction of using extra space.
 *
 * You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", 
 * you know that the reversed integer might overflow. How would you handle such case?
 *
 * There is a more generic way of solving this problem.
 * */
#include <iostream>
#include <climits>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        int result = 0;
        while (x) {
            if (result > INT_MAX/10 || result < INT_MIN/10)
                return 0;
            result *= 10;
            result += x%10;
            x /= 10;
        }
        return result;
    }

    bool isPalindrome(int x) {
        if (x < 0) return false;
        return reverse(x) == x;                          
    }
};

int main() {
    Solution s;
    cout << s.isPalindrome(123321) << endl;
    cout << s.isPalindrome(-123321) << endl;
    cout << s.isPalindrome(5) << endl;
    cout << s.isPalindrome(54) << endl;
    cout << s.isPalindrome(-2147447412) << endl;
    cout << INT_MAX << endl;
    cout << INT_MIN << endl;
}
