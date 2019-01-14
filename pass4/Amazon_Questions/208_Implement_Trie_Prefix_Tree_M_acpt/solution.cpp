/*
 * 208. Implement Trie (Prefix Tree)
 *
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Example:
 *
 * Trie trie = new Trie();
 *
 * trie.insert("apple");
 * trie.search("apple");   // returns true
 * trie.search("app");     // returns false
 * trie.startsWith("app"); // returns true
 * trie.insert("app");   
 * trie.search("app");     // returns true
 * Note:
 *
 * You may assume that all inputs are consist of lowercase letters a-z.
 * All inputs are guaranteed to be non-empty strings.
 * */

#include <iostream>
#include <vector>
#include <string>

class TrieNode {
public:
    TrieNode() {
        is_end = false;
        prefix_cnt = 0;
        c.resize(26);
        std::fill(c.begin(), c.end(), nullptr);
    }
    bool is_end;         // true if this is a word
    size_t prefix_cnt;   // num of words starting with this prefix
    std::vector<TrieNode*> c;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();                
    }
                
    /** Inserts a word into the trie. */
    void insert(std::string word) {
        TrieNode *p = root;
        for (auto x : word) {
            int ind = x - 'a';
            if (p->c[ind] == nullptr) {
                p->c[ind] = new TrieNode();
            }
            p->c[ind]->prefix_cnt++;
            p = p->c[ind];
        }
        p->is_end = true;
    }
                    
    /** Returns if the word is in the trie. */
    bool search(std::string word) {
        TrieNode *p = root;
        for (auto x : word) {
            int ind = x - 'a';
            if (p->c[ind]) {
                p = p->c[ind];
            } else 
                return false;
        }
        return p->is_end;
    }
                        
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix) {
        TrieNode *p = root;
        for (auto x : prefix) {
            int ind = x - 'a';
            if (p->c[ind]) 
                p = p->c[ind];
            else 
                return false;
        }
        return true;
    }
private:
    TrieNode* root;
};

/**
 *  * Your Trie object will be instantiated and called as such:
 *  Trie obj = new Trie();
 *  obj.insert(word);
 *  bool param_2 = obj.search(word);
 *  bool param_3 = obj.startsWith(prefix);
 *  */

int main() {
    Trie* obj = new Trie();
    obj->insert("apple");
    std::cout << obj->search("apple") << std::endl;
    std::cout << obj->search("app") << std::endl;
    std::cout << obj->startsWith("app") << std::endl;
    obj->insert("app");
    std::cout << obj->search("app") << std::endl;
    return 1;
}
