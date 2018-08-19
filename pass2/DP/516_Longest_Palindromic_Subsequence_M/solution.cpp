/*
 * 516. Longest Palindromic Subsequence
 *
 * Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.
 *
 * Example 1:
 * Input:
 *
 * "bbbab"
 * Output:
 * 4
 * One possible longest palindromic subsequence is "bbbb".
 * Example 2:
 * Input:
 *
 * "cbbd"
 * Output:
 * 2
 * One possible longest palindromic subsequence is "bb".
 * */

class Solution {
public:
    // 
    // d[i][j]: the length of longest palindromic subsequence between [i, j];
    // if s[i] == s[j]: 
    //    d[i][j] = d[i+1][j-1] + 2 
    // else
    //    d[i][j] = max(d[i][j-1], d[i+1][j]);
    //
    // start:
    //    d[i][i] = 1; 0<= i < s.length()
    //
    // Result:
    //    d[0][s.length()-1]
    // 
    int longestPalindromeSubseq(string s) {
        
    }
};

int main () {
    return 1;
}
