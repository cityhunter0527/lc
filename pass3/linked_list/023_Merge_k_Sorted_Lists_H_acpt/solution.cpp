/*
 * 23. Merge k Sorted Lists
 *
 * Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
 * */

#include <iostream>
#include <queue>
using namespace std;

/** Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class mycomp {
public:
    bool operator () (ListNode* l, ListNode* r){
        return l->val > r->val; // greater than which is minHeap
    }

};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // minHeap                       
        // 1. Construct minHead for every node in lists.
        // 2. Create empty list with dummyNode. tail = &(dummy->next);
        // 3. *tail = root; tail = &((*tail)->next)
        // 4. Push root->next into minHeadp. 
        //    If root->next is null, go to step 3.
        // 5. repeat 3~5 until there is no node in minHeap
        // Complexity O(n*k*log k) n: total nodes in all lists, K: number of lists
        priority_queue<ListNode*, vector<ListNode*>, mycomp> minheap;
        ListNode* dummyNode = new ListNode(0);
        for (vector<ListNode*>::iterator it = lists.begin(); it != lists.end(); it++) {
            if (*it != nullptr)
                minheap.push(*it);
        }
        ListNode* root = nullptr, **tail = &(dummyNode->next);
        while(!minheap.empty()) {
            root = minheap.top();
            minheap.pop();
            *tail = root;
            tail = &((*tail)->next); 
            if (root->next) 
                minheap.push(root->next);
        }
        *tail = nullptr;
        return dummyNode->next;
    }
};

int main() {
    vector<ListNode*> lists;
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(6);
    ListNode* l2 = new ListNode(3);
    l2->next = new ListNode(5);
    l2->next->next = new ListNode(7);
    ListNode* l3 = new ListNode(1);
    l3->next = new ListNode(8);
    l3->next->next = new ListNode(9);
    ListNode* l4 = new ListNode(10);
    lists.push_back(l1);
    lists.push_back(l2);
    lists.push_back(l3);
    lists.push_back(l4);
    Solution s;
    ListNode* h = s.mergeKLists(lists);
    while (h) {
        cout << h->val << ", ";
        h = h->next;
    }
    cout << endl;
    return 1;
}
