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
#include <stack>

class FreqStack {
public:
    FreqStack() { 
        m_max_freq = 0;
    }

    void push(int x) {
        if (m_map.find(x) == m_map.end())    m_map[x] = 1;
        else m_map[x]++;

        if (m_max_freq < m_map[x]) m_max_freq = m_map[x];
        
        // Note: need to keep x's original freq in m_map_stack because we need this information 
        // to get the next most recent in this level of freq;
        // e.g. when 5 is poped, and there is no freq:4 in the m_map_stack[4], we fallback to m_map_stack[3] 
        // and the elements being pushed already are in the most recent seqence;
        m_map_stack[m_map[x]].push(x);
    }

    int pop() {
        int res = m_map_stack[m_max_freq].top();
        m_map_stack[m_max_freq].pop();
        m_map[res]--;
        if (m_map_stack[m_max_freq].size() == 0)
            m_max_freq--; // m_max_freq must be liner because m_max_freq was increased one by one from some element, there must be an element in this freq waiting in the stack;
        return res;
    }
private:
    std::map<int, int>                  m_map;       // map from element to its frequency
    std::map<int, std::stack<int>>      m_map_stack; // map from freqency to a stack of elements;
    int                                 m_max_freq;  // current max freq;
};

void print_vec(std::vector<int>& o) {
    for (auto x: o) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}

int main() {
    FreqStack s;
    std::vector<int> o;
    s.push(5); s.push(7); s.push(5); s.push(7); s.push(4); s.push(5);
    
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
