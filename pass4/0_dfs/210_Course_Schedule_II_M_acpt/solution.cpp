/*
 * 210. Course Schedule II
 *
 * There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

Example 1:

Input: 2, [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
             course 0. So the correct course order is [0,1] .
Example 2:

Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

 * */

#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <unordered_set>

enum class Color {white, grey, black};

class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::pair<int, int>>& prerequisites) {
        std::vector<int>            res;
        std::vector<Color>          v(numCourses, Color::white);      // visited
        std::vector<std::list<int>> edges(numCourses);
        std::vector<int>            indegrees(numCourses, 0);
        std::stack<int>             s;      // order

        for (auto& x : prerequisites) {
            edges[x.first].push_back(x.second);
            indegrees[x.second]++;
        }
        // dfs
        for (uint32_t i = 0; i < numCourses; i++) {
            if (indegrees[i]) { continue; }
            s.push(i);
            v[i] = Color::grey;
            while (!s.empty()) {
                int j = s.top();
                if (edges[j].empty()) {
                    res.push_back(j);    
                    s.pop();
                    v[j] = Color::black;
                } else {
                    int k = edges[j].front();
                    if (v[k] == Color::grey) {
                        res.clear();
                        return res;
                    } else if (v[k] == Color::white) {
                        s.push(k);
                        v[k] = Color::grey;
                    } 
                    edges[j].pop_front();
                }
            }
        }
        // 
        // if there is loop, it is possible that every node in this loop has in-degree > 0, so this loop never got chance to be iterated;
        // so if the result doesn't contain all the nodes, it must be this case, so return empty;
        // e.g. 
        //    _________
        //  \|/        |
        //   1 -> 0 -> 2
        //   3 -> 4
        //
        if (res.size() != numCourses) {
            res.clear();
        }
        return res;
    }
};

void print(std::vector<int> v) {
    for (auto x : v) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}
int main () {
    Solution s;
    std::vector<std::pair<int, int>> v;
    
    v.push_back(std::make_pair(1,0));
    print(s.findOrder(2, v));
#if 0 
    // 
    //  1 -> 0
    // /|\  /|\
    //  3 -> 2
    //
    v.clear();
    v.push_back(std::make_pair(1,0));
    v.push_back(std::make_pair(2,0));
    v.push_back(std::make_pair(3,1));
    v.push_back(std::make_pair(3,2));
    print(s.findOrder(4, v));

    // 1-> 0 -> 3
    //         \|/
    //       -> 2 -> 5 -> 6
    //         \|/  /|\
    //          4 ----
    v.clear();
    v.push_back(std::make_pair(1,0));
    v.push_back(std::make_pair(0,3));
    v.push_back(std::make_pair(0,2));
    v.push_back(std::make_pair(3,2));
    v.push_back(std::make_pair(2,5));
    v.push_back(std::make_pair(4,5));
    v.push_back(std::make_pair(5,6));
    v.push_back(std::make_pair(2,4));
    print(s.findOrder(7, v));
#endif
    // 
    // [[1,0],[2,6],[1,7],[5,1],[6,4],[7,0],[0,5]]
    //
    v.clear();
    v.push_back(std::make_pair(1,0));
    v.push_back(std::make_pair(2,6));
    v.push_back(std::make_pair(1,7));
    v.push_back(std::make_pair(5,1));
    v.push_back(std::make_pair(6,4));
    v.push_back(std::make_pair(7,0));
    v.push_back(std::make_pair(0,5));
    print(s.findOrder(8, v));
    return 1;
}
