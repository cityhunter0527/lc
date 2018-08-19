/*
 * 91. Decode Ways
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing digits, determine the total number of ways to decode it.
 *
 * For example,
 * Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
 *
 * The number of ways decoding "12" is 2.
 * */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


// 1,2,1
// 1,21,
// 12,1
// 
// 1,2,1,2
// 12,1,2
// 12,12
// 1,21,2
// 1,2,12
//
// f[i] = f[i-1] or
// f[i] += f[i-2]
class Solution {
public:
    int numDecodings(string s) {
        if (s.length() == 0) 
            return 0;
        int len = s.length();
        int f[len+1];
        fill(f, f+len+1, 0);
        f[0] = 1;
        f[1] = ((s[0] == '0')? 0 : 1);
        // f[i] stands for all the number of combination with s from index 0 to i-1;
        for (int i = 2; i <= len; i++) {
            // if s[i-1] is not '0', firstly get all the numbers from f[i-1] since we can simply put s[i-1] as single number after each combination of f[i-2];
            if (s[i-1] != '0') f[i] = f[i-1];
            // if s[i-1] is '0':
            //     1. if s[i-2] is not '0' and s[i-2]s[i-1] is good decode, set f[i] as f[i-2];
            //     2. if s[i-2] is '0' or s[i-2]s[i-1] is not a good decode, f[i] stays 0;
            //        
            //        Note, f[i] being '0' will be passed to other indexes moving forward, and the final value will also be 0;
            // if s[i-1] is not '0', and s[i-1]s[i-2] is good decode, 
            // then s[i-1]s[i-2] can be treated as one digit, 
            // all we needs to do is to plus f[i-2] to f[i];
            if (s[i-2] != '0' && ((s[i-2]-'0')*10+s[i-1]-'0')<=26) f[i] += f[i-2];
        }
        return f[len];
    }
};
int main () {
    string s = "1212";
    Solution ms;
    int v = ms.numDecodings(s);
    cout<<v<<endl;
    return 1;
}
