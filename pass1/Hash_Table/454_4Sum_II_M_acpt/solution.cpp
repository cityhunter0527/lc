/*
 * 454. 4Sum II
 * Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) 
 * there are such that A[i] + B[j] + C[k] + D[l] is zero.
 *
 * To make problem a bit easier, all A, B, C, D have same length of N where 0 <= N <= 500. 
 * All integers are in the range of -2^28 to 2^28 - 1 and the result is guaranteed to be at most 2^31 - 1.
 *
 * Example:
 *
 * Input:
 * A = [ 1, 2]
 * B = [-2,-1]
 * C = [-1, 2]
 * D = [ 0, 2]
 *
 * Output:
 * 2
 *
 * Explanation:
 * The two tuples are:
 * 1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
 * 2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Complexity: O(n^2), 
    // Space: O(1)
    int fourSumCount (vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> m; // first: sum, second: # of occurrence.
        int n = A.size();
        int sum = 0, cnt = 0;
        // Construct hash based on sum of A and B
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <n; j++) {
                sum = A[i] + B[j];
                if (m.find(sum) == m.end()) {
                    m.insert({sum, 1});
                } else 
                   m[sum]++; 
            }
        }
        // re-visit hash based on sum of C and D
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum = -1 * (C[i] + D[j]);
                if (m.find(sum) != m.end()) {
                    cnt += m[sum];  // m[sum] is # of occurence of combination from A and B.
                }
            }
        }
        return cnt;
    }
};

int main() {
    vector<int> A = {1,2};
    vector<int> B = {-2,-1};
    vector<int> C = {-1,2};
    vector<int> D = {0,2};

    Solution s;
    int o = s.fourSumCount(A,B,C,D);
    cout << o << endl;
    return 1;
}
