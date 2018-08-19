/*
 * 275. H-Index II
 * Given an array of citations (each citation is a non-negative integer) of a researcher, 
 * write a function to compute the researcher's h-index.
 *
 * According to the definition of h-index on Wikipedia: "A scientist has index h if h of 
 * his/her N papers have at least h citations each, and the other N - h papers have no 
 * more than h citations each."
 *
 * For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers 
 * in total and each of them had received 3, 0, 6, 1, 5 citations respectively. 
 * Since the researcher has 3 papers with at least 3 citations each and the remaining two 
 * with no more than 3 citations each, his h-index is 3.
 *
 * Note: If there are several possible values for h, the maximum one is taken as the h-index.
 * Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?
 * */


#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Already sorted
    //
    // h=4
    //     1  4  5  6  7          
    //     x, x, x, x, x
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int start = 0, end = n-1;
        int mid;
        while (start <= end) {
            mid = start + (end - start)/2;   
            if ((n - mid) > citations[mid]) 
                start = mid+1;
            else 
                end = mid-1;
        }
        return n-start;
    }
};

int main() {
    vector<int> v = {0,1,3,5,6};
    Solution s;
    cout << s.hIndex(v) << endl;
    v = {0,0};
    cout << s.hIndex(v) << endl;
    return 1;
}
