
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int dfs(TreeNode* root, int sum, unordered_map<int, int>& m, int pre) {
        if (!root) return 0;
        root->val += pre;
        int res = (root->val == sum) + (m.count(root->val - sum) ? m[root->val - sum] : 0);
        m[root->val]++;
        res += dfs(root->left, sum, m, root->val) + dfs(root->right, sum, m, root->val);
        m[root->val]--;
        return res;
    }

    int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> m;
        return dfs(root, sum, m, 0);
    }
};

int main() {
    return 1;
}
