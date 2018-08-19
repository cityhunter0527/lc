/*
 * 138. Copy List with Random Pointer
 *
 * A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
 * Return a deep copy of the list.
 * */

#include <iostream>
#include <unordered_map>
#include <assert.h>
using namespace std;
/** *  * Definition for singly-linked list with a random pointer.*/
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    // For each node in the RandomListNode:
    RandomListNode *copyRandomList (RandomListNode *head) {
        if (head == nullptr) return head;
        RandomListNode* cpHead = new RandomListNode(head->label);
        RandomListNode* p = cpHead, *q = head;
        unordered_map<RandomListNode*, RandomListNode*> m;
        m[head] = cpHead;
        while (q->next) {
            p->next = new RandomListNode(q->next->label);
            m[q->next] = p->next;
            q = q->next;
            p = p->next;
        }
        p = cpHead; q = head;
        while (q) {
            if (q->random == nullptr)
                p->random = nullptr;
            else {
                assert (m.find(q->random) != m.end());
                p->random = m[q->random];
            }
            q = q->next;
            p = p->next;
        }
        return cpHead;
    }
};

int main() {
    RandomListNode* h = new RandomListNode(1);
    h->next = new RandomListNode(2);
    h->random = h;
    h->next->next = new RandomListNode(3);
    h->next->random = h;
    Solution s;
    RandomListNode* newH = s.copyRandomList(h);
    return 1;
}
