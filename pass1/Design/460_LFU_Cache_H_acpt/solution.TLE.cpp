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
#include <vector>
#include <unordered_map>
using namespace std;
class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
    }
    int get(int key) {
        if (m.find(key) == m.end()) return -1;
        // increase used count
        v[m[key]].cnt++; 
        return v[update(m[key])].val;
    }
    void set(int key, int value) {
        if (cap == 0) return;
        if (m.find(key) != m.end()) {
            m[key]->val = value;
            get(key);
        } else {
            if (cap == v.size()) {
                m.erase(v.back().key);
                v.pop_back();
            }
            v.push_back(CacheNode(key, value, 1));
            m[key] = update(v.size()-1);
        }
    }
private:
    // update the vector starting from index i;
    int update(int i) {
        // update v based on cnt in desending order
        // e.g: the smallest cnt is always in the back.
        while ((i > 0) && (v[i].cnt >= v[i-1].cnt)) {
            m[v[i-1].key] = i;
            m[v[i].key] = i-1;
            swap(v[i], v[i-1]);
            i--;
        }
        return i;
    }
private:
   struct CacheNode {
       int key; 
       int val;
       int cnt;  // # of used
       CacheNode(int x, int y, int z):key(x), val (y), cnt(z) {}
   }; 
private:
    int                     cap; 
    unordered_map<int, int> m;   // first: key, second: index in v;
    vector<CacheNode>       v;    
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

