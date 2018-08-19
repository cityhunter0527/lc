#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
};

class mycomp {
public:
    bool operator() (const TreeNode* l, const TreeNode* r) {
        return l->val < r->val; // << by default: less which is maxHeap
    }
};

bool mycomp2 (const TreeNode* l, const TreeNode* r) {
    return l->val < r->val; 
}

int main() { 
    priority_queue<TreeNode*, vector<TreeNode*>, mycomp> pq; // <<< maxHeap
    vector<TreeNode*> v;
    TreeNode* r = new TreeNode(12);
    pq.push(r);
    v.push_back(r);
    r = new TreeNode(3);
    pq.push(r);
    v.push_back(r);
    r = new TreeNode(51);
    pq.push(r);
    v.push_back(r);
    r = new TreeNode(6);
    pq.push(r);
    v.push_back(r);
    r = new TreeNode(22);
    pq.push(r);
    v.push_back(r);
    pq.pop();
    cout << pq.top()->val << endl;
#if 1
    sort(v.begin(), v.end(), mycomp2);
    for (auto x:v) 
        cout << x->val<< ",";
    cout << endl;
#endif

    return 1;
}
