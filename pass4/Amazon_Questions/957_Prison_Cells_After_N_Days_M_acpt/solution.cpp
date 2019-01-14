/*
 * 957. Prison Cells After N Days
 * There are 8 prison cells in a row, and each cell is either occupied or vacant.
 *
 * Each day, whether the cell is occupied or vacant changes according to the following rules:
 *
 * If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
 * Otherwise, it becomes vacant.
 * (Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.)
 *
 * We describe the current state of the prison in the following way: cells[i] == 1 if the i-th cell is occupied, else cells[i] == 0.
 *
 * Given the initial state of the prison, return the state of the prison after N days (and N such changes described above.)
 *
 *  
 *
 *  Example 1:
 *
 *  Input: cells = [0,1,0,1,1,0,0,1], N = 7
 *  Output: [0,0,1,1,0,0,0,0]
 *  Explanation: 
 *  The following table summarizes the state of the prison on each day:
 *  Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
 *  Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
 *  Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
 *  Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
 *  Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
 *  Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
 *  Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
 *  Day 7: [0, 0, 1, 1, 0, 0, 0, 0]  // <<< answer
 *  Day 8: [0, 0, 0, 0, 0, 1, 1, 0]
 *  Day 9: [0, 1, 1, 1, 0, 0, 0, 0]
 *  Day10: [0, 0, 1, 0, 0, 1, 1, 0]
 *  Day11: [0, 0, 1, 0, 0, 0, 0, 0]
 *  Day12: [0, 0, 1, 0, 1, 1, 1, 0]
 *  Day13: [0, 0, 1, 1, 0, 1, 0, 0]
 *  Day14: [0, 0, 0, 0, 1, 1, 0, 0]
 *
 *  Example 2:
 *
 *  Input: cells = [1,0,0,1,0,0,1,0], N = 1000000000
 *  Output: [0,0,1,1,1,1,1,0]
 *   
 *
 *   Note:
 *   cells.length == 8
 *   cells[i] is in {0, 1}
 *   1 <= N <= 10^9
 * */

#include <vector>
#include <iostream>
#include <map>
#include <cassert>

class Solution {
    void next_state(std::vector<int>& cells) {
        std::vector<int> tmp(8);
        std::fill(tmp.begin(), tmp.end(), 0);
        for (int i = 1; i < 7; i++) {
            if (cells[i-1] == cells[i+1]) 
                tmp[i] = 1;
        }
        cells = tmp;
    }
    
public:
    int convert(std::vector<int>& cells) {
        // 
        // example: {0,0,1,0,1,1,0,0} wll be converted to 54 in dec
        //
        int sum = 0;
        for (int i = 0; i < 8; i++) {
            sum <<= 1;   
            if (cells[i]) sum += 1;
        }
        return sum;
    }

    // 
    // Solution:
    // Since cells.length == 8, there are total 256 possible states;
    // And soon they will repeat. 
    // When it repeats, we can just get the state based on the left days;
    //
    std::vector<int> prisonAfterNDays(std::vector<int>& cells, int N) {
        std::vector<std::vector<int>>       states; // stores all the states we've currently which are all unique (not repeated yet)
        std::map<int, int>                  m;      // stores whether the state has occurred already; map can be replaced with unordered_set, no need to store the index in states;
                                                    // leetcode shows using map is even faster than unordered_set, which is not reasonble;
        for (int i = 0; i < N; i++) {
            next_state(cells); 
            int s = convert(cells);            // convert the states to a integer so that we can hash it;
            if (m.find(s) == m.end()) {
                states.push_back(cells);
                m[s] = states.size()-1;
            } else {
                // state already occurred.
                // state repeat must occur from the beginning;
                //assert(m[s] == 0);
                return states[(N-i-1) % states.size()];
            }
        }
        return cells;
    }
};

void print_vec(std::vector<int>& v) {
    for (auto& x : v)
        std::cout << x << ", ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> v = {0,1,0,1,1,0,0,1};
    Solution s;
    //std::cout << s.convert(v);

    std::vector<int> o = s.prisonAfterNDays(v, 7);
    print_vec(o);
#if 0
    o.clear();
    v = {0,1,0,1,1,0,0,1};
    o = s.prisonAfterNDays(v, 300);
    print_vec(o);
#endif   
#if 1
    o.clear();
    v = {1,0,0,1,0,0,1,0};
    o = s.prisonAfterNDays(v, 1000000000);
    print_vec(o);
#endif
    return 0;
}


