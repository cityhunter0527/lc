/*
 * Merge Two Balanced Binary Search Trees
 *
 * You are given two balanced binary search trees e.g., AVL or Red Black Tree. 
 * Write a function that merges the two given balanced BSTs into a balanced binary search tree. 
 * Let there be m elements in first tree and n elements in the other tree. 
 *
 * Your merge function should take O(m+n) time.
 *
 * Method 2 (Merge Inorder Traversals) 
 * 1) Do inorder traversal of first tree and store the traversal in one temp array arr1[]. This step takes O(m) time.
 * 2) Do inorder traversal of second tree and store the traversal in another temp array arr2[]. This step takes O(n) time.
 * 3) The arrays created in step 1 and 2 are sorted arrays. Merge the two sorted arrays into one array of size m + n. This step takes O(m+n) time.
 * 4) Construct a balanced tree from the merged array using the technique discussed in this post. This step takes O(m+n) time.
 *
 * Time complexity of this method is O(m+n) which is better than method 1. 
 * This method takes O(m+n) time even if the input BSTs are not balanced.
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left; 
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> InOrderTraversalIterative(TreeNode* r) {
        vector<int> result;
        stack<TreeNode*> s;
        TreeNode* p = r;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                result.push_back(p->val);
                p = p->right;   
            }
        }
        return result;
    }

    // Merge two sorted array. 
    // Space Complexity: O(1)
    //
    // http://www.geeksforgeeks.org/merge-two-sorted-arrays-o1-extra-space/
    // The idea is to sort smaller part in a1 and bigger part in a2. 
    // E.g. a1: 1, 3, 5, 7, 9; a2: 2,4,6,8. 
    // After sort: 
    //      a1: 1, 2, 3, 4, 5
    //      a2: 6, 7, 8, 9
    //
    // General Solution: Every round we get a maximum element and put it to end of a2 (back to front). 
    // 1. For each element in a2 (back to front), say it is a2[i]:
    //    a. compare a2[i] with every elment in a1(back to front) and find the smallest element in a1 that is larger than a2[i].
    //       store a1's last element into "last": last = a1[a1.size()-1];
    //       if a1[j] is larger than a2[i], move a1[j] ahead: 
    //                 a1[j+1] = a1[j]; 
    //    b. if a1[j] is smaller than a2[i], 
    //       insert a2 to position j+1 in a1, since a[j+1] has bene moved to a[j+2]
    //       a1[j+1] = a2[i]
    //    c. Store "last" to a2[i];
    //    d. repeat from begining until every element of a2 is visited.
    void MergeTwoSortedArrayO1Space(vector<int>& a1, vector<int>& a2) {
        int m = a1.size(), n = a2.size();
        for (int i = n-1; i >= 0; i--) {
            int j, last = a1[m-1];
            for (j = m-2; j >= 0 && a1[j] > a2[i]; j--) {
                a1[j+1] = a1[j];
            }
            // if found a smallest greater element;
            if (last > a2[i]) {
                a1[j+1] = a2[i];
                a2[i] = last;
            }
        }  
    }

    // Merge two sorted array. 
    // Space Complexity: O(m+n)
    void MergeTwoSortedArray(vector<int>& a1, vector<int>& a2, vector<int>& result) {
        int i = 0, j = 0, k = 0;
        while (i < a1.size() && j < a2.size()) {
            if (a1[i] < a2[j])
                result[k++] = a1[i++];
            else 
                result[k++] = a2[j++];
        }
        if (i < a1.size())
            copy(a1.begin() + i, a1.end(), result.begin() + k);
        else if (j < a2.size())
            copy(a2.begin() + j, a2.end(), result.begin() + k);
    }

    // Convert sorted array to balanced BST
    TreeNode* SortedArrayToBalancedBST(vector<int>& nums, int start, int end) {
        if (start > end) return nullptr;
        int mid = start + (end-start)/2;
        TreeNode* n = new TreeNode(nums[mid]);
        n->left = SortedArrayToBalancedBST(nums, start, mid-1);
        n->right = SortedArrayToBalancedBST(nums, mid+1, end);
        return n;
    }
public: 
    TreeNode* MergeTwoBalancedBST(TreeNode* r1, TreeNode* r2) {
        vector<int> inOrder1, inOrder2, mergedResult;
        inOrder1 = InOrderTraversalIterative(r1);
        inOrder2 = InOrderTraversalIterative(r2);
        mergedResult.resize(inOrder1.size() + inOrder2.size());
        MergeTwoSortedArray(inOrder1, inOrder2, mergedResult);
        return SortedArrayToBalancedBST(mergedResult, 0, mergedResult.size()-1);
    }
};

int main() {
    vector<int> v1 = {2,4,6,8,10,12,14};
    vector<int> v2 = {1, 3, 5, 7, 9};
    Solution s;
    s.MergeTwoSortedArrayO1Space(v1, v2);
    cout << "v1: ";
    for (auto x:v1) cout << x << ",";
    cout << endl;
    cout << "v2: ";
    for (auto x:v2) cout << x << ",";
    cout << endl;
#if 0
    Solution s;
    cout << "Merge Two Balanced BST:" << endl;
    TreeNode* t1 = s.SortedArrayToBalancedBST(v1, 0, v1.size()-1);
    TreeNode* t2 = s.SortedArrayToBalancedBST(v2, 0, v2.size()-1);
    TreeNode* t3 = s.MergeTwoBalancedBST(t1, t2);
    vector<int> ans = s.InOrderTraversalIterative(t3);
    for (auto x:ans) cout << x << ", ";
    cout << endl;
#endif
    return 1;
}
