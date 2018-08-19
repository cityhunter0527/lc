/*
In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair {u, v} with u < v, that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge {u, v} should be in the same format, with u < v.

Example 1:
Input: {{1,2}, {1,3}, {2,3}}
Output: {2,3}
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}}
Output: {1,4}
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly the graph is an undirected graph. For the directed graph follow up please see Redundant Connection II). We apologize for any inconvenience caused.
*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Solution {
public:
    bool dfs (vector<list<int>>& tree, int edgeFrom, int edgeTo, vector<bool>& f) {
        f[edgeFrom] = true;

        for (auto y:tree[edgeFrom]) {
            if (f[y]) continue;
            
            f[y] = true;

            if (y == edgeTo) return true;
            else {
                if(dfs(tree, y, edgeTo, f))
                    return true;
            }
        }

        return false;
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<list<int>> tree(1001);
        vector<int> res(2);
        vector<bool> f(1001, false);
        for (auto x:edges) {
            fill(f.begin(), f.end(), false);
            if (dfs(tree, x[0], x[1], f)) {
                res[0] = x[0];
                res[1] = x[1];
                break;
            } else {
                tree[x[0]].push_back(x[1]);
                tree[x[1]].push_back(x[0]);
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> a(1000, vector<int>(2));
    Solution s;

    // 
    // {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    //
    //  5- 1 - 2
    //     |   |
    //     4 - 3
    //
    // out: {1,4}
    //
    a = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    vector<int> res = s.findRedundantConnection(a);
    cout << "[" << res[0] << ", " << res[1] << "]" << endl;
    
    // 
    // {{1,4},{3,4},{1,3},{1,2},{4,5}}
    //   
    //                     1 - 2
    //                   /   \
    //                  4  -  3
    //                  |
    //                  5
    // out: {1,3}                    
    //
    a = {{1,4}, {3,4}, {1,3}, {1,2}, {4,5}};
    res = s.findRedundantConnection(a);
    cout << "[" << res[0] << ", " << res[1] << "]" << endl;
    
    // Input:
    // {{3,4},{1,2},{2,4},{3,5},{2,5}}
    //         5 - 3 - 4
    //           \ |
    //         1 - 2
    //
    // Expected:
    // {2,5}
    a = {{3,4}, {1,2}, {2,4}, {3,5}, {2,5}};
    res = s.findRedundantConnection(a);
    cout << "[" << res[0] << ", " << res[1] << "]" << endl;
    return 1;
}
