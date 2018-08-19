#ifndef __LLIST_TEST_HPP__
#define __LLIST_TEST_HPP__

#include <vector>
#include <iostream>
#include <typeinfo>
#include <unordered_set>
#include <ctime>
#include "LinkedList.hpp"
using namespace std;

class LListTestBase {
protected:
    void Print(ListNode* x) {
        while(x) {
            cout << x->val << "->";
            x = x->next;
        }       
        cout << "nullptr" << endl;
    }
    ListNode* Construct(vector<int>& num) {
        ListNode dummy(1);
        ListNode* p = &dummy;
        for (int i = 0; i < num.size(); i++) {
            p->next = new ListNode(num[i]);
            p = p->next;
        }
        return dummy.next;
    }

    vector<int> getUniqueRandomKeys(int num, int range) {
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
};

class LListTest725 : public LListTestBase {
private:
    // bool f1 and f2 is used to pretty printing. e.g. to 
    // avoid print ", " after/before the last/first element in []
    void Print(vector<ListNode*>& v); 
    void Print(vector<int>& a, vector<ListNode*>& b, int k);
    void Print(vector<int>& v);
public:
    bool tc1();
    bool tc2(); 
    bool tc3();
    bool tc4();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1(); 
        tc2(); 
        tc3(); 
        tc4();
        return true;
    }
};

class LListTest445 : public LListTestBase {
public:
    bool tc1();
    bool tc2();
    bool tc3();
    bool tc4();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1();
        tc2();
        tc3();
        tc4();
        return true;
    }
};

class LListTest328 : public LListTestBase {
public:
    bool tc1();
    bool tc2();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1();
        return true;
    }
};

class LListTest148 : public LListTestBase {
public:
    bool tc1();
    bool tc2();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1();
        tc2();
        return true;
    }
};

class LListTest147 : public LListTestBase {
public:
    bool tc1();
    bool tc2();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1();
        tc2();
        return true;
    }
};
class LListTest142: public LListTestBase {
public:
    bool tc1();
    bool tc2();
    bool tc3();
    bool tc4();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1();
        tc2();
        tc3();
        tc4();
        return true;
    }
};

class LListTest23: public LListTestBase {
public:
    bool tc1();
    bool tc2();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1();
        tc2();
        return true;
    }
};
class LListTestIntersect: public LListTestBase {
public:
    bool tc1();
    bool tc2();
    bool tc3();
    bool tc4();
    bool run() {
        cout << "===== " << typeid(*this).name() << " =====" << endl;
        tc1();
        tc2();
        tc3();
        tc4();
        return true;
    }
};
#endif
