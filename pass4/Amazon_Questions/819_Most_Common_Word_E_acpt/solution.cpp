/*
 * 819. Most Common Word
 * Given a paragraph and a list of banned words, return the most frequent word that is not in the list of 
 * banned words.  It is guaranteed there is at least one word that isn't banned, and that the answer is unique.
 *
 * Words in the list of banned words are given in lowercase, and free of punctuation.  
 * Words in the paragraph are not case sensitive.  The answer is in lowercase.
 *
 *  Example:
 *
 *  Input: 
 *  paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
 *  banned = ["hit"]
 *  Output: "ball"
 *  Explanation: 
 *  "hit" occurs 3 times, but it is a banned word.
 *  "ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
 *  Note that words in the paragraph are not case sensitive,
 *  that punctuation is ignored (even if adjacent to words, such as "ball,"), 
 *  and that "hit" isn't the answer even though it occurs more because it is banned.
 *
 *  Note:
 *
 *  1 <= paragraph.length <= 1000.
 *  1 <= banned.length <= 100.
 *  1 <= banned[i].length <= 10.
 *  The answer is unique, and written in lowercase (even if its occurrences in paragraph may have uppercase symbols, and even if it is a proper noun.)
 *  paragraph only consists of letters, spaces, or the punctuation symbols !?',;.
 *  There are no hyphens or hyphenated words.
 *  Words only consist of letters, never apostrophes or other punctuation symbols.
 * */
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <unordered_set>

class Solution {
public:
    std::string mostCommonWord(std::string paragraph, std::vector<std::string>& banned) {
        std::unordered_map<std::string, int>    map;        /// word to # of occurence
        std::unordered_set<std::string>         banned_set; /// word to # of occurence

        // replace all the punctions to while space
        std::transform(paragraph.begin(), paragraph.end(), paragraph.begin(), 
                [](unsigned char c) -> unsigned char { if (c == '!' || c == '?' || c == '\'' || c == ',' || c == ';' || c == '.') return ' '; else return c; });
        
        // replace all the punctions to lower case
        std::transform(paragraph.begin(), paragraph.end(), paragraph.begin(), ::tolower);


        // load each band word in to set;
        for (auto& x : banned) {
            banned_set.insert(x);
        }
        
        int max_cnt = 0;
        std::string res;
        std::istringstream i(paragraph);

        // for each word in the paragrah
        while (i) {
            std::string word;
            i >> word;
            if (banned_set.find(word) == banned_set.end()) {
                // word is not in the banned list
                if (map.find(word) == map.end())
                    map[word] = 1;
                else 
                    map[word]++;

                if (map[word] > max_cnt) {
                    max_cnt = map[word];
                    res = word;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    std::vector<std::string>  banned = {"hit"};
    std::string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
    std::cout << s.mostCommonWord(paragraph, banned) << std::endl;
    return 0;
}
