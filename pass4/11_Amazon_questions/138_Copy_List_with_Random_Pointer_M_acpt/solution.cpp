/*
 * 138. Copy List with Random Pointer
 * A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
 *
 * Return a deep copy of the list.
 * */

#include <map>
#include <iostream>

// Definition for singly-linked list with a random pointer. 
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 };

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        std::map<RandomListNode*, RandomListNode*>      m;  
        RandomListNode* p = head, dummy(0), *q = &dummy;
        while (p) {
            q->next = new RandomListNode(p->label);
            m[p] = q->next;
            p = p->next;
            q = q->next;
        }

        p = head, q = &dummy;
        while (p) {
            // for each node in the list, adjust its corresponding copy list node's random pointer
            if (p->random) {
                // p's copied node is m[p];
                m[p]->random = m[p->random];
            }
            p = p->next;
        }
        return dummy.next;
    }
};

int main() {
    return 0;
}
