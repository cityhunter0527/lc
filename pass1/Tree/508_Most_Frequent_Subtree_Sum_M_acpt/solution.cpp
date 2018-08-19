/*
 * 508. Most Frequent Subtree Sum
 *
 * Given the root of a tree, you are asked to find the most frequent subtree sum. 
 * The subtree sum of a node is defined as the sum of all the node values formed 
 * by the subtree rooted at that node (including the node itself). 
 * So what is the most frequent subtree sum value? If there is a tie, 
 * return all the values with the highest frequency in any order.
 *
 * Examples 1
 * Input:
 *   5
 *  /  \
 * 2   -3
 * return [2, -3, 4], since all the values happen only once, return all of them in any order.
 * Examples 2
 * Input:
 *
 *    5
 *   /  \
 *  2   -5
 * return [2], since 2 happens twice, however -5 only occur once.
 * Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // bottom-up
    // dfs caculate the sum of current node n (in a bottom-up manner).
    int dfs(TreeNode* n, int& numMaxCnt, unordered_map<int, int>& m) {
        if (n == nullptr) return 0;
        int sum = dfs(n->left) + dfs(n->right) + n->val;
        m[sum]++; 
        numMaxCnt = max(numMaxCnt, m[sum]);
        return sum;
    }
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> res;
        unordered_map<int, int> m; // first: sum, second: numOfOccurence
        int numMaxCnt = 0;
        dfs(root, numMaxCnt, m);
        for (auto x:m) {
            if (x.second == numMaxCnt)
                res.push_back(x.first);
        }
        return res;
    }
};

int main() {
    TreeNode* r = new TreeNode(5);
    r->left = new TreeNode(2);
    r->right = new TreeNode(-3);

    Solution s;
    vector<int> out = s.findFrequentTreeSum(r);

    for (auto x:out) 
        cout << x << ", ";
    cout << endl;
    return 1;
}
