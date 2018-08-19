#include "OptimalBST.hpp"

class TestOptBST {
public:
    bool tc1();
    bool tc2();
};

bool TestOptBST::tc1() {
    vector<int> keys = {1,2,3,4,5};
    vector<int> p = {0, 15, 10, 5, 10, 20};
    vector<int> q = {5, 10,  5, 5, 5,  10};
    OptimalBST* obst = new OptimalBST(q, p, p.size()-1);
    cout << "Cost: " << obst->GetOptCost() << endl;
    
    TreeNode* root = obst->GetOptBST(keys);
    return true;

}

bool TestOptBST::tc2() {
    vector<int> keys = {'A','B','C','D','E','F'};
    vector<int> p = {0, 20, 23, 2, 5, 100, 1};
    vector<int> q = {0,  0,  0, 0, 0,   0, 0};
    OptimalBST* obst = new OptimalBST(q, p, p.size()-1);
    cout << "Cost: " << obst->GetOptCost() << endl;
    
    TreeNode* root = obst->GetOptBST(keys);
    return true;
}


int main() { 
    TestOptBST t;
    t.tc1();
    t.tc2();
    return 0;
}
