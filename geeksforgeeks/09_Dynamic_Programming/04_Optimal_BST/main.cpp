#include "OptimalBST.hpp"
#include <string>

class TestOptBST {
public:
    bool tc1();
    bool tc2();
};

bool TestOptBST::tc1() {
    vector<int> keys = {1,2,3,4,5};
    vector<int> p = {0, 15, 10, 5, 10, 20};
    vector<int> q = {5, 10,  5, 5, 5,  10};
    OptimalBST<int>* obst = new OptimalBST<int>(q, p, p.size()-1);
    cout << "Cost: " << obst->GetOptCost() << endl;
    
    OptimalBST<int>::TreeNode* root = obst->GetOptBST(keys);
    return true;

}

bool TestOptBST::tc2() {
    vector<string> keys = {"fox","cat","dog","tiger","lion","wolf"};
    vector<int> p = {0, 20, 23, 2, 5, 100, 1};
    vector<int> q = {0,  0,  0, 0, 0,   0, 0};
    OptimalBST<string>* obst = new OptimalBST<string>(q, p, p.size()-1);
    cout << "Cost: " << obst->GetOptCost() << endl;
    
    OptimalBST<string>::TreeNode* root = obst->GetOptBST(keys);
    return true;
}


int main() { 
    TestOptBST t;
    t.tc1();
    t.tc2();
    return 0;
}
