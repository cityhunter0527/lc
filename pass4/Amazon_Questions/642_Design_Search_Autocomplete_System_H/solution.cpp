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

#define NUM_CHAR_TYPES  256
class TrieNode {
public:
    TrieNode() {
        is_end = false;
        c.resize(NUM_CHAR_TYPES);
        std::fill(c.begin(), c.end(), nullptr);
        prefix_cnt = 0;
        sentence_cnt = 0;
    }
    uint32_t prefix_cnt;
    uint32_t sentence_cnt;
    std::vector<TrieNode*> c;
    bool is_end;
};

class AutocompleteSystem {
public:
    void add_word(std::string sentence, TrieNode* p, int times) {
        for (auto x : sentence) {
            if (x != '#') {
                if (p->c[x] == nullptr) {
                    p->c[x] = new TrieNode();
                }
                p->prefix_cnt++;
                p = p->c[x];
            }
        }
        if (p->is_end) 
            p->sentence_cnt += times;
        else {
            p->is_end = true;
            p->sentence_cnt = times;
        }
    }
    
    AutocompleteSystem(std::vector<std::string> sentences, std::vector<int> times) {
        root = new TrieNode();
        TrieNode* p = root;
        int n = sentences.size();
        for (uint32_t i = 0; i < n; i++) {
            p = root;
            add_word(sentences[i], p, times[i]);
        }
    }

    std::vector<std::string> input(char d) {
        std::vector<std::string>     res(3);
        // Need to save the input in m_input as user might type chars one by one and we need to adjust the return by the input;
        // e.g. input('i') and input(' '), m_input would be "i ", 
        if (d =='#') {
            add_word(m_input, root, 1); 
            
            m_input.clear();
            res.resize(0);
            return res;
        }
        m_input.push_back(d);
        int m1= 0, m2 = 0, m3= 0;   // m1 <= m2 <= m3
        
        std::string s(m_input);

        // get the node p that starts with "i ";
        TrieNode *p = get_node(root, s);

        // if no such node, just return null
        if (p == nullptr) {
            res.resize(0);
            return res;
        }

        // otherwise, do dfs search and save the results in res;
        // m1, m2, and m3 is the top 3 num of occurences in which m1 <= m2 <= m3
        dfs(p, s, res, m1, m2, m3);
        // if there are less than 3 results, we need to remove the empty ones;
        if (res[2] == "") res.pop_back();
        if (res[1] == "") res.pop_back();
        if (res[0] == "") res.pop_back();
        return res;
    }

    TrieNode* get_node(TrieNode *x, std::string& s) {
        for (int i = 0; i < s.size(); i ++) {
            if (x->c[s[i]]) {
                x = x->c[s[i]];
            } else 
                return nullptr;
        }
        return x;
    }
    
    // TODO: only beats 4.6%. Do some improvement;
    void dfs(TrieNode *x, std::string& s, std::vector<std::string>& res, int& m1, int& m2, int& m3) {
        if (x->is_end) {
            // we've got a complete sentence saved in s while do depth-first-search;
            // let's check whether this sentence is of top 3
            // "Batmap".compare("Superman")  < 0;
            if (x->sentence_cnt > m3 || (x->sentence_cnt == m3 && s.compare(res[2]) < 0)) {
                res[2] = res[1];
                res[1] = res[0];
                res[0] = s;
                m1 = m2;
                m2 = m3;
                m3 = x->sentence_cnt;
            } else if (x->sentence_cnt > m2 || (x->sentence_cnt == m3 && m3 > m2 && s.compare(res[2]) > 0) || (x->sentence_cnt == m2 && s.compare(res[1]) < 0)){
                // m3 keeps unchanged; m1 to be removed
                res[2] = res[1];
                res[1] = s;
                m1 = m2;
                m2 = x->sentence_cnt;
            } else if (x->sentence_cnt > m1 || (x->sentence_cnt == m2 && m2 > m1 && s.compare(res[1]) > 0) || (x->sentence_cnt == m1 && s.compare(res[0]) < 0)){
                res[2] = s;
                m1 = x->sentence_cnt;       
            } 
        } 
        //else {
            // not a complete sentence yet;
            // keep searching with dfs;
            for (size_t i = 0; i < NUM_CHAR_TYPES; i++) {
                if (x->c[i]) {
                    s.push_back(i);
                    dfs(x->c[i], s, res, m1, m2, m3);
                    // when its done, need to pop it from s so that we only form strings traversing that belongs to a sentence;
                    s.pop_back();
                } 
            }
        //}
    }

private:
    TrieNode   *root;
    std::string m_input;
    //std::map<std::string, int>  m;
};

/**
 *  Your AutocompleteSystem object will be instantiated and called as such:
 *  AutocompleteSystem obj = new AutocompleteSystem(sentences, times);
 *  vector<string> param_1 = obj.input(c);
 *  */
    
void print(std::vector<std::string>  o) {
    for (auto& x : o) {
        std::cout << x << std::endl;
    }
    std::cout << "===============" << std::endl;
}
// Input:
// ["AutocompleteSystem","input","input","input","input","input","input","input","input","input","input","input","input"]
// [[["i love you","island","iroman","i love leetcode"],[5,3,2,2]],["i"],[" "],["a"],["#"],["i"],[" "],["a"],["#"],["i"],[" "],["a"],["#"]]
// Output:
// [null,["i love you","island","i love leetcode"],["i love you","i love leetcode"],[],[],["i love you","island","i love leetcode"],["i love you","i love leetcode","i a"],["i a"],[],["i love you","island","i love leetcode"],["i love you","i love leetcode","i a"],["i a"],[]]
// Expected:
// [null,["i love you","island","i love leetcode"],["i love you","i love leetcode"],[],[],["i love you","island","i love leetcode"],["i love you","i love leetcode","i a"],["i a"],[],["i love you","island","i a"],["i love you","i a","i love leetcode"],["i a"],[]]
//
int main() {
    // test case 1
    std::vector<int> times = {5,3,2,2};
    std::vector<std::string>  sentences = {"i love you#", "island#","ironman#", "i love leetcode#"};
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
  *  Output:
  *  [null,[],[],[],["bc"],["bc"],[],["a"],["abbc","abc"],["abc"],[],["a"],["abbc","abc"],["abc"],[]]
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
