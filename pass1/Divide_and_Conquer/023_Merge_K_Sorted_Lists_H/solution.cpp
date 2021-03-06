//
// Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
//
#include <iostream>
#include <priority_queue>
#include <vector>
#include <limits.h>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) 
            return NULL;
        ListNode *p = lists[0];

        for (int i = 1; i < lists.size(); i++) {
            p = mergeTwoLists(p, lists[i]);
        }

        return p;
    }

private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode head (-1);        
        for (ListNode *p = &head; l1 != NULL || l2 != NULL; p = p->next) {
            int val1 = l1 == NULL? INT_MAX: l1->val;
            int val2 = l2 == NULL? INT_MAX: l2->val;
            if (val1 <= val2) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
        }

        return head.next;
    }
};

int main () {
    vector<ListNode *> v;
    ListNode *l1 = NULL;
    ListNode *l2 = new ListNode (1);
    v.push_back (l1);
    v.push_back (l2);

    Solution s;
    ListNode* m = s.mergeKLists(v);
    
    return 1;
}
