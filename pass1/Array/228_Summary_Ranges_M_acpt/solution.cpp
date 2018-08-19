/*
 * 228. Summary Ranges
 * 
 * Given a sorted integer array without duplicates, return the summary of its ranges.
 * For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
 * */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
    // improve: use binary search
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int n = nums.size();
        ostringstream o;
        for (int i = 0, i0 = 0; i < n; i++) {
            if (i == n-1 || nums[i] + 1 < nums[i+1]) {
                o << nums[i0];
                if (i>i0) o << "->" << nums[i];
                res.push_back(o.str());
                o.str("");
                i0 = i + 1;
            }
        }
        return res;
    }
};

int main() {
    vector<int> v = {0,1,2,4,5,7};
    Solution s;
    vector<string> out = s.summaryRanges(v);
    for (auto x:out)
        cout << x << ",";
    cout << endl;
    return 1;
}
