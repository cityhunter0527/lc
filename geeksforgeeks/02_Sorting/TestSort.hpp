#ifndef __TEST_SORT_HPP__
#define __TEST_SORT_HPP__

#include <iostream>
#include <typeinfo>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class TestSortBase {
public:
    void print(vector<int> v) {
        for (auto x:v)
            cout << x << ", ";
        cout << endl;
    }

    vector<int> getRandomKeys(int num, int range) {
        vector<int> res;
        srand(rand()+time(nullptr));
        while (res.size() < num) {
            res.push_back(rand() % range);
        }
        return res;
    }

    vector<int> getUniqueRandomKeys(int num, int range) {
        vector<int> res;
        srand(rand() + time(nullptr));
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

};

class TestSortPartition : public TestSortBase {
private:
    bool verify(vector<int>& v, int f1, int f2); 

public:
    bool tc0(); 
    bool tc1(); 
    bool tc2(); 
    bool run() {
        //tc0();
        //tc1();
        tc2();
        return true;
    }    
};
#endif
