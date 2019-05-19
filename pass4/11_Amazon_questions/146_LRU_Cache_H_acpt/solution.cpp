// 
// Design and implement a data structure for Least Recently Used (LRU) cache. 
// It should support the following operations: get and put.
//
// get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
// put(key, value) - Set or insert the value if the key is not already present. 
// When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
//
// Follow up:
// Could you do both operations in O(1) time complexity?
//
// Example:
//
// LRUCache cache = new LRUCache( 2 /* capacity */ );
//
// cache.put(1, 1);
// cache.put(2, 2);
// cache.get(1);       // returns 1
// cache.put(3, 3);    // evicts key 2
// cache.get(2);       // returns -1 (not found)
// cache.put(4, 4);    // evicts key 1
// cache.get(1);       // returns -1 (not found)
// cache.get(3);       // returns 3
// cache.get(4);       // returns 4
//

#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <functional>
#include <cassert>

class LRUCache {
public:
    LRUCache(int capacity) {
        m_cap = capacity;
    }
    int get(int key) {
        if (m_map.find(key) == m_map.end()) return -1;
        // get the value;
        int val = m_map[key]->second;
        // move the node to head of lru list;
        m_lru_list.erase(m_map[key]);
        m_lru_list.push_front(std::make_pair(key, val));
        // now update the map with val's corresponding iteratior in lru list;
        m_map[key] = m_lru_list.begin();
        return val;
    }
    void put(int key, int value) {
        if (m_map.find(key) == m_map.end()) {
            // key doesn't exist yet
            m_lru_list.push_front(std::make_pair(key, value));
            m_map[key] = m_lru_list.begin();
            // if the totoal keys exeeds m_cap, need to invalidate the oldest one;
            if (m_lru_list.size() > m_cap) {
                // remove the last key,val pair in the m_lru_list;
                m_map.erase(m_lru_list.back().first);
                m_lru_list.pop_back();
            }
        } else {
            // key already exists, no need to invalidate any one;
            
            // remove it from its original position
            m_lru_list.erase(m_map[key]);
            // put it in the beginning.
            m_lru_list.push_front(std::make_pair(key, value));
            // update map with its latest position
            m_map[key] = m_lru_list.begin();
        }
    }
private:
    int                                                                 m_cap;      // capacity
    std::list<std::pair<int, int>>                                      m_lru_list; // first: key, second: val
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator>   m_map;      // key to m_lru_list iterator
};

/**
 *  Your LRUCache object will be instantiated and called as such:
 *  LRUCache obj = new LRUCache(capacity);
 *  int param_1 = obj.get(key);
 *  obj.put(key,value);
 *  */

int main() {
    LRUCache cache(2 /* capacity */ );

    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1);       // returns 1
    cache.put(3, 3);            // evicts key 2
    assert(cache.get(2) == -1);       // returns -1 (not found)
    cache.put(4, 4);    // evicts key 1
    assert(cache.get(1) == -1);       // returns -1 (not found)
    assert(cache.get(3) == 3);       // returns 3
    assert(cache.get(4) == 4);       // returns 4

    return 0;
}
