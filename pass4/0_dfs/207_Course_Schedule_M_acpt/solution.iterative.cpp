/*
 * 207. Course Schedule
 * 
 * There are a total of n courses you have to take, labeled from 0 to n-1.  
 * Some courses may have prerequisites, for example to take course 0 you have to first take course 1, 
 * which is expressed as a pair: [0,1]

 Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

Example 1:

Input: 2, [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

 * */

#include <iostream>
#include <list>
#include <unordered_map>
#include <stack>
#include <vector>
#include <cassert>

// 
// white: not visited;
// grey: being visited;
// black: already visited;
//
enum class Color { white, grey, black };

class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::pair<int, int>>& prerequisites) {
        std::unordered_map<int, std::list<int>>  m;
        std::vector<Color>  v(numCourses, Color::white);
        std::stack<int>     s;    // stack for dfs
        for (auto& x : prerequisites) {
            m[x.first].push_back(x.second);
        }
        for (uint32_t i = 0; i < numCourses; i++) {
            if (v[i] == Color::white) {
                s.push(i);
                v[i] = Color::grey;
                while (!s.empty()) {
                    int j = s.top();
                    int k = -1;
                    if (m.find(j) == m.end()) {
                        v[j] = Color::black;
                        s.pop();
                        continue;
                    } else {
                        k = m[j].front();
                    }

                    if (v[k] == Color::grey) {
                        return false;
                    } else if (v[k] == Color::white){
                        v[k] = Color::grey;
                        s.push(k);
                    }
                     
                    m[j].pop_front();

                    if (m[j].empty()) {
                        m.erase(j);
                    }
                }
            } 
            // assert(v[i] != Color::grey);
        }
        return true;
    }
};

int main() {
    Solution s;
    std::vector<std::pair<int, int>> v;
#if 0
    v.push_back(std::make_pair(0,1));
    v.push_back(std::make_pair(1,2));
    v.push_back(std::make_pair(2,3));
    v.push_back(std::make_pair(3,1));
    std::cout << s.canFinish(4,v) << std::endl;
#endif
    v.clear();
    v.push_back(std::make_pair(0,1));
    v.push_back(std::make_pair(1,2));
    v.push_back(std::make_pair(2,3));
    v.push_back(std::make_pair(4,5));
    v.push_back(std::make_pair(5,1));
    v.push_back(std::make_pair(5,7));
    v.push_back(std::make_pair(6,4));
    v.push_back(std::make_pair(7,6));
    std::cout << s.canFinish(8,v) << std::endl;
    return 1;
}
