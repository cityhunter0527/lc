#include "LinkedList.hpp"
#include <queue>
// 
// 725. Split Linked List in Parts
// Given a (singly) linked list with head node root, write a function to 
// split the linked list into k consecutive linked list "parts". The length 
// of each part should be as equal as possible: no two parts should have a 
// size differing by more than 1. This may lead to some parts being null.
// The parts should be in order of occurrence in the input list, and parts 
// occurring earlier should always have a size greater than or equal parts 
// occurring later.
//
// Return a List of ListNode's representing the linked list parts that are 
// formed.
//
// Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
// Example 1:
// Input: 
// root = [1, 2, 3], k = 5
// Output: [[1],[2],[3],[],[]]
// Explanation:
// The input and each element of the output are ListNodes, not arrays.
// For example, the input root has root.val = 1, root.next.val = 2, 
// \root.next.next.val = 3, and root.next.next.next = null.
// The first element output[0] has output[0].val = 1, output[0].next = null.
// The last element output[4] is null, but it's string representation as a 
// ListNode is [].
// 
// Example 2:
// Input: 
// root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
// Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
// Explanation:
// The input has been split into consecutive parts with size difference at 
// most 1, and earlier parts are a larger size than the later parts.
// 
// Note:
// The length of root will be in the range [0, 1000].
// Each value of a node in the input will be an integer in the range [0, 999].
// k will be an integer in the range [1, 50].
//
#include "LinkedList.hpp"
vector<ListNode*> Solution::splitListToParts(ListNode* root, int k) {
    int len = getListLen(root); 
    int n = len/k, m = len%k;
    vector<ListNode*> res;
    ListNode* p = root, *prev = nullptr;
    int i = 0, j = 0;
    while (p) {
        while (i++ < n) { prev = p; p = p->next; }
        if (j < m) { prev = p; p = p->next; j++;}
        if (prev) prev->next = nullptr;
        res.push_back(root);
        root = p;
        i = 0; 
    }
    while (res.size() < k) res.push_back(nullptr);
    return res;
}

// 
// 445. Add Two Numbers II
// You are given two non-empty linked lists representing two non-negative integers. 
// The most significant digit comes first and each of their nodes contain a single digit. 
// Add the two numbers and return it as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Follow up:
// What if you cannot modify the input lists? In other words, reversing the lists is not allowed.
//
// Example:
//
// Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 8 -> 0 -> 7
//
// Option-2: No reversing
//
ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2) {
    vector<int> num1, num2;
    while (l1) {
        num1.push_back(l1->val);
        l1 = l1->next;
    }
    while(l2) {
        num2.push_back(l2->val);
        l2 = l2->next;
    }
    
    int i = num1.size(), j = num2.size();
    ListNode dummy(1), *p = nullptr;
    int carry = 0, sum = 0;;
    while (i&&j) {
        sum = num1[i-1] + num2[j-1] + carry;
        p = dummy.next;
        dummy.next = new ListNode(sum%10);
        dummy.next->next = p;
        carry = sum/10;
        i--; j--;
    }
    while (i) {
        sum = num1[i-1] + carry; carry = sum/10;
        p = dummy.next;
        dummy.next = new ListNode(sum%10);
        dummy.next->next = p;
        i--;
    } 
    while (j){
        sum = num2[j-1] + carry; carry = sum/10;
        p = dummy.next;
        dummy.next = new ListNode(sum%10);
        dummy.next->next = p;
        j--;
    }
    if (carry) { 
        p = dummy.next;
        dummy.next = new ListNode(carry);
        dummy.next->next = p;
    }
    return dummy.next;
}

