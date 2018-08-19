/** 
 * 96. Unique Binary Search Trees
 * Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
 *
 * For example,
 * Given n = 3, there are a total of 5 unique BST's.
 *
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *     3     2     1      1   3      2
 *    /     /       \                 \
 *   2     1         2                 3
 * */ 

//
// Dynamic Programming:
//
// f[i] means the number unique BST with n equals to i;
//
// f[0] = 1;
// f[1] = 1;
// f[2] = 2;
// f[i] = f[i-1] * f[0] +
//        f[i-2] * f[1] +
//        ...
//        f[1] * f[i-2] +
//        f[0] * f[i-1]
//
#include <iostream>
#include <cassert>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        int* f = new int[n+1];
        fill(f, f+n+1, 0);
        f[0] = 1;
        f[1] = 1;
        int i = 2;
        while (i <= n) {
            for (int j = 1; j <= i; j++) {
                f[i] += f[i-j]*f[j-1];
            }
            i++;
        }
        return f[n];
    }
};

int main() {
    Solution s;
    int v = s.numTrees(4);
    cout<<v<<endl;
    assert(v==14);

    v = s.numTrees(5);
    cout<<v<<endl;
    assert(v==42);
}
