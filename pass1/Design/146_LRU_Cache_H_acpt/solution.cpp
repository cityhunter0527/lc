/*
 * 146. LRU Cache
 *
 * Design and implement a data structure for Least Recently Used (LRU) cache. 
 * It should support the following operations: get and set.
 *
 * get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 * set(key, value) - Set or insert the value if the key is not already present. 
 *                   When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 * */

#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache{
private:
    unsigned int cap;
    struct CacheNode {
        int key, val;
        CacheNode(int x, int y): key(x), val(y) {}
    };
    unordered_map<int, list<CacheNode>::iterator> m;
    list<CacheNode> l;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
                
    int get(int key) {
        if (m.find(key) == m.end())
            return -1;
        // remove from l, then add to begin;
        l.splice(l.begin(), l, m[key]);
        m[key] = l.begin();
        return l.begin()->val;
    }
                    
    void set(int key, int value) {
        if (cap == 0) return;
        if (m.find(key) == m.end()) {
            if (cap == l.size()) {
                m.erase(l.back().key);
                l.pop_back();
            }
            l.emplace_front(CacheNode(key, value));
            m[key] = l.begin();
        } else {
            // update value;
            m[key]->val = value;
            // remove from l, then add to begin;
            l.splice(l.begin(), l, m[key]);
            // restore iterator
            m[key] = l.begin();
        }
    }
};

int main() {
    LRUCache* c = new LRUCache(0);
    c->set(0,0);
    cout << c->get(0) << endl;
    return 1;
}
