#include "TestLList.hpp"
#include <algorithm>
#include <thread>
#include <chrono>
#include <assert.h>

void LListTest725::Print(vector<ListNode*>& v) {
    cout << "[";
    bool f1 = true;
    for (auto x:v) {
        if (!f1) cout << ", ";
        f1 = false;
        cout << "[";
        bool f2 = true;
        while (x) {
            if (!f2) cout << ", ";
            f2 = false;
            cout << x->val;
            x = x->next;
        }
        cout << "]";
    }
    cout << "]" << endl;
}
void LListTest725::Print(vector<int>& a, vector<ListNode*>& b, int k) {
    Print(a);
    cout << "k: " << k << " =====> ";
    Print(b);
}
void LListTest725::Print(vector<int>& v) { 
    cout << "[";
    bool f = true;
    for (auto x:v) {
        if(!f) cout << ", ";
        f = false;
        cout << x ;
    }
    cout << "]" << endl;
}
bool LListTest725::tc1() {
    Solution s;
    vector<int> v = {1,2,3,4};
    ListNode* root = Construct(v);
    vector<ListNode*> out = s.splitListToParts(root, 5);
    Print(v, out, 5);
    return true;
}
bool LListTest725::tc2() {
    Solution s;
    vector<int> v = {1,2,3};
    ListNode* root = Construct(v);
    vector<ListNode*> out = s.splitListToParts(root, 5);
    Print(v, out, 5);
    return true;
}
bool LListTest725::tc3() {
    Solution s;
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    ListNode* root = Construct(v);
    vector<ListNode*> out = s.splitListToParts(root, 3);
    Print(v, out, 3);
    return true;
}
bool LListTest725::tc4() {
    Solution s;
    vector<int> v;
    for (int i = 1; i <= 20; i++) v.push_back(i);
    ListNode* root = nullptr;

    vector<int> bk = {1,2,3,4,5,6,7,8,9,10};
    for (int i = 0; i < bk.size(); i++) {
        root = Construct(v);
        vector<ListNode*> out = s.splitListToParts(root, bk[i]);
        Print(v, out, bk[i]);
    }
    return true;
}

bool LListTest445::tc1() {
    Solution s;
    vector<int> v1 = {7,2,4,3};
    vector<int> v2 = {5,6,4};
    ListNode* out = s.addTwoNumbers(Construct(v1), Construct(v2));
    Print(out);
    return true;
}
bool LListTest445::tc2() {
    Solution s;
    vector<int> v1 = {2,3,4,5};
    vector<int> v2 = {6,5,5};
    ListNode* out = s.addTwoNumbers(Construct(v1), Construct(v2));
    Print(out);
    return true;
}
bool LListTest445::tc3() {
    Solution s;
    vector<int> v1 = {1,1,1};
    vector<int> v2 = {9,9,9,9,8,8,9};
    ListNode* out = s.addTwoNumbers(Construct(v1), Construct(v2));
    Print(out);
    return true;
}
bool LListTest445::tc4() {
    Solution s;
    vector<int> v1 = {9,1,6};
    vector<int> v2 = {0};
    ListNode* out = s.addTwoNumbers(Construct(v1), Construct(v2));
    Print(out);
    return true;
}

bool LListTest328::tc1() {
    Solution s;
    vector<int> v = {1,2,3,4,5};
    ListNode* l = s.oddEvenList(Construct(v));
    Print(l);
    
    v.clear();
    v.push_back(1);
    l = s.oddEvenList(Construct(v));
    Print(l);

    v.clear();
    l = s.oddEvenList(Construct(v));
    Print(l);
    return true;
}

bool LListTest148::tc1() {
    vector<int> v = {5,4,3,2,1};
    Solution s;
    Print(Construct(v));
    Print(s.sortList(Construct(v)));
    return true;
}

bool LListTest148::tc2() {
    vector<int> v = getUniqueRandomKeys(100, 100);
    Solution s;
    Print(Construct(v));
    Print(s.sortList(Construct(v)));
    return true;
}

bool LListTest147::tc1() {
    vector<int> v = getUniqueRandomKeys(10, 10);
    Solution s;
    Print(Construct(v));
    Print(s.insertionSortList(Construct(v)));
    return true;
}

bool LListTest147::tc2() {
    vector<int> v = getUniqueRandomKeys(30, 30);
    Solution s;
    Print(Construct(v));
    Print(s.insertionSortList(Construct(v)));
    return true;
}

bool LListTest23::tc1() {
    vector<int> v1 = {1,3,5,7,11,11, 13};
    vector<int> v2 = {2,4,5,6,12};
    vector<int> v3 = {0, 3, 6,7,8,9,10};
    Solution s;
    vector<ListNode*> lists;
    lists.push_back(Construct(v1));
    lists.push_back(Construct(v2));
    lists.push_back(Construct(v3));
    ListNode* l = s.mergeKLists(lists);
    Print(l);
    return true;
}


