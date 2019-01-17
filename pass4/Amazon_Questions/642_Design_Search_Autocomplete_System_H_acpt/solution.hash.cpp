/*
 * 642. Design Search Autocomplete System
 * Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#'). 
 * For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of 
 * sentence already typed. Here are the specific rules:
 *
 * The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
 * The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). 
 * If several sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first).
 * 
 * If less than 3 hot sentences exist, then just return as many as you can.
 * When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
 *
 * Your job is to implement the following functions:
 *
 * The constructor function:
 *
 * AutocompleteSystem(String[] sentences, int[] times): This is the constructor. The input is historical data. 
 * Sentences is a string array consists of previously typed sentences. 
 * Times is the corresponding times a sentence has been typed. 
 * Your system should record these historical data.
 *
 * Now, the user wants to input a new sentence. The following function will provide the next character the user types:
 *
 * List<String> input(char c): The input c is the next character typed by the user. 
 * The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#'). 
 * Also, the previously typed sentence should be recorded in your system. 
 * The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.
 *
 *
 * Example:
 * Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2]) 
 * The system have already tracked down the following sentences and their corresponding times: 
 * "i love you" : 5 times 
 * "island" : 3 times 
 * "ironman" : 2 times 
 * "i love leetcode" : 2 times 
 * Now, the user begins another search: 
 *
 * Operation: input('i') 
 * Output: ["i love you", "island","i love leetcode"] 
 * Explanation: 
 * There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. 
 * Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". 
 * Also we only need to output top 3 hot sentences, so "ironman" will be ignored. 
 *
 * Operation: input(' ') 
 * Output: ["i love you","i love leetcode"] 
 * Explanation: 
 * There are only two sentences that have prefix "i ". 
 *
 * Operation: input('a') 
 * Output: [] 
 * Explanation: 
 * There are no sentences that have prefix "i a". 
 *
 * Operation: input('#') 
 * Output: [] 
 * Explanation: 
 * The user finished the input, the sentence "i a" should be saved as a historical sentence in system. 
 * And the following input will be counted as a new search. 
 *
 * Note:
 * 1. The input sentence will always start with a letter and end with '#', and only one blank space will exist between two words.
 * 2. The number of complete sentences that to be searched won't exceed 100. 
 * 3. The length of each sentence including those in the historical data won't exceed 100.
 * 4. Please use double-quote instead of single-quote when you write test cases even for a character input.
 * 5. Please remember to RESET your class variables declared in class AutocompleteSystem, 
 *    as static/class variables are persisted across multiple test cases. Please see here for more details.
 * */

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <map>

class AutocompleteSystem {
public:
    // map to hash string to its number of occurences;
    AutocompleteSystem(std::vector<std::string> sentences, std::vector<int> times) {
        for (int i = 0; i < sentences.size(); i++) {
            m_map[sentences[i]] = times[i];
        }
    }
    // return true if a is prefix of s;
    bool is_prefix(const std::string &s, std::string& a) {
        if (a.size() > s.size()) return false;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != s[i]) return false;
        }
        return true;
    }
    std::vector<std::string> input(char c) {
        std::vector<std::pair<std::string, int>>  res;
        std::vector<std::string> tmp;
        if (c == '#') { 
            // This is end of the input, lets put this word in the our map;
            if (m_map.find(m_input) == m_map.end()) m_map[m_input] = 1;
            else m_map[m_input]++;  // if this word already exists, let's increase by 1;
            // clear the content saved in m_input before we process for next input;
            m_input.clear();
            return tmp;
        }
        
        // save this input to m_input;
        m_input.push_back(c);  
        // search all the sentences and check whether there is a match for m_input as the prefix
        for (auto it = m_map.begin(); it != m_map.end(); it++) {
            if (is_prefix(it->first, m_input))
                // if found, save it and its num of occurences;
                res.emplace_back(std::make_pair(it->first, it->second));
        }
        
        // sort base on occurrences and strings;
        std::sort(res.begin(), res.end(), [](std::pair<std::string, int>& a, std::pair<std::string, int>& b) {
                    // if the ocurrences is equal, then compare the two strings;
                    if (a.second == b.second) { 
                        // "Batman".compare("Superman") is < 0
                        if (a.first.compare(b.first) < 0) return true;
                        else return false;
                    } else {
                        // return the one with bigger occurrences;
                        return a.second > b.second;
                    }
                });
        
        // now get the top 3;
        for (int i = 0; i < std::min(3ul, res.size()); i++) 
            tmp.push_back(res[i].first);
        return tmp;
    }

private:
    std::map<std::string, int>  m_map;
    std::string                 m_input;
};

void print(std::vector<std::string>  o) {
    for (auto& x : o) {
        std::cout << x << std::endl;
    }
    std::cout << "===============" << std::endl;
}
// Input:
// ["AutocompleteSystem","input","input","input","input","input","input","input","input","input","input","input","input"]
// [[["i love you","island","iroman","i love leetcode"],[5,3,2,2]],["i"],[" "],["a"],["#"],["i"],[" "],["a"],["#"],["i"],[" "],["a"],["#"]]
//
// Expected:
// [null,["i love you","island","i love leetcode"],["i love you","i love leetcode"],[],[],["i love you","island","i love leetcode"],["i love you","i love leetcode","i a"],["i a"],[],["i love you","island","i a"],["i love you","i a","i love leetcode"],["i a"],[]]
//
int main() {
    // test case 1
    std::vector<int> times = {5,3,2,2};
    std::vector<std::string>  sentences = {"i love you", "island","ironman", "i love leetcode"};
    AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
    std::vector<std::string> o = obj->input('i');
    print(o);
    print(obj->input(' '));
    print(obj->input('a'));
    print(obj->input('#'));

    print(obj->input('i'));
    print(obj->input(' '));
    print(obj->input('a'));
    print(obj->input('#'));

    print(obj->input('i'));
    print(obj->input(' '));
    print(obj->input('a'));
    print(obj->input('#'));
    delete obj;

 /*   test case 2
  *  
  *  ["AutocompleteSystem","input","input","input","input","input","input","input","input","input","input","input","input","input","input"]
  *  [[["abc","abbc","a"],[3,3,3]],["b"],["c"],["#"],["b"],["c"],["#"],["a"],["b"],["c"],["#"],["a"],["b"],["c"],["#"]]
  *  
  *  Expected:
  *  [null,[],[],[],["bc"],["bc"],[],["a","abbc","abc"],["abbc","abc"],["abc"],[],["abc","a","abbc"],["abc","abbc"],["abc"],[]] 
  *  */
    times.clear();
    sentences.clear();
    times = {3,3,3};
    sentences = {"abc", "abbc", "a"};
    AutocompleteSystem* obj2 = new AutocompleteSystem(sentences, times);
    print(obj2->input('b'));
    print(obj2->input('c'));
    print(obj2->input('#'));

    print(obj2->input('b'));
    print(obj2->input('c'));
    print(obj2->input('#'));
    
    print(obj2->input('a'));
    print(obj2->input('b'));
    print(obj2->input('c'));
    print(obj2->input('#'));

    print(obj2->input('a'));
    print(obj2->input('b'));
    print(obj2->input('c'));
    print(obj2->input('#'));

    return 0;
}
