#include "BSTUtil.hpp"

bool BinarySearchTree::search(TreeNode* x, int k) {
    if (x == nullptr) return false;
    if (x->val > k)
        return search(x->left, k);
    else if (x->val < k)
        return search(x->right, k);
    else 
        return true;
}

vector<int> BinarySearchTree::inOrder() {
    stack<TreeNode*> s; 
    TreeNode *p = mRoot;
    vector<int> r;
    while (!s.empty() || p) {
        if (p) {
            s.push(p);
            p = p->left;
        } else {
            p = s.top();
            r.push_back(p->val);
            s.pop();
            p = p->right;
        }
    }
    return r;
}

int BinarySearchTree::getMin(TreeNode* x) {
    assert(x != nullptr);
    while (x->left) x = x->left;
    return x->val;
}

// 
// remove 'key' in subTree rooted at x;
// return new root after removal of key;
//
TreeNode* BinarySearchTree::remove(TreeNode* x, int key) {
    if (x == nullptr) return nullptr;
    if (x->val > key)
        x->left = remove(x->left, key);
    else if (x->val < key)
        x->right = remove(x->right, key);
    else {
        // One child or no child
        if (x->left == nullptr || x->right == nullptr) { 
            TreeNode* tmp = x->left ? x->left : x->right;
            delete x;
            return tmp;
        } else { 
            // Two children
            // Get x's successor (which is min value of x->right)
            int min = getMin(x->right);
            x->val = min;
            // remove it from x;
            x->right = remove(x->right, min);
            return x;
        }
    }
    return x; // make compiler happy;
}

TreeNode* BinarySearchTree::insert(TreeNode* x, int key) {
    if (x == nullptr)
        return new TreeNode(key);
    if (x->val > key) 
        x->left = insert(x->left, key);
    else if (x->val < key)
        x->right = insert(x->right, key);
    return x;
}

TreeNode* BSTUtil::deserialize(istringstream& i) {
    string val;
    TreeNode* x = nullptr;
    i >> val;
    if (val == "#") return x;
    else {
        x = new TreeNode(stoi(val));
        x->left = deserialize(i);
        x->right = deserialize(i);
    }
    return x;
}

TreeNode* BSTUtil::deserialize(string data) {
    istringstream i(data);
    return deserialize(i);
}

void BSTUtil::serialize(ostringstream& o, TreeNode* x) {
    if (x == nullptr) {
        o << "# ";
    } else {
        o << x->val << " ";
        serialize(o, x->left);
        serialize(o, x->right);
    }
}

string BSTUtil::serialize(TreeNode* x) {
    ostringstream o;
    serialize(o, x);
    return o.str();
}

// no duplicated keys;
vector<int> 
BSTUtil::getUniqueRandomKeys(int num, int range) {
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
 
// convert array to a binary search tree. 
// it might not be balanced;
BinarySearchTree* 
BSTUtil::arrayToBST(vector<int>& arr) {
    BinarySearchTree* t = new BinarySearchTree();
    for (auto x:arr) {
        t->insert(x);
    }
    return t;
}

// 
// [start, end)
// start: not visited;
// end: should be excluced;
template <typename Iterator>
TreeNode* BSTUtil::sortedArrayToBST(Iterator start, Iterator end) {
    if (start >= end) return nullptr;
    auto size = distance(start, end);
    int val = *(start + size/2);
    auto pos = find(start, end, val);
    TreeNode* root = new TreeNode(val);
    root->left = sortedArrayToBST(start, pos);
    root->right = sortedArrayToBST(next(pos), end);
    return root;
}

// sorted array to balanced BST;
BinarySearchTree* 
BSTUtil::sortedArrayToBST(vector<int>& arr) {
    int n = arr.size();
    int val = arr[n/2];
    auto pos = find(arr.begin(), arr.end(), val);
    TreeNode* root = new TreeNode(val);
    root->left = sortedArrayToBST(arr.begin(), pos);
    root->right = sortedArrayToBST(next(pos), arr.end());
    return new BinarySearchTree(root);
}

