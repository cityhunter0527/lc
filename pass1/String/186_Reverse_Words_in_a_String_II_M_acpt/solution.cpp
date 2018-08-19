/*
 * 186. Reverse Words in a String II
 *
 * Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.
 *
 * The input string does not contain leading or trailing spaces and the words are always separated by a single space.
 *
 * For example,
 * Given s = "the sky is blue",
 * return "blue is sky the".
 *
 * Could you do it in-place without allocating extra space?
 *
 * Related problem: Rotate Array
 * */
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        int i = s.length() - 1;
        
        while (s[i] != ' ' && (i>=0)) i--;
        while (i-- > 0) {
            // there is no whitespace between [wordStart, wordEnd]
            int wordEnd = i;
            while (s[i] != ' ' && (i >= 0)) i--; // i wil be -1 reaching first character of the string
            int wordStart = i+1; // wordStart will be 0 after we hit first character of the string.
            s.push_back(' ');
            s.insert(s.end(), s.begin()+wordStart, s.begin()+wordEnd+1);
            s.erase(wordStart, wordEnd-wordStart+2);
        }
    }
};

int main () {
    string s = "the sky is blue";
    Solution mysolution;
    mysolution.reverseWords(s);
    cout << "|"<<s << "|"<<endl;
    s = "the sky";
    mysolution.reverseWords(s);
    cout << "|"<<s << "|"<<endl;
    s = "";
    mysolution.reverseWords(s);
    cout << "|"<<s << "|"<<endl;
    return 1;
}
