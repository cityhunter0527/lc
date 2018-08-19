/*
 * 718. Maximum Length of Repeated Subarray
 *
 * Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.
 *
 * Example 1:
 * Input:
 * A: [1,2,3,2,1]
 * B: [3,2,1,4,7]
 * 
 * Output: 3
 * Explanation: 
 * The repeated subarray with maximum length is [3, 2, 1].
 * 
 * Note:
 *  1 <= len(A), len(B) <= 1000
 *  0 <= A[i], B[i] < 100
 *
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 
    // Dynamic Programming
    // f[i][j]: len of repeated subarray starting from A[i] and B[j]
    // f[i][j] = f[i+1][j+1] + 1;   if A[i] == B[j]
    // 
    // Then result is max of all f[i][j];
    //
    int findLength(vector<int>& A, vector<int>& B) {
        vector<vector<int>> f(A.size()+1, vector<int>(B.size()+1, 0));
        int ans = 0;
        for (int i = A.size()-1; i >= 0; i--) {
            for (int j = B.size()-1; j >= 0; j--) {
                if (A[i] == B[j])
                    f[i][j] = f[i+1][j+1] + 1;
                if (ans < f[i][j]) ans = f[i][j];
            }
        }
        return ans;
    }
};

int main() {
    vector<int> A = {1,2,3,2,1};
    vector<int> B = {3,2,1,4,7};
    Solution s;
    cout << s.findLength(A, B) << endl;
    return 1;
}
