/* 
 * 151. Reverse Words in a String
 *
 * Given an input string, reverse the string word by word.
 *
 * For example,
 * Given s = "the sky is blue",
 * return "blue is sky the".
 *
 * Update (2015-02-12):
 * For C programmers: Try to solve it in-place in O(1) space.
 * */
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        istringstream i(s);
        string ns;
        string tmp;
        while (i >> tmp) {
            tmp.insert(0, " ");
            ns.insert(0, tmp);
            tmp.clear();
        }
        ns.erase(0, 1);
        s = ns;
    }
};

int main() {
    string str = "the sky is blue";
    Solution s;
    s.reverseWords(str);
    cout << str << endl;
    return 1;
}
