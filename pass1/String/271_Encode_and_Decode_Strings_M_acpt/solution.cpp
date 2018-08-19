/* 
 * 271. Encode and Decode Strings
 *
 * Design an algorithm to encode a list of strings to a string. 
 * The encoded string is then sent over the network and is decoded back to the original list of strings.
 *
 * Machine 1 (sender) has the function:
 *
 * string encode(vector<string> strs) {
 *   // ... your code
 *   return encoded_string;
 * }
 *     
 * Machine 2 (receiver) has the function:
 * vector<string> decode(string s) {
 *       //... your code
 *         return strs;
 * }
 * So Machine 1 does:
 * string encoded_string = encode(strs);
 * and Machine 2 does:
 *
 * vector<string> strs2 = decode(encoded_string);
 * strs2 in Machine 2 should be the same as strs in Machine 1.
 *
 * Implement the encode and decode methods.
 *
 * Note:
 * The string may contain any possible characters out of 256 valid ascii characters. 
 * Your algorithm should be generalized enough to work on any possible characters.
 * 
 * Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
 * Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.
 * */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Codec {
public:
    // Encodes a list of strings to a single string.
    // "len" + @ + "string"
    string encode (vector<string>& strs) {
        string res;
        for (auto x : strs) {
            res.append(to_string(x.size()));
            res.push_back('@');
            res.append(x);
        }
        return res;
    }
    // Decodes a single string to a list of strings.
    vector<string> decode (string s) {
        vector<string> res;
        int len = s.length();
        int i = 0;
        while (i < len) {
            string wordLen;
            while (s[i] >= '0' && s[i] <= '9') wordLen.push_back(s[i++]);
            int ilen = stoi(wordLen);
            string word;
            i++; // skip @;
            ilen += i;
            for (; i < ilen; i++) {
                word.push_back(s[i]);
            }
            res.push_back(word);
        }
        return res;
    }
};


// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
int main () {
    vector<string> strs;
    strs.push_back("hello");
    strs.push_back("world");
    strs.push_back("again12@asd!");
    
    Codec codec;
    vector<string> s = codec.decode(codec.encode(strs));
    for (auto x:s)
        cout << x<<endl;
    return 1;
}
