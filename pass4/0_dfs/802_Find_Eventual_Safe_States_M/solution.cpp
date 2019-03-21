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
#include <vector>


enum class Visited { white, grey, black };

class Solution {
public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph) {
        std::vector<int> res;
        std::stack<int> s;
        uint32_t num_nodes = graph.size();
        std::vector<Visited> v(num_nodes, Visited::white);
        
        uint32_t start = 0, cur = start;
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
                    // we've got a loop and pop up all the nodes in stack (which forms the loop) 
                    // mark all the nodes as visited
                    while (!s.empty()) {
                        v[s.top()] = Visited::black;
                        s.pop();
                    }
                    break;
                } else {
                    // black
                    res.push_back(i);
                    continue;
                }
            }

            if (!dfs) {
                // all the connected nodes with cur have been visited and there is no loop,
                // add this node to return result;
                res.push_back(cur);
                s.pop();
            }

            if (s.empty()) {
                start++;
                if (start < num_nodes) {
                    // keep going
                    s.push(start);
                } else {
                    // reach last node, we are done
                    break;
                }
            }

        }
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
    std::vector<std::vector<int>> g;
    std::vector<int> v;
    v = {1,2};
    g.push_back(v);
    v = {2,3};
    g.push_back(v);
    v = {5};
    g.push_back(v);
    v = {0};
    g.push_back(v);
    v = {5};
    g.push_back(v);

    g.push_back({});
    g.push_back({});

    Solution s;
    std::vector<int> o = s.eventualSafeNodes(g);
    
    print(o);
    

    return 1;
}
