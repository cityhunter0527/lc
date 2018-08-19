#include <iostream>
#include <assert.h>
#include <ctime>
#include <vector>
#include <unordered_set>
#include "BinaryHeap.hpp"


class TestMinHeap {
protected:
    vector<int> getUniqueRandomKeys(int num, int range = 100);
public:
    bool mixed1();
    bool mixed2();
};

// no duplicated keys;
vector<int> TestMinHeap::getUniqueRandomKeys(int num, int range) {
    vector<int> res;
    srand(time(nullptr));
    unordered_set<int> s;
    int i = 0;
    if (num > range) return res;
    while (i < num) {
        int key = rand()%range;
        if (s.find(key) == s.end()) {
            s.insert(key);
            res.push_back(key);
            i++;
        } 
    }
    return res;
}

bool TestMinHeap::mixed2() {
    vector<int> v = getUniqueRandomKeys(10000, 10000);
    MinHeap h(v.size());
    // inset random keys to min heap;
    cout << "MinHeap Inserting: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
        h.insert(i);
    }
    cout << endl;

    // set all the bits in v since all keys are now in heap;
    fill(v.begin(), v.end(), 1);
    
    srand(time(nullptr));
    cout << "Heap Size: " << h.size() << endl;
    cout << "DeletingKey [Index, Val]: "; 
    // randomly extract half elements in heap
    for (int i = 0; i < v.size(); i += 2) {
        int index = rand()%h.size();   
        int key = h.getElement(index);
        // delete this element;
        h.deleteKey(index); 
        // unset it in v;
        cout << "[" << index << ", " << key << "]  ";
        assert(key != -1);
        assert(v[key] == 1);
        v[key] = 0;
    }
    
    cout << endl;
    
    cout << "ExtratMin [min, i]: ";
    // Get keys from small to large, if this key has not been deleted yet, 
    // assert it should be the root of the heap (returned by extractMin());
    for (int i = 0; i < v.size(); i++) {
        if (!v[i]) continue;
        int min = h.extractMin();
        cout << "["<< min << ", " << i << "]  ";
        assert (min == i);
    }
    cout << endl;
    return true;
}

bool TestMinHeap::mixed1() {
    vector<int> v = getUniqueRandomKeys(1000, 1000);
    MinHeap h(v.size());
    // inset random keys to min heap;
    cout << "MinHeap Inserting: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
        h.insert(i);
    }
    cout << endl;
    
    // extract key one by one and assert min value;
    cout << "MinHeap Extracting: ";
    for (int i = 0; i < v.size(); i++) {
        int ret = h.extractMin();
        cout << ret << ", ";
        assert(ret == i);
    }
    cout << endl;
    return true;
}

int main() {
    TestMinHeap t;
    //t.mixed1();
    t.mixed2();
}
