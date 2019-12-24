/*
 * 1007. Minimum Domino Rotations For Equal Row
 *
 * In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.  
 * (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the i-th domino, so that A[i] and B[i] swap values.

Return the minimum number of rotations so that all the values in A are the same, 
or all the values in B are the same.

If it cannot be done, return -1.

Example 1:
Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by A and B: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, 
as indicated by the second figure.

Example 2:
Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of values equal.

Note:
1 <= A[i], B[i] <= 6
2 <= A.length == B.length <= 20000
 * */

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int minDominoRotations(std::vector<int>& A, std::vector<int>& B) {
        std::vector<int> a(7, 0);
        std::vector<int> b(7, 0);

        for (auto x : A) { a[x]++; }
        for (auto x : B) { b[x]++; }
        
        int n = A.size();
        int c = 0; bool found = false;
        for (int i = 1; i < 7; i++) {
            if (a[i] + b[i] >= n) {
                c = i; found = true; // no need to found all candidates;
                break;
            }
        }

        if (found == false) return -1;

        // result will be one candidate or two candidates, either case, only need to check one canidate, 
        // because other caididate's result is opposite of each other.
        int ca = 0, cb = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] != c && B[i] != c) return -1;
            if (A[i] == c) ca++;
            if (B[i] == c) cb++;
        }

        return ca > cb? n - ca : n-cb;
    }
};

int main() {
    std::vector<int> A = {2,1,2,4,2,2};
    std::vector<int> B = {5,2,6,2,3,2};

    Solution s;
    std::cout<< s.minDominoRotations(A, B) << std::endl;

    A.clear(); B.clear();
    
    A = {3,5,1,2,3};
    B = {3,6,3,3,4};
    std::cout<< s.minDominoRotations(A, B) << std::endl;

    A = {1,2,3,4,6};
    B = {6,6,6,6,5};
    std::cout<< s.minDominoRotations(A, B) << std::endl;

    A = {2,1,2,4,2,2};
    B = {5,2,6,2,3,2};
    std::cout<< s.minDominoRotations(A, B) << std::endl;

    A = {2,1,1,1,2,2,2,1,1,2};
    B = {1,1,2,1,1,1,1,2,1,1};
    std::cout<< s.minDominoRotations(A, B) << std::endl;
    return 1;
}
