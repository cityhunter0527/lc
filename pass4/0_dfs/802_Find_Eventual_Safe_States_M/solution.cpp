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
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph) {
        uint32_t num_nodes = graph.size();
        std::vector<int> res;
        std::vector<Visited> v(num_nodes, Visited::white);
        for (uint32_t i = 0; i < num_nodes; i++) {
            if (dfs(i, graph, v)) {
                res.push_back(i);
            }
        }
        return res;
    }

private:
    // true: no loop
    // false: loop
    //
    // white: never visited;
    // grey: "being visited" 
    // black: visited and definitely no loop
    //
    bool dfs(int n, std::vector<std::vector<int>>& g, std::vector<Visited>& v) {
        if (v[n] != Visited::white) {
            // there is no loop if n's color is black;
            return v[n] == Visited::black;
        }
        v[n] = Visited::grey;
        for (auto x : g[n]) {
            if (v[x] == Visited::black) {
                // no need to keep dfs with node x;
                continue;
            } else if (v[x] == Visited::grey || !dfs(x, g, v)) {
                // if this node is grey or it is not visited yet (white), but this node has loop;
                return false;
            }
        }
        v[n] = Visited::black;
        return true;
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
    // result: 2, 4, 5, 6
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
    // result: 5
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
    // result: 4
    o = s.eventualSafeNodes(g);
    print(o);

    return 1;
}
