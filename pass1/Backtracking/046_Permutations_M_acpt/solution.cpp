/* 
 * 46. Permutations
 *
 * Given a collection of distinct numbers, return all possible permutations.
 *
 * For example,
 * [1,2,3] have the following permutations:
 * [
 * [1,2,3],
 * [1,3,2],
 * [2,1,3],
 * [2,3,1],
 * [3,1,2],
 * [3,2,1]
 * ]
 * */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
// Algorithm: Backtracking
class Solution {
public:
    vector<vector<int>> res; // solution vector
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.size() == 0) return res;
        generate(nums);
        return res;
    }

    void generate(vector<int>& nums) {
        vector<int> a(nums.size()+1); // one solution
        bt_dfs(a, 0, nums);
    }

    // Backtracking DFS
    void bt_dfs(vector<int>& a, int k, vector<int>& nums) {
        vector<int> c(nums.size());
        int nCandidates;

        if (is_a_solution(a, k, nums))
            process_solution(a, k, nums);
        else {
            k++;
            construct_candidates(a, k, nums, c, nCandidates);
            for (int i = 0; i < nCandidates; i++) {
                a[k] = c[i];
                bt_dfs(a, k, nums);
            }
        }
    }

    bool is_a_solution(vector<int>& a, int k, vector<int>& nums) {
        return (k == nums.size());
    }

    void construct_candidates(vector<int>& a, int k, vector<int>& nums, vector<int>& c, int& nCandidates) {
        int i;
        unordered_set<int> in_perm(nums.size()); // implicitely means all positions not seletected yet.

        // mark the previous k-1 posistions 
        for (i = 1; i < k; i++) 
            in_perm.insert(a[i]); 

        nCandidates = 0;

        for (i = 0; i < nums.size(); i++) {
            // for each element, if it hasn't been selected yet, put it into candidates
            if (in_perm.find(nums[i]) == in_perm.end()) {
                c[nCandidates] = nums[i];
                nCandidates++;
            }
        }
    }
    
    void process_solution(vector<int>& a, int k, vector<int>& nums) {
        vector<int> temp;
        for (int i = 1; i < a.size(); i++)
            temp.push_back(a[i]);
        res.push_back(temp);
    }
};

int main () {
    vector<int> v = {1,2,3};
    vector<vector<int>> res;
    Solution s;
    res = s.permute(v);

    for (auto x : res) {
        cout << "[";
        for (auto y : x) {
            cout<< y << ",";
        }
        cout<<"]"<<endl; 
    }
    return 1;
}
