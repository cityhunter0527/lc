/*
 * 662. Maximum Width of Binary Tree
 *
 * Given a binary tree, write a function to get the maximum width of the given tree. 
   The width of a tree is the maximum width among all levels. The binary tree has the 
   same structure as a full binary tree, but some nodes are null.

   The width of one level is defined as the length between the end-nodes (the leftmost and 
   right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).

Note: Answer will in the range of 32-bit signed integer.
* */

#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
using namespace std;

/** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /*

The idea is to use heap indexing:
        1
   2         3
 4   5     6   7
8 9 x 11  x 13 x 15
Regardless whether these nodes exist:

Always make the id of left child as parent_id * 2;
Always make the id of right child as parent_id * 2 + 1;

    1. Do level order traversal, for each level record left most node's id in array "left";
    2. For each visiting node in current level, compare its id with left most id, and update max width as needed.
*/
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        vector<int> left; // left[i]: depth i's left most node's id
        int width = 0, depth = 0;
        deque<TreeNode*> q;
        unordered_map<TreeNode*, int> m;  // hash table for node's addr to its id
        q.push_back(root);
        q.push_back(nullptr);
        m[root] = 1;       // set root's id as 1

        while (!q.empty()) {
            TreeNode* tmp = q.front(); q.pop_front();
            if (tmp == nullptr) {
                depth++;
                if (!q.empty()) q.push_back(nullptr);
                continue;
            }
            int id = m[tmp];
            if (depth >= left.size()) left.push_back(id); // first (and left most) node found in this level, record its id  
            if (tmp->left) {
                m[tmp->left] = 2*id;
                q.push_back(tmp->left);
            }
            if (tmp->right) {
                m[tmp->right] = 2*id + 1;
                q.push_back(tmp->right);
            }
            width = max(width, id - left[depth] + 1);
        }
        return width;
    }
#if 0
    // level order traversal
    int widthOfBinaryTree2(TreeNode* root) {
        if (!root) return 0;
        int width = 0, levWidth = 0;
        deque<TreeNode*> q;
        q.push_back(root);
        //q.push_back(nullptr); // level EOF
        TreeNode* tmp = nullptr;
        bool flag = true;
        while (!q.empty()) {
            if (flag) {
                // remove tailing nulls
                while ( !q.empty() && q.back() == nullptr) { 
                    q.pop_back();
                }
                // remove prefix nulls
                while ( !q.empty() && q.front() == nullptr) { 
                    q.pop_front();
                }
                if (q.empty()) break;
                q.push_back((TreeNode*)0xdeadbeaf);//re-insert the level EOF
                flag = false;
            }
            tmp = q.front(); q.pop_front();
            if (tmp == (TreeNode*)0xdeadbeaf) { // end of this level
                //q.push_back(nullptr);
                width = max(width, levWidth);
                levWidth = 0;
                flag = true;
                continue;
            }
            
            levWidth++;

            if (tmp == nullptr) { 
                q.push_back(nullptr);
                q.push_back(nullptr);
            } else { 
                if (tmp->left) q.push_back(tmp->left); 
                else q.push_back(nullptr);
                if (tmp->right) q.push_back(tmp->right);
                else q.push_back(nullptr);
            }
        }
        return width;
    }
#endif
};

int main() {
    /*
          1
         / \
        3   2
       /     \
      5       9 
     /         \
    6           7
     * */
    TreeNode* r =  new TreeNode(1);
    r->left = new TreeNode(3);
    r->right = new TreeNode(2);
    r->left->left = new TreeNode(5);
    r->left->left->left = new TreeNode(6);
    r->right->right = new TreeNode(9);
    r->right->right->right = new TreeNode(7);
    Solution s;
    cout << s.widthOfBinaryTree(r) << endl;


    //                      1
    //                   /      \
    //                  1          1
    //                /   \       /  \
    //               1     1     1    1
    //                       \
    //                        1
    //                     /     \
    //                    2        2
    //                  /   \    /   \
    //                 2     2  2     2
    //                /     /     \     \
    //               2     2       2     2
    TreeNode* nr = new TreeNode(1);
    nr->left = new TreeNode(1);
    nr->right = new TreeNode(1);
    
    nr->left->left = new TreeNode(1);
    nr->left->right = new TreeNode(1);
    nr->right->left = new TreeNode(1);
    nr->right->right = new TreeNode(1);

    nr->left->right->right = new TreeNode(1);
    
    nr->left->right->right->left = new TreeNode(2);
    nr->left->right->right->right = new TreeNode(2);
    nr->left->right->right->left->left = new TreeNode(2);
    nr->left->right->right->left->right = new TreeNode(2);
    nr->left->right->right->right->left = new TreeNode(2);
    nr->left->right->right->right->right = new TreeNode(2);

    nr->left->right->right->left->left->left = new TreeNode(2);
    nr->left->right->right->left->right->left = new TreeNode(2);
    nr->left->right->right->right->left->right= new TreeNode(2);
    nr->left->right->right->right->right->right = new TreeNode(2);
    cout << s.widthOfBinaryTree(nr) << endl;
    return 1;
}
