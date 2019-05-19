/*
 * 895. Maximum Frequency Stack
 *
 * Implement FreqStack, a class which simulates the operation of a stack-like data structure.

FreqStack has two functions:

push(int x), which pushes an integer x onto the stack.
pop(), which removes and returns the most frequent element in the stack.
If there is a tie for most frequent element, the element closest to the top of the stack is removed and returned.


Example 1:

Input:
["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],
[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
Output: [null,null,null,null,null,null,null,5,7,5,4]
Explanation:
After making six .push operations, the stack is [5,7,5,7,4,5] from bottom to top.  Then:

pop() -> returns 5, as 5 is the most frequent.
The stack becomes [5,7,5,7,4].

pop() -> returns 7, as 5 and 7 is the most frequent, but 7 is closest to the top.
The stack becomes [5,7,5,4].

pop() -> returns 5.
The stack becomes [5,7,4].

pop() -> returns 4.
The stack becomes [5,7].


Note:

Calls to FreqStack.push(int x) will be such that 0 <= x <= 10^9.
It is guaranteed that FreqStack.pop() won't be called if the stack has zero elements.
The total number of FreqStack.push calls will not exceed 10000 in a single test case.
The total number of FreqStack.pop calls will not exceed 10000 in a single test case.
The total number of FreqStack.push and FreqStack.pop calls will not exceed 150000 across all test cases.
 * */


// push:
// double linked list, each element is inserted into the begining.
// max heap: key is freqency of each element, and its related element;
// map: element to its freqency;
//
// pop:
// from the begining of the double linked list;
// if map[elemnent] == maxheap.front().first; then this is the element we needed.
//      map[element] --;
//      maxheap.pop();
//      mapheap.insert(element, map[element]) // add the element back to the maxheap
// else go to next node in the double linked list;
//

#include <iostream>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <unordered_set>

class FreqStack {
public:
    FreqStack() { }
    void push(int x) {
        // 1. push x to deque;
        m_deque.emplace_front(x);
        // 2. update x's occurences in m_map
        m_map[x]++;
        // 3. update x in multimap
        if (m_map[x] > 1) {
            // 3.a if x has been inserted to multimap before, first remove it from its previous num_of_occurrences;
            auto range = m_multimap.equal_range(m_map[x] - 1);
            for (auto it = range.first; it != range.second; it++) {
                if (it->second == x) {
                    // Note: no need to update maxheap even though currently x's occurrences is the max one in heap (say x is increasing from 5 to 6 with this push), 
                    // because we are doing push, and x's occurences will eventually drop to 5 when doing pop();
                    // We only need to remove the top of the maxheap when we are doing pop()
                    m_multimap.erase(it);
                    break;
                }
            }
        }
        // 4. insert x's num_of_occurences into max_heap, if the number already exists, the maxheap should ignore this insert;
        if (m_set.find(m_map[x]) == m_set.end()) {
            // m_max_heap should never have duplicate keys;
            m_max_heap.push(m_map[x]);
            m_set.insert(m_map[x]);
        }
        // 3.b insert x to new place;
        m_multimap.insert(std::make_pair(m_map[x], x));
    }
    int pop() {
        int res = 0;
        for (auto it = m_deque.begin(); it != m_deque.end(); it++) {
            if (m_max_heap.top() == m_map[*it]) {
                // the element in deque has the num_of_occurences equal to the one on top of maxheap;
                res = *it;
                // 1. remove it from deque;
                m_deque.erase(it);
                //assert(m_map[res] > 0);
                // 2. update m_map
                // It is okay to decrease m_map[res] to 0 if res doesn't exist anymore;
                m_map[res]--;
                // 3. remove res from its original num_of_occurences in multimap;
                auto range = m_multimap.equal_range(m_max_heap.top());
                for (auto it = range.first; it != range.second; it++) {
                    if (it->second == res) {
                        m_multimap.erase(it);
                        break;
                    }
                }
                // 4. update the max heap;
                // 4.a first, add the decreased num_of_occurences into the heap
                if ((m_map[res] > 0) && (m_set.find(m_map[res]) == m_set.end())) { 
                    m_set.insert(m_map[res]);
                    m_max_heap.push(m_map[res]);
                }
                // 4.b if this is the last element of the max num_of_occurences being poped, remove the top value in the heap;
                if (m_multimap.count(m_max_heap.top()) == 0)  {
                    // remove it from the set;
                    m_set.erase(m_max_heap.top());
                    // no element left in this num_of_occurences, remove the top element in maxheap;
                    m_max_heap.pop();
                }
                m_multimap.insert(std::make_pair(m_map[res], res));
                break;
            }
        } 
        return res;
    }

private:
    std::unordered_multimap<int, int>   m_multimap; // multimap of num_of_occurences ==> list of elements with same # of occurrences;
    std::unordered_map<int, int>        m_map;      // map of elements ==> # of occurences;
    std::deque<int>                     m_deque;    // deque of pushed element 
    std::priority_queue<int>            m_max_heap; // by default, it is maxheap
    std::unordered_set<int>             m_set;      // whether num_of_occurrences has been added to max_heap (only allow unique keys in max heap)
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack obj = new FreqStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 */

void print_vec(std::vector<int>& o) {
    for (auto x: o) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}

int main() {
    FreqStack s;
    std::vector<int> o;
    s.push(5);
    s.push(7);
    s.push(5);
    s.push(7);
    s.push(4);
    s.push(5);
    
    // [5,7,5,7,4,5]
    // 5, [5,7,5,7,4]
    o.push_back(s.pop()); 
    // 7, [5,7,5,4]
    o.push_back(s.pop()); 
    // 5, [5,7,4]
    o.push_back(s.pop()); 
    // 4, [5,7]
    o.push_back(s.pop()); 
    // 7, [5]
    o.push_back(s.pop()); 
    // 5
    o.push_back(s.pop()); 
    print_vec(o);

    o.clear();
    
    FreqStack s2;
    //[5],[1],[2],[5],[5],[5],[1],[6],[1]
    s2.push(5);
    s2.push(1);
    s2.push(2);
    s2.push(5);
    s2.push(5);
    s2.push(5);
    s2.push(1);
    s2.push(6);
    s2.push(1);

    o.push_back(s2.pop());
    o.push_back(s2.pop());
    o.push_back(s2.pop());
    o.push_back(s2.pop());
    o.push_back(s2.pop());
    o.push_back(s2.pop());
    o.push_back(s2.pop());
    o.push_back(s2.pop());
    o.push_back(s2.pop());

    // [5,5,1,5,1,5,6,2,1,5]
    print_vec(o);

    return 0;
}
