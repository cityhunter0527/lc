/*
 * 23. Merge k Sorted Lists
 * Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
 *
 * Example:
 *
 * Input:
 * [
 * 1->4->5,
 * 1->3->4,
 * 2->6
 * ]
 * Output: 1->1->2->3->4->4->5->6
 * */

#include <iostream>
#include <vector>
#include <cassert>
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    ListNode* merge_two_sorted_lists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0), *p = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if (l1 == nullptr) p->next = l2;
        if (l2 == nullptr) p->next = l1;
        return dummy.next;
    }
public:

    ListNode* mergeKListsV2(std::vector<ListNode*>& lists) {
        // 
        // Merge 
        // list[0], list[n-1]
        // list[1], list[n-2]
        // list[2], list[n-3]
        // ...
        // list[i], list[n-i-1];  util i > n-i
        //
        if (lists.empty()) return nullptr;

        int k = lists.size();
        while (k > 1) {
            int i = 0;
            while (i < k - i - 1) {
                // merge list[i] and list[k-i-1];
                lists[i] = merge_two_sorted_lists(lists[i], lists[k-i-1]);
                i++;
            }
            k = k - i;
        }
        //assert(lists.size()==1);
        return lists[0];
    }
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // 
        // Merge 
        // list[0], list[n-1]
        // list[1], list[n-2]
        // list[2], list[n-3]
        // ...
        // list[i], list[n-i-1];  util i > n-i
        //
        if (lists.empty()) return nullptr;
        while (lists.size() > 1) {
            int i = 0;
            while (i < lists.size() - 1) {
                // merge list[i] and list[n-i-1];
                lists[i] = merge_two_sorted_lists(lists[i], lists[lists.size()-1]);
                i++;
                lists.erase(std::prev(lists.end()));
            }
        }
        assert(lists.size()==1);
        return lists[0];
    }
};

int main() {
    ListNode *l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    ListNode *l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    ListNode *l3 = new ListNode(2);
    l3->next = new ListNode(6);
    
    ListNode *l4 = new ListNode(3);
    l4->next = new ListNode(7);
    
    std::vector<ListNode*>  v;
    v.push_back(l1);
    v.push_back(l2);
    v.push_back(l3);
    v.push_back(l4);
    Solution s;
    ListNode* r = s.mergeKListsV2(v);

    while (r) {
        std::cout << r->val << ", ";
        r = r->next;
    }
    std::cout << std::endl;
    return 0;
}
