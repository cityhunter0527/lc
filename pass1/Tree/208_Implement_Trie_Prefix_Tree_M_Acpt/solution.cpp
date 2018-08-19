/* 
 * 208. Implement Trie (Prefix Tree)
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Note:
 * You may assume that all inputs are consist of lowercase letters a-z.
 * */
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

const int ALPHABET_NUM=26;
class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isEnd = false;
        prefixCount = 0;
        for (int i = 0; i < ALPHABET_NUM; i++) {
            child[i] = NULL;
        }
    }
    bool isEnd;
    int  prefixCount;
    TrieNode* child[ALPHABET_NUM];
};
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    // Inserts a word into the trie.
    void insert(string word) {
        // if word is already there, just return;
        if (search(word)) {
            return;
        }
        TrieNode* p = root;
        p->prefixCount++;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i] - 'a';
            if (p->child[c] == NULL) {
                p->child[c] = new TrieNode();
            }
            p->child[c]->prefixCount++;
            p = p->child[c];
        }
        p->isEnd = true;
    }
    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* p = root;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i] - 'a';
            if (p->child[c] == NULL) {
                return false;
            }
            p = p->child[c];
        }
        return p->isEnd;
    }
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* p = root;
        for (int i = 0; i < prefix.length(); i++) {
            int c = prefix[i] - 'a';
            if (p->child[c] == NULL) {
                return false;
            }
            p = p->child[c];
        }

        return true;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
int main() {
    Trie trie;
    trie.insert("cast");
    trie.insert("cat");
    trie.insert("dog");
    trie.insert("tiger");
    trie.insert("cats");
    trie.insert("a");
    bool b = trie.search("a");
    assert(b);
    b = trie.search("cat");
    assert(b);
    b = trie.search("catss");
    assert(!b);
    b = trie.search("tiger");
    assert(b);

    return 1;
}
