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

void BinarySearchTree::inOrderPrint() {
    vector<int> v = inOrder();
    cout << "Inorder: ";
    for (auto x:v) {
        cout << x << ", ";
    }
    cout << endl;
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

void GeneralTree::levelOrderPrint(GenTreeNode* x) {
    if (x == nullptr) return;
    queue<GenTreeNode*>  q;
    q.push(x);
    q.push(nullptr);
    cout << "Level Order: " << endl;
    while (!q.empty()) {
        x = q.front();
        q.pop();
        if (x != nullptr) {
            cout << x->val << ", ";  // visit this node
            for (unsigned int i = 0; i < x->c.size(); i++) {
                q.push(x->c[i]);
            }
        } else {
            if (!q.empty()) q.push(nullptr);
            cout << endl;
        }
    }
}

vector<vector<string>> BSTUtil::printTree(TreeNode* root) {
    vector<vector<string>> res;
    if (!root) return res;
    deque<TreeNode*> q;
    q.push_back(root);
    q.push_back(nullptr);
    int depth = 0;
    // 1. Get height of this tree by level order traversal;
    while (!q.empty()) {
        TreeNode* t = q.front(); q.pop_front();
        if (t == nullptr) {
            depth++;
            if (!q.empty()) q.push_back(nullptr);
            continue;
        } 
        if (t->left)
            q.push_back(t->left);
        if (t->right)
            q.push_back(t->right);
    }

    //
    // init 2D array based on depth, default value to ""
    // numer of colums should be 2^depth-1.
    //
    res.resize(depth, vector<string>(pow(2, depth)-1, ""));

    // 
    // do another level order traversal and for each node, set its value into 2D array
    //
    q.push_back(root);
    q.push_back(nullptr);
    int curDepth = 0;
    unordered_map<TreeNode*, int> m;     // node's address to its id in its row (row is curDepth)
    m[root] = pow(2, depth-1) - 1;
    res[curDepth][m[root]] = to_string(root->val);
    curDepth++;
    while(!q.empty()) {
        TreeNode* t = q.front(); q.pop_front();
        int id;
        if(t == nullptr) {
            curDepth++;
            if (!q.empty()) q.push_back(nullptr);
            continue;
        }
        if (t->left) {
            q.push_back(t->left);
            // left child's id is:
            //      parent's id - (total subTree's nodes (complete subTree) / 2) 
            // Total subTree's nodes is 2^(depth-curDepth)
            id = m[t] - pow(2, depth-curDepth)/2;  
            res[curDepth][id] = to_string(t->left->val);
            m[t->left] = id;
        } 
        if (t->right) {
            q.push_back(t->right);
            // right child's id is: 
            //      parent's id + (total subTree's nodes (complete subTree) / 2)
            // Total subTree's nodes is 2^(depth-curDepth)
            id = m[t] + pow(2, depth-curDepth)/2;
            res[curDepth][id] = to_string(t->right->val);
            m[t->right] = id;
        }
    }
    return res;
}
