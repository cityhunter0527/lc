#ifndef __TEST_TREE_HPP__
#define __TEST_TREE_HPP__

#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;

class TestTreeBase {
public:
    void print(vector<int>& v) {
        for (auto x:v) 
            cout << x << ", ";
        cout << endl;
    }
    void print(vector<vector<string>>& res) {
        for (auto x:res) {
            for (auto y:x) {
                cout << y << ", ";
            }
            cout << endl;
        }
    }
};

class GenTreeToBinTreeTest : public TestTreeBase {
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

class ConstructGenTreeTest : public TestTreeBase {
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

class TestTree685 : public TestTreeBase {
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

class TestTree684 : public TestTreeBase {
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

class TestTree662 : public TestTreeBase {
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

class TestTree669 : public TestTreeBase {
public:
    bool tc1();
    bool run() {
        tc1();
        return true;
    }
};


class TestTree654 : public TestTreeBase {
public:
    bool tc0();
    bool tc1();
    bool run() {
        tc0();
        tc1();
        return true;
    }
};

class TestTree653 : public TestTreeBase {
public:
    bool tc0();
    bool tc1();
    bool run() {
        tc0();
        tc1();
        return true;
    }
};

class TestTree437 : public TestTreeBase {
public:
    /bool tc0();
    bool tc1();
    bool run() {
        //tc0();
        tc1();
        return true;
    }
};

#endif
