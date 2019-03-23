/*
 * 802. Find Eventual Safe States
 * In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  
 * If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop. 
 * Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  
 * More specifically, there exists a natural number K so that for any choice of where to walk, we must 
 * have stopped at a terminal node in less than K steps.  
 * 
 * Which nodes are eventually safe?  Return them as an array in sorted order.  
 * 
 * The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  
 * The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Here is a diagram of the above graph.

Illustration of graph
0: [1,2]
1: [2,3]
2: [5]
3: [0]
4: [5]

Note:

graph will have length at most 10000.
The number of edges in the graph will not exceed 32000.
Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].
* */

#include <iostream>
#include <stack>
#include <deque>
#include <vector>

enum class Visited { white, grey, black };

class Solution {
public:
    // white: not visited yet;
    // grey: being visited;
    // black: already visited (could be in loop or not in loop)
    // that's why we need vector loop to indicate whether a node in black is in loop or not;
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph) {
        std::vector<int> res;
        std::stack<int> s;
        uint32_t num_nodes = graph.size();
        std::vector<Visited> v(num_nodes, Visited::white);
        
        uint32_t start = 0, cur = start;
        v[0] = Visited::grey;
        s.push(start); 
        while (!s.empty()) {
            cur = s.top();
            bool dfs = false;
            for (uint32_t i = 0 ; i < graph[cur].size(); i++) {
                uint32_t n = graph[cur][i];
                if (v[n] == Visited::white) {
                    v[n] = Visited::grey;
                    s.push(n);
                    // break out of the for loop to do dfs;
                    dfs = true;
                    break;
                } else if (v[n] == Visited::grey) {
                    while (!s.empty()) s.pop();
                    dfs = true;
                    break;
                }
                // for black, we just keep skip dfs with n and move to next 
            }

            if (!dfs) {
                res.push_back(cur);
                // mark this node as visited;
                v[cur] = Visited::black;
                // pop this node to keep dfs
                s.pop();
            }
            
            // it is possible s can be empty, meaning some node are not connected with others, so dfs can not visit such node;
            if (s.empty()) {
                // pick up an un-visited node;
                while (start < num_nodes && v[start] != Visited::white) start++; 
                if (start < num_nodes) {
                    // keep going with dfs
                    s.push(start);
                    v[start] = Visited::grey;
                } 
            }
        }

        // sort the result before return;
        std::sort(res.begin(), res.end());
        return res;
    }
};

void print(std::vector<int>& o) {

    for (auto& x:o) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}

// Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
// Output: [2,4,5,6]
int main() {
    Solution s;
    std::vector<std::vector<int>> g;
    std::vector<int> v;
    std::vector<int> o;
#if 1
    g.push_back({1,2});
    g.push_back({2,3});
    g.push_back({5});
    g.push_back({0});
    g.push_back({5});
    g.push_back({});
    g.push_back({});
    o = s.eventualSafeNodes(g);
    print(o);
    o.clear();
    g.clear();

    g.push_back({1});
    g.push_back({3});
    g.push_back({3,5});
    g.push_back({0,4});
    g.push_back({2});
    g.push_back({});
    o = s.eventualSafeNodes(g);
    print(o);
#endif 
    o.clear();
    g.clear();
    g.push_back({0});
    g.push_back({2,3,4});
    g.push_back({3,4});
    g.push_back({0,4});
    g.push_back({});
    o = s.eventualSafeNodes(g);
    print(o);

    return 1;
}
