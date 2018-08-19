#include "BTree.hpp"
#include <ctime>
#include <unordered_set>
#include <assert.h>
using namespace std;

class BTreeTest {
protected:
    vector<int> getUniqueRandomKeys(int num, int range = 100);
    vector<int> getRandomKeys(int num, int range = 100);
public:
    bool inserttc0();
    bool inserttc1();
    bool deletetc1();
    bool mixed();
    bool bug1ut();
    bool bug2ut();
};

// duplicated keys allowed;
vector<int> getRandomKeys(int num, int range = 100) {
    vector<int> res;
    srand(time(nullptr));
    int i = 0;
    while (i++ < num) 
        res.push_back(rand()%range);
    return res;
}

// no duplicated keys;
vector<int> BTreeTest::getUniqueRandomKeys(int num, int range) {
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
bool BTreeTest::bug2ut() {
    vector<int> v = {90, 41, 70, 96, 4, 9, 16, 94, 81, 39, 86, 30, 58, 79, 63, 46, 57, 10, 40, 89, 20, 98, 73, 45, 27, 29, 93, 88, 31, 83, 82, 54, 80, 15, 48, 32, 49, 42, 44, 6, 92, 95, 33, 87, 61, 71, 97, 25, 77, 65, 36, 35, 59, 14, 51, 85, 55, 43, 2, 19, 68, 7, 66, 75, 56, 84, 50, 12, 11, 67, 1, 8, 24, 53, 38, 64, 37, 99, 76, 47, 78, 34, 74, 91, 69, 18, 17, 21, 28, 5, 26, 22, 62, 60, 3, 13, 72, 23, 0, 52};

    BTree bt(3);
    for (auto x:v) {
        bt.insert(x);
        assert(bt.isValidBTree());
    }

    bt.levelOrder();

    cout << "Start to remove: 90" << endl;
    bt.remove(90);
    bt.levelOrder();
    assert(bt.isValidBTree());

    cout << "remove: 41" << endl;
    bt.remove(41);
    bt.levelOrder();
    assert(bt.isValidBTree());
    return true;
}
bool BTreeTest::bug1ut() {
    vector<int> v = {1, 44, 98, 19, 78, 47, 86, 43, 59, 73, 25, 90, 40, 39, 20, 15, 11, 68, 54, 42, 8, 99, 31, 48, 45, 30, 95, 9, 62, 17, 10, 58, 67, 81, 37, 14, 80, 93, 6, 85, 53, 55, 18, 74, 22, 61, 34, 82, 71, 29, 89, 46, 66, 75, 36, 28, 83, 12, 56, 79, 24, 23, 60, 77, 52, 33, 32, 65, 16, 64, 26, 76, 2, 72, 27, 7, 92, 94, 41, 3, 88, 4, 91, 51, 5, 57, 50, 38, 35, 96, 21, 70, 97, 0, 63, 49, 13, 69, 84, 87};

    BTree bt(3);
    for (auto x:v) {
        bt.insert(x);
        assert(bt.isValidBTree());
    }

    bt.levelOrder();

    cout << "Start to remove: 1" << endl;
    bt.remove(1);
    bt.levelOrder();
    assert(bt.isValidBTree());

    return true;
}
// 
// 1. Generate a set of unique keys and insert to b-tree one by one. Validate b-tree;
// 2. Generate a same set of unique keys but with different sequence.
// 3. Remove them one by one and validate b-tree property.
//
bool BTreeTest::mixed() {
    srand(time(nullptr));
    int md = rand()%10;
    if (md < 3) md = 3;
    BTree bt(md);
    vector<int> v = getUniqueRandomKeys(100, 100);
    cout << "Start to insert:" << endl;
    for (auto x:v) {
        cout << x << ", ";
        bt.insert(x);
        assert(bt.isValidBTree());
    }
    cout << endl;

    cout << "Minimum Degree: " << bt.getMinDegree() << endl;
    bt.levelOrder();

    cout << "Start to remove:" << endl;
    srand(time(nullptr));
    v.clear();
    // get the same set of unique keys but different sequence;
    v = getUniqueRandomKeys(100, 100);
    for (auto x:v) {
        cout << "====> Remove " << x << endl;
        bt.remove(x);
        bt.levelOrder();
        assert(bt.isValidBTree());
    }

    return true;
}

bool BTreeTest::deletetc1() {
    BTree bt(3);
    bt.insert(15);
    bt.insert(9);
    bt.insert(2);
    bt.insert(19);
    bt.insert(16);
    bt.insert(8);
    bt.insert(5);
    bt.insert(18);
    bt.insert(4);
    bt.insert(1);
    bt.insert(20);
    bt.insert(7);
    bt.insert(12);
    bt.insert(13);
    bt.insert(3);
    bt.insert(6);
    bt.insert(10);
    bt.insert(11);
    bt.insert(17);
    bt.insert(14);
    cout << "Minimum Degree: " << bt.getMinDegree() << endl;
    bt.levelOrder();
    
    cout << "====> remove 6" << endl;
    bt.remove(6);
    bt.levelOrder();
    assert(bt.isValidBTree());
    cout << "====> remove 7" << endl;
    bt.remove(7);
    bt.levelOrder();
    assert(bt.isValidBTree());
    cout << "====> remove 19" << endl;
    bt.remove(19);
    bt.levelOrder();
    assert(bt.isValidBTree());
    cout << "====> remove 13" << endl;
    bt.remove(13);
    bt.levelOrder();
    assert(bt.isValidBTree());
    cout << "====> remove 1" << endl;
    bt.remove(1);
    bt.levelOrder();
    assert(bt.isValidBTree());
    cout << "====> remove 12" << endl;
    bt.remove(12);
    bt.levelOrder();
    assert(bt.isValidBTree());
    cout << "====> remove 3" << endl;
    bt.remove(3);
    bt.levelOrder();
    assert(bt.isValidBTree());
    cout << "====> remove 18" << endl;
    bt.remove(18);
    bt.levelOrder();
    assert(bt.isValidBTree());
    return true;
}

bool BTreeTest::inserttc0() {
    BTree bt(4);
    bt.insert(15);
    bt.insert(9);
    bt.insert(2);
    bt.insert(19);
    bt.insert(16);
    bt.insert(8);
    bt.insert(5);
    bt.insert(18);
    bt.insert(4);
    bt.insert(1);
    bt.insert(20);
    bt.insert(7);
    bt.insert(12);
    bt.insert(13);
    bt.insert(3);
    bt.insert(6);
    bt.insert(10);
    bt.insert(11);
    bt.insert(17);
    bt.insert(14);

    bt.levelOrder();
    return true;
}
bool BTreeTest::inserttc1() {
    BTree bt(4);
    vector<int> keys = getUniqueRandomKeys(57, 57);
    for (auto x:keys)
        bt.insert(x);
    vector<int> v = bt.traverse();
    cout << "Traverse: ";
    for (auto x:v)
        cout << x << ", ";
    cout << endl;

    bt.levelOrder();
    return true;
}

int main() {
    BTreeTest test;
#if 0
    test.inserttc0();
    if (test.inserttc1() != true)
        cout << "test case: inserttc1() failed" << endl;
    test.deletetc1();
    //test.bug1ut();
    //test.bug2ut();
#endif
    test.mixed();
    return 0;
}

