/*
 * 138. Copy List with Random Pointer
 *
 * A linked list is given such that each node contains an additional random pointer 
 * which could point to any node in the list or null.
 *
 * Return a deep copy of the list.
 * */

#include <iostream>
#include <unordered_map>
using namespace std;

/** *  * Definition for singly-linked list with a random pointer. **/
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) return nullptr;
        unordered_map<RandomListNode*, RandomListNode*>    m;
        RandomListNode* dummyNode = new RandomListNode(0), **p = &(dummyNode->next);
        while (head) {
            if (m.find(head) == m.end()) {
                (*p) = new RandomListNode(head->label);
                m[head] = *p;
            } else {
                *p = m[head];
            }
            if (head->random) { 
                if (m.find(head->random) == m.end()) {
                    (*p)->random = new RandomListNode(head->random->label);
                    m[head->random] = (*p)->random;
                } else {
                    (*p)->random = m[head->random];
                }
            } 
            // if head->random is null, (*p)->random is already init to null;
            head = head->next;
            p = &((*p)->next);
        }

        return dummyNode->next;
    }
};

int main() {
    RandomListNode* r = new RandomListNode(1);
    r->next = new RandomListNode(2);
    r->next->next = new RandomListNode(3);
    r->next->next->next = new RandomListNode(4);
    r->next->next->next->next = new RandomListNode(5);
    
    r->random = r->next->next->next;
    r->next->random = r;
    r->next->next->random = r->next->next->next->next;
    r->next->next->next->random = r->next->next->next;
    r->next->next->next->next->random = r->next->next->next;
    
    Solution s;
    RandomListNode* h = s.copyRandomList(r);
    while (h) {
        cout << h->label << ": "; 
        if (h->random)
            cout << h->random->label;
        else 
            cout << "null"; 
        cout << ", ";
        h = h->next;
    }
    cout << endl;
    return 0;
}
