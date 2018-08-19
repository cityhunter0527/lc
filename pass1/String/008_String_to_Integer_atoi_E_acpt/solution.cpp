/*
 * 8. String to Integer (atoi)
 * 
 * Implement atoi to convert a string to an integer.
 *
 * Hint: Carefully consider all possible input cases. 
 * If you want a challenge, please do not see below and ask yourself what are the possible input cases.
 *
 * Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). 
 * You are responsible to gather all the input requirements up front.
 *
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. 
 * If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.
 *
 * spoilers alert... click to show requirements for atoi.
 *
 * Requirements for atoi:
 * The function first discards as many whitespace characters as necessary until the first non-whitespace 
 * character is found. Then, starting from this character, takes an optional initial plus or minus sign 
 * followed by as many numerical digits as possible, and interprets them as a numerical value.
 *
 * The string can contain additional characters after those that form the integral number, which are 
 * ignored and have no effect on the behavior of this function.
 *
 * If the first sequence of non-whitespace characters in str is not a valid integral number, 
 * or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.
 *
 * If no valid conversion could be performed, a zero value is returned. 
 * If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 * */

#include <iostream>
#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int i = 0, sign = 1, n = str.size();
        long sum = 0;
        // remove leading white spaces.
        while (i < n && str[i] == ' ') i++; 
        // deal with sign
        if (str[i] == '-') { sign = -1; i++;}  
        else if (str[i] == '+') { sign = 1; i++;}

        while (i < n && str[i] >= '0' && str[i] <= '9') {
            sum *= 10;
            sum += str[i]-'0';
            if (sum > INT_MAX)
                return sign == 1?INT_MAX:INT_MIN;
            i++;
        }
        return sum * sign;
    }
};

int main() {
    Solution s;
    cout << s.myAtoi("    -2147483647") << endl;;
    return 1;
}