// Option-1. Reverse list
ListNode* Solution::addTwoNumbersOpt1(ListNode* l1, ListNode* l2) {
    l1 = reverse(l1); l2 = reverse(l2);
    ListNode dummy(1), *p = nullptr;
    int carry = 0, sum = 0;;
    while (l1&&l2) {
        sum = l1->val + l2->val + carry; carry = sum/10;
        p = dummy.next;
        dummy.next = new ListNode(sum%10);
        dummy.next->next = p; l1 = l1->next; l2 = l2->next;
    }
    if (!l1) l1 = l2; 
    while (l1) {
        sum = l1->val + carry; carry = sum/10;
        p = dummy.next;
        dummy.next =  new ListNode(sum%10);
        dummy.next->next = p; l1 = l1->next;
    }
    if (carry) { 
        p = dummy.next;
        dummy.next = new ListNode(carry);
        dummy.next->next = p;
    }
    return dummy.next;
}

// 
// 328. Odd Even Linked List
// Given a singly linked list, group all odd nodes together followed by the even nodes. 
// Please note here we are talking about the node number and not the value in the nodes.
//
// You should try to do it in place. The program should run in O(1) space complexity and 
// O(nodes) time complexity.
//
// Example:
// Given 1->2->3->4->5->NULL,
// return 1->3->5->2->4->NULL.
//
// Note:
// The relative order inside both the even and odd groups should remain as it was in the input. 
// The first node is considered odd, the second node even and so on ...
//
ListNode* Solution::oddEvenList(ListNode* head) {
    ListNode dummyOdd(1), dummyEven(1);
    ListNode* p = &dummyOdd, *q = &dummyEven, *tmp = nullptr;
    bool odd = true;
    while(head) {
        tmp = head;
        head = head->next;
        if (odd) {
            p->next = tmp;
            p = p->next;
        } else {
            q->next = tmp;
            q = q->next;
        }
        tmp->next = nullptr;
        odd = !odd;
    }
    p->next = dummyEven.next;
    return dummyOdd.next;
}

// 
// 148. Sort List
// Sort a linked list in O(n log n) time using constant space complexity.
// Merge sort: O(n log n) 
// Specifically: log n * (n/2 + n) in which:
// ....n/2 is the cost for frontBackSplit; 
// ....n is for SortedMerge. 
// ....repeated for log n times since this we split list into two halves every time.
//
ListNode* Solution::sortList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* left = nullptr, *right = nullptr;
    frontBackSplit(head, left, right);
    left = sortList(left);
    right = sortList(right);
    return sortedMerge(left, right);
}

// merge(in-place) two sorted list and return the sorted list's head; 
ListNode* Solution::sortedMerge(ListNode* l1, ListNode* l2) {
    ListNode dummy(1), *p = &dummy;
    while(l1&&l2) {
        if (l1->val > l2->val) {
            p->next = l2;
            l2 = l2->next;
        } else {
            p->next = l1;
            l1 = l1->next;
        }
        p = p->next;
    }
    if (l1) p->next = l1;
    else p->next = l2;
    return dummy.next;
}

// split list into two halves (front and back). The head stored in a and b respectively;
void Solution::frontBackSplit(ListNode* head, ListNode*& a, ListNode*& b) {
    if (!head) { a = nullptr; b = nullptr; return; }
    ListNode* slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    b = slow->next;
    slow->next = nullptr;
    a = head;
}

// 
// 147. Insertion Sort List
// Sort a linked list using insertion sort.
//
// 1) Create an empty list;
// 2) For each node in the given list, insert it to the list so that it is sorted.
// 3) Return the sorted list's head;
//
ListNode* Solution::insertionSortList(ListNode* head) {
    ListNode dummy(1), *tmp = nullptr;
    while (head) {
        tmp = head;
        head = head->next;
        tmp->next = nullptr;
        insertSorted(&dummy, tmp);
    }
    return dummy.next;
}

// insert node x into a sorted list who's head is dummy->next;
void Solution::insertSorted(ListNode* dummy, ListNode* x) {
    if (x == nullptr) return;
    ListNode* p = dummy;
    while (p->next) {
        if (p->next->val < x->val) p = p->next;
        else {
            x->next = p->next;
            p->next = x;
            return;
        }
    }
    p->next = x;
    x->next = nullptr;
}



// 
// operator() means:
// ListNodeComp a;
// ListNode* left, *right;
// a(left,right); will return true or false;
//
class ListNodeComp{
public:
    bool operator() (ListNode* l, ListNode* r) {
        return l->val > r->val;
    }
};

