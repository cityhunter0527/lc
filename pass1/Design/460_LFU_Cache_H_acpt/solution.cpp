/*
 * 460. LFU Cache
 *
 * Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and set.
 *
 * get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 * set(key, value) - Set or insert the value if the key is not already present. 
 *                   When the cache reaches its capacity, it should invalidate the least frequently used item before 
 *                   inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys 
 *                   that have the same frequency), the least recently used key would be evicted.
 *
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 *
 * Example:
 *
 * LFUCache cache = new LFUCache( 2 );

cache.set(1, 1);
cache.set(2, 2);
cache.get(1);       // returns 1
cache.set(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.set(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
 * */

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;
class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
    }
    // O(1)
    int get(int key) {
        if (m.find(key) == m.end()) return -1;
        // m[key].second is freq of this key;
        // use freq as "key" to erase it from the list (this list holds keys with same freq)
        freq[m[key].second].erase(mIt[key]); 
        m[key].second++; // increase freq
        freq[m[key].second].push_front(key); // move it to the front of list with same freq
        mIt[key] = freq[m[key].second].begin(); // save the iterator in this list to mIt

        // list size becomes zero, it must be because it is the last key in the list.
        // so it is safe to set minFreq to its new Freq (after increased by 1);
        if (freq[minFreq].size() == 0)
            minFreq = m[key].second;
        return m[key].first;
    }
    // O(1)
    void set(int key, int value) {
        if (cap == 0) return;
        if (m.find(key) != m.end()) {
            m[key].first = value; 
            get(key); // increase the freq
            return;
        } else {
            if (cap == m.size()) {
                int key = freq[minFreq].back();
                freq[minFreq].pop_back();
                m.erase(key);
                mIt.erase(key);
            }
            m[key] = {value, 1};
            minFreq = 1;
            freq[1].push_front(key);
            mIt[key] = freq[1].begin();
        }
    }
private:
    int cap;
    int minFreq;
    unordered_map<int, pair<int, int>>      m;    // key to {value, freq}
    unordered_map<int, list<int>>           freq; // freq to key list
    unordered_map<int, list<int>::iterator> mIt;  // key to list iterator (same freq)
};

int main() {
#if 0
    LFUCache* cache = new LFUCache(0);
    cache->set(0,0);
    cout << cache->get(0) << endl;
#endif
#if 1
    LFUCache* cache = new LFUCache(3);
    int v;
    cache->set(1, 1);
    cache->set(2, 2);
    cout<< cache->get(1) << endl;       // returns 1
    cache->set(3, 3);    
    cache->set(4, 4);    // evicts key 2.
    cout << cache->get(2) << endl;       // returns -1 (not found)
    cout << cache->get(1) << endl;       // returns 1 
    cout << cache->get(3) << endl;       // returns 3
    cout << cache->get(4) << endl;       // returns 4
#endif
    return 1;
}

