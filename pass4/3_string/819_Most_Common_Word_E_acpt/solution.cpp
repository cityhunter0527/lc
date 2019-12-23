/*
 * 819. Most Common Word
 * Given a paragraph and a list of banned words, return the most frequent word that is not in the list of banned words.  
 * It is guaranteed there is at least one word that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of punctuation.  
Words in the paragraph are not case sensitive.  The answer is in lowercase.

Example:

Input:
paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
banned = ["hit"]
Output: "ball"
Explanation:
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph.
Note that words in the paragraph are not case sensitive,
that punctuation is ignored (even if adjacent to words, such as "ball,"),
and that "hit" isn't the answer even though it occurs more because it is banned.


Note:

1 <= paragraph.length <= 1000.
0 <= banned.length <= 100.
1 <= banned[i].length <= 10.
The answer is unique, and written in lowercase (even if its occurrences in paragraph may 
have uppercase symbols, and even if it is a proper noun.)
paragraph only consists of letters, spaces, or the punctuation symbols !?',;.
There are no hyphens or hyphenated words.
Words only consist of letters, never apostrophes or other punctuation symbols.
 * */

#include <iostream>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

class StrElem {
public:
    std::string val;
    uint64_t    count;
};

class mycomp {
public:
    bool operator() (const StrElem* l, const StrElem* r) {
        return l->count < r->count; // << by default: less which is maxHeap
    }
};

class Solution {
public:
    void convert() {
    
    }

    std::string mostCommonWord(std::string paragraph, std::vector<std::string>& banned) {
        std::priority_queue<StrElem*, std::vector<StrElem*>, mycomp>  q;
        std::unordered_map<std::string, StrElem*> m;
        std::unordered_set<std::string> s;
        
        for (auto & y : banned) {
            s.insert(y);
        }
        
        std::for_each(paragraph.begin(), paragraph.end(), [](char & c) {
                if (c == '!' || c == '\'' || c == ';' || c == ',' || c == '?' || c == '.') {
                    c = ' ';
                } else {
                    c = ::tolower(c); 
                }});
        
        std::istringstream ss(paragraph);
        while (!ss.eof()) {
            std::string w;
            ss >> w;
            if (w.empty()) {
                break;
            }
            // w is valid word, no upper case, no punction symbols;
            if (m.find(w) != m.end()) {
                m[w]->count++;
            } else {
                // a new word;
                m[w] = new StrElem();
                m[w]->val = w;
                m[w]->count = 1;
            }
        } 

        for (auto& x : m) {
            q.push(x.second);
        }
        
        while (1) {
            auto t = q.top();
            if (s.find(t->val) == s.end()) {
                return t->val;
            }
            q.pop();
        }
    }
};

int main() {
    std::string paragraph = "a, a, a, a, b,b,b,c, c";
    std::vector<std::string> ban;
    ban.push_back("a");

    Solution s;
    
    std::cout << s.mostCommonWord(paragraph, ban) << std::endl;;

    return 1;
}
