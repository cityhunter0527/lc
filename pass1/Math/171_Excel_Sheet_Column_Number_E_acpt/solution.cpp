/*
 * 171. Excel Sheet Column Number
 *
 * Related to question "Excel Sheet Column Title"
 * Given a column title as appear in an Excel sheet, return its corresponding column number.
 *
 * For example:
 *
 *     A -> 1
 *     B -> 2
 *     C -> 3
 *     ...
 *     Z -> 26
 *     AA -> 27
 *     AB -> 28 
 * */
#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    int titleToNumber(string s) {
        if (s.length() == 0) return 0;
        int i = 0;
        int num = s[0]-'A' + 1;
        while (++i < s.length()) num = num*26+s[i]-'A'+1;
        return num;
    }
};

int main () {
    Solution s;
    cout << s.titleToNumber("A")<<endl;
    cout << s.titleToNumber("AB")<<endl;
    cout << s.titleToNumber("CAB")<<endl;
    return 1;
}
