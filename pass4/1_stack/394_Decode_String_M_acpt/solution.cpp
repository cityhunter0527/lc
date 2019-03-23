/*
 * 394. Decode String
 * Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets 
is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those 
repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
 * */

#include <iostream>
#include <stack>

class Solution {
private:
    // 
    // get the string from stack based on 'f', and append to res;
    // f: true
    //  get all the string from stack
    // f: false
    //  get string until we hit '['
    //
    void get(std::stack<char>& stk, std::string& res, bool f = false) {
        std::string tmp;
        while ((f && stk.top() != '[') || (!f && !stk.empty())) {
            tmp.insert(0,1,stk.top());   
            stk.pop();
        }
        res.append(tmp);
    }
public:
    std::string decodeString(std::string s) {
        std::string res;
        std::stack<char> stk;
        uint32_t k = 0; // keep track of [] pair to decide whether there is any string that doesn't start with num and [];
        for (auto c : s) {
            if (c == ']') {
                std::string tmp;
                k--;
                get(stk, tmp, true); // get tmp until we hit '['
                stk.pop(); // pop '['
                uint32_t num = 0, d = 1;
                while (!stk.empty() && stk.top() >= '0' && stk.top() <= '9') {
                    num += (stk.top()-'0') * d;
                    d *= 10;
                    stk.pop();
                }
                // decode the string;
                std::string tt = tmp;
                while (num-- > 1) tmp.append(tt);
                
                if (k == 0) {
                    get(stk, res); // get the string with no num and [] pair and save it to res before we can append tmp;
                    res.append(tmp);
                } else {
                    for (auto t : tmp) stk.push(t);
                }
            } else {
                stk.push(c);
                if (c == '[') k++;
            }
        }
        // if there is string left with no num and [], need to save it to res;
        get(stk, res);
        return res;
    }
};

int main () {
    Solution s;
    std::cout << s.decodeString("3[a]2[bc]") << std::endl;
#if 1
    std::cout << s.decodeString("2[abc]xyc3[z]") << std::endl;
    std::cout << s.decodeString("100[leetcode]") << std::endl;
    std::cout << s.decodeString("3[a2[c]]") << std::endl;
    std::cout << s.decodeString("2[abc]3[cd]ef") << std::endl;
    std::cout << s.decodeString("xy2[abc]3[cd]ef") << std::endl;
#endif
    return 1;
}
