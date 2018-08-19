/*
 * Give two linked list:
 * L1:  node->node->node -> ... -> null
 * L2:  node->node->node -> ... -> null
 * Return the intersection node, if not intersect, return null.
 *
 * HINT: need to consider L1 or L2 has loops.
 * Space complexity should be O(1), 
 * */


#include <iostream>
#include <assert.h>
using namespace std;

struct LinkNode {
    int val;
    LinkNode* next;
    LinkNode(int x): val(x), next(nullptr) {}
};

LinkNode* hasLoop(LinkNode* l);
int getNonLoopLen(LinkNode* n);
LinkNode* getIntersectNode(LinkNode* l1, int n1, LinkNode* l2, int n2);


int getLoopSteps(LinkNode* n, LinkNode* refNode = nullptr) {
    LinkNode* p1 = n, *p2 = n;
    int steps = 0;
    while (p2 && p2->next) {
        steps++;
        if (p1 == p2->next || p1 == p2->next->next || p1 == refNode) 
            break;
        p1 = p1->next;
        p2 = p2->next->next;
    }
    if (p1 == refNode)
        return steps;
    while (refNode && p1 != refNode) {
        p1 = p1->next;
        steps++;
    }
    return steps;
}


//                 L1   L2     Intersect
//  Has Loop?      N    N        Yes
//                 Y    Y        Yes
//                 Y    N        No
//                 N    Y        No
//
LinkNode* intersect(LinkNode* l1, LinkNode* l2) {
    LinkNode* l1Loop = hasLoop(l1);
    LinkNode* l2Loop = hasLoop(l2);
    int n1, n2;
    if ((l1Loop && !l2Loop) || (!l1Loop && l2Loop)) {
        // one has loop, the other has no loop, 
        // definitely couldn't intersect
        return nullptr;
    }

    if (l1Loop && l2Loop) {
        // both l1 and l2 have loop
        // get steps from l1 to l1Loop
        n1 = getLoopSteps(l1);
        // get steps from l2 to l1Loop
        n2 = getLoopSteps(l2, l1Loop);
    } else if (!l1Loop && !l2Loop) {
        // neigher l1 nor l2 has loop
        n1 = getNonLoopLen(l1);
        n2 = getNonLoopLen(l2);
    }
    return getIntersectNode(l1, n1, l2, n2);
}
LinkNode* getIntersectNode(LinkNode* l1, int n1, LinkNode* l2, int n2){
    LinkNode* t1, *t2;
    int d;
    if (n1 > n2) {
        d = n1 - n2;
        t1 = l1;
        t2 = l2;
    } else {
        d = n2 - n1;
        t1 = l2;
        t2 = l1;
    }

    while (d--) t1 = t1->next;
    while (t1 && t2) {
        if (t1 == t2) return t1;
        t1 = t1->next;
        t2 = t2->next;
    }
    // Should never come here;
    assert (0);
}

int getNonLoopLen(LinkNode* n) {
    int len = 0;
    while (n) {
        n = n->next;
        len++;
    }
    return len;
}

LinkNode* hasLoop(LinkNode* l) {
    LinkNode* p1 = l, *p2 = l;
    while (p2 && p2->next) {
        if (p1 == p2->next || p1 == p2->next->next) 
            return p1;
        p1 = p1->next;
        p2 = p2->next->next;
    }
    return nullptr;
}

int main() {
    LinkNode* l1 = new LinkNode(1);
    l1->next = new LinkNode(2);
    l1->next->next = new LinkNode(3);
    l1->next->next->next = new LinkNode(4);
    l1->next->next->next->next = new LinkNode(5);
    l1->next->next->next->next->next = new LinkNode(6);
    l1->next->next->next->next->next->next = new LinkNode(7);
    l1->next->next->next->next->next->next->next = new LinkNode(8);
    l1->next->next->next->next->next->next->next->next = new LinkNode(9);
    l1->next->next->next->next->next->next->next->next->next = new LinkNode(10);
    l1->next->next->next->next->next->next->next->next->next->next = new LinkNode(11);
    // make loop
    l1->next->next->next->next->next->next->next->next->next->next->next = l1->next->next->next->next->next;

    LinkNode* l2 = new LinkNode(21);
    l2->next = new LinkNode(22);
    l2->next->next = new LinkNode(23);
    l2->next->next->next = new LinkNode(24);
    l2->next->next->next->next = new LinkNode(25);
    l2->next->next->next->next->next = new LinkNode(26);
    l2->next->next->next->next->next->next = new LinkNode(27);
    // make intersect
    l2->next->next->next->next->next->next->next = l1->next->next->next->next;

    LinkNode* ins = intersect(l1, l2);
    cout << ins->val << endl;
    
    l2->next->next->next->next->next->next->next = l1->next->next->next;
    l1->next->next->next->next->next->next->next->next->next->next->next = nullptr;
    ins = intersect(l1, l2);
    cout << ins->val << endl;
    return 1;
}