// 
// 23. Merge k Sorted Lists
// Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
// TODO: Merge k sorted array, min heap too n*k*logk (k linked lists each with n nodes).
//
ListNode* Solution::mergeKLists(vector<ListNode*>& lists) {
    // min heap
    priority_queue<ListNode*, vector<ListNode*>, ListNodeComp> q;
    ListNode dummy(1), *p = &dummy, *tmp = nullptr;
    // make heap
    for (auto x:lists)  
        if (x != nullptr) q.push(x);
    while(!q.empty()) {
        tmp = q.top();
        q.pop();
        if(tmp->next) 
            q.push(tmp->next);
        p->next = tmp;
        p = p->next;
    }
    p->next = nullptr;
    return dummy.next;
}

// 
// 142. Linked List Cycle II
// Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
//
// Note: Do not modify the linked list.
//
// Follow up:
// Can you solve it without using extra space?
//
// Solution:
// ....Suppose the length from head to the node K (cycle begins) is k.
// ....The length from node K to the node that slow and fast node intersect 
// ....is a. When slow and fast pointer intersect:
// ........Slow: k+a, Fast: 2(k+a);  if we decude Fast with Slow, Fast pointer
// ........could have looped the circle for n (n>=1) times.
// ........So we have: 
// ........====> k+a + n*l = 2(k+a)  where l is the length of the circle and n >= 0;
// ........====> k+a = n*l; 
// ........if n is 1, then if we rebase slow to head again, and fast moves k nodes
// ........(slow moves k nodes too), they will at node K; 
// ........if n > 1; then when the first time slow and fast meet, they must meet at node K;
//
// Note: k could be very larget and l could be very small, then n could be larger than 1;
//
ListNode *Solution::detectCycle(ListNode *head) {
    ListNode* slow = head, *fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (fast && fast->next) {
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    } else
        return nullptr;
}

ListNode *Solution::detectIntersect(ListNode *l1, int len1, ListNode* l2, int len2) {
    int d = len1 - len2;
    ListNode* tmp = nullptr;
    if (len1 < len2) { 
        d = len2 - len1;
        tmp = l1; 
        l1 = l2; 
        l2 = tmp;
    }
    // l1 always points to the longer list;
    while(d-- > 0) l1 = l1->next;
    while (l1 != l2) {
        l1 = l1->next; 
        l2 = l2->next;
    }
    return l1;

}

// Distance between the two nodes;
// caller must garunteen end could be reached via start, otherwise, it will be dead loop
int Solution::dist(ListNode* start, ListNode* end) {
    int len = 0;
    while (start != end) {
        start = start->next;
        len++;
    }
    return len;
}
// 
// Linked List Cycle IV - No Cycle and with Cycle
//
ListNode *Solution::detectIntersect(ListNode *l1, ListNode* l2) {
    ListNode* c1 = detectCycle(l1), *c2 = detectCycle(l2);
    int len1 = 0, len2 = 0;
    if (c1 != nullptr && c2 != nullptr) {
        // both l1 and l2 have cycles
        if (c1 == c2) {
            // 
            // intersect node is outside of the cycle;
            // l1:  1->2->3-> 4 ->5->6->7
            //        /|\    /|\        |
            //         |      |_________|
            //         |
            // l2:  1->2
            //
            return detectIntersect(l1, dist(l1, c1), l2, dist(l2, c1));
        } else {
            // 
            // intersect node is inside the cycle;
            // l1: 1->2->3-----------  
            //                      |
            //                     \|/
            // l2: 1->2->3-> 4 ->5->6->7
            //              /|\        |
            //               |_________|
            //
            // in this case either c1 or c2 can be treated as the intersect node;  
            return c1;
        }
    } else if (c1 == nullptr && c2 == nullptr) {
        // neigher l1 nor l2 have cycles
        return detectIntersect(l1, getListLen(l1), l2, getListLen(l2));
    } else {
        // only one of l1 and l2 has cycle
        return nullptr;
    }
}