bool LListTest23::tc2() {
    vector<int> v1 = getUniqueRandomKeys(10, 100);
    this_thread::sleep_for(chrono::seconds(1));
    vector<int> v2 = getUniqueRandomKeys(10, 100);
    this_thread::sleep_for(chrono::seconds(1));
    vector<int> v3 = getUniqueRandomKeys(10, 100);
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    sort(v3.begin(), v3.end());
    Solution s;
    vector<ListNode*> lists;
    lists.push_back(Construct(v1));
    lists.push_back(Construct(v2));
    lists.push_back(Construct(v3));
    ListNode* l = s.mergeKLists(lists);
    Print(l);
    return true;
}

// no cycle
bool LListTest142::tc1() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next->next->next = new ListNode(8);
    head->next->next->next->next->next->next->next->next = new ListNode(9);
    Solution s;
    ListNode* p = s.detectCycle(head);
    assert(p == nullptr);
    return true;
}

// tail points to 5
bool LListTest142::tc2() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next->next->next = new ListNode(8);
    head->next->next->next->next->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next->next->next->next->next = head->next->next->next->next->next;
    Solution s;
    ListNode* p = s.detectCycle(head);
    assert(p != nullptr);
    assert(p->val == head->next->next->next->next->next->val);
    return true;
}


// tail points to head
bool LListTest142::tc3() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next->next->next = new ListNode(8);
    head->next->next->next->next->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next->next->next->next->next = head;
    Solution s;
    ListNode* p = s.detectCycle(head);
    assert(p != nullptr);
    assert(p->val == head->val);
    return true;
}

// tail points to 8
bool LListTest142::tc4() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next->next->next = new ListNode(8);
    head->next->next->next->next->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next->next->next->next->next = head->next->next->next->next->next->next->next;
    Solution s;
    ListNode* p = s.detectCycle(head);
    assert(p != nullptr);
    assert(p->val == head->next->next->next->next->next->next->next->val);
    return true;
}

bool LListTestIntersect::tc1() {
    vector<int> v1 = {1,2,3,4,5,6,7,8,9};
    ListNode* l1 = Construct(v1);
    vector<int> v2 = {1,2,3,4,5,6,7,8,9};
    ListNode* l2 = Construct(v2);
    Solution s;
    ListNode* ret = s.detectIntersect(l1, l2);
    assert(ret == nullptr);
    return true;
}

bool LListTestIntersect::tc2() {
    vector<int> v1 = {1,2,3,4,5,6,7,8,9};
    ListNode* l1 = Construct(v1);
    ListNode* l2 = new ListNode(10);
    l2->next = new ListNode(11);
    l2->next->next = new ListNode(12);
    l2->next->next->next = new ListNode(13);
    l2->next->next->next->next = l1->next->next->next->next;
    Solution s;
    ListNode* ret = s.detectIntersect(l1, l2);
    assert(ret != nullptr);
    assert(ret->val == l1->next->next->next->next->val);
    return true;
}

bool LListTestIntersect::tc3() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(3);
    l1->next->next->next = new ListNode(4);
    l1->next->next->next->next = new ListNode(5);
    l1->next->next->next->next->next = new ListNode(6);
    l1->next->next->next->next->next->next = new ListNode(7);
    l1->next->next->next->next->next->next->next = new ListNode(8);
    l1->next->next->next->next->next->next->next->next = new ListNode(9);
    l1->next->next->next->next->next->next->next->next->next = l1->next->next->next->next;
    
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(2);
    l2->next->next = l1->next->next->next;

    Solution s;
    ListNode* ret = s.detectIntersect(l1, l2);
    assert(ret != nullptr);
    assert(ret->val == l1->next->next->next->val);
    return true;
}
bool LListTestIntersect::tc4() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(3);
    l1->next->next->next = new ListNode(4);
    l1->next->next->next->next = new ListNode(5);
    l1->next->next->next->next->next = new ListNode(6);
    l1->next->next->next->next->next->next = new ListNode(7);
    l1->next->next->next->next->next->next->next = new ListNode(8);
    l1->next->next->next->next->next->next->next->next = new ListNode(9);
    l1->next->next->next->next->next->next->next->next->next = l1->next->next->next->next;
    
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(2);
    l2->next->next = l1->next->next->next->next->next->next;

    Solution s;
    ListNode* ret = s.detectIntersect(l1, l2);
    assert(ret != nullptr);
    assert(ret->val == 5 || ret->val == 7);
    return true;
}
