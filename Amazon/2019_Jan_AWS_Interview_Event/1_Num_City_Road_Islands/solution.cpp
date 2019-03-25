/*
 * Input: 
 * - Given a list of cities and a list of roads.
 *   Each road is connected by two cities.
 *
 * Output:
 * - The number of islands that doesn't connect with each other
 *
 * Example:
 * Input:
 * City List: A, B, C, D, E, F
 * Roads: A-B, B-C, D-E,
 *
 * Output: 3
 *
 * Explaination: 
 * A-B-C is an island, B-C is another island, F is also an island because it connects to no other cities. 
 *
 * Hint:
 * Can you do it in O(n) with DFS?
 * 
 * */

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <list>

class Solution {
public:
    uint32_t num_islands(std::vector<std::string>& cities, std::vector<std::pair<std::string, std::string>>& roads) {
        std::unordered_set<std::string>                         v;
        std::unordered_map<std::string, std::list<std::string>> c;
        uint32_t k = 0;
        // iterate all roads and construt the map;
        for (auto& x : roads) {
            c[x.first].push_back(x.second);
        }
        
        // dfs in O(n) since we only viist each road once;
        for (int n = 0; n < cities.size(); n++) {
            while (n < cities.size() && v.find(cities[n]) != v.end()) { 
                n++;
            }

            if (n >= cities.size()) { 
                return k;
            }

            std::stack<std::string>  s;
            std::string j = cities[n];
            s.push(j);
            k++;
            v.insert(j);
            while (!s.empty()) { 
                std::string t = s.top();
                while (!(c[t].empty())) {
                    auto i = c[t].begin();
                    v.insert(*i);
                    s.push(*i);
                    c[t].pop_front();
                    t = *i;
                }
                s.pop();
                c.erase(t);
            }
        }

        return k;
    }
};

int main() {
    // TODO: how to do O(n) without need to sort cities and no restriction of roads first < second?
    std::vector<std::string> cities = {"A", "B", "C", "D", "E", "F", "G", "H"};
    std::vector<std::pair<std::string, std::string>>  roads;
    // Note: in the below pair, first must be "smaller" second;
    roads.push_back(std::make_pair("A", "B"));
    roads.push_back(std::make_pair("B", "C"));
    roads.push_back(std::make_pair("B", "E"));
    roads.push_back(std::make_pair("B", "Q"));
    roads.push_back(std::make_pair("C", "D"));
    roads.push_back(std::make_pair("E", "P"));
    roads.push_back(std::make_pair("E", "L"));
    roads.push_back(std::make_pair("L", "K"));
    roads.push_back(std::make_pair("L", "M"));
    roads.push_back(std::make_pair("F", "G"));

    Solution s;
    std::cout << s.num_islands(cities, roads) << std::endl;
    return 0;
}
