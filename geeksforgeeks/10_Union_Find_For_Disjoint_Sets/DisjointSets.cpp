#include "DisjointSets.hpp"
#include <assert.h>

DisjointSetsArray::DisjointSetsArray() {

}

DisjointSetsArray::DisjointSetsArray(int n) {
    mSets.resize(n+1);
    for (auto& x:mSets) {
        x.numElems = 0;
        x.startIdx = cEndOfElement;
    }
    mElems.resize(n+1);
    for (auto& x:mElems) {
        x.sid = cInvalidSetId;
        x.nextIdx = cEndOfElement;
    }

    for (int i = 1; i <= n; i++) {
        MakeSet(i);   
    }
}

int DisjointSets::GetFreeSetID() {
    return mFreeId++;
}

// 
// Runtime Complexity: O(1);
//
int DisjointSetsArray::FindSet(int u) {
    return mElems[u].sid;
}

int DisjointSetsArray::MakeSet(int u) {
    int sid = GetFreeSetID();
    assert(sid != cInvalidSetId);
    
    mSets[sid].numElems = 1;
    mSets[sid].startIdx = u;

    assert(mElems[u].sid == cInvalidSetId);
    mElems[u].sid = sid;

    assert(mElems[u].nextIdx == cEndOfElement);
    return sid;
}

// merge two sets
int DisjointSetsArray::Union(int s1, int s2) {
    if (mSets[s1].numElems < mSets[s2].numElems) swap(s1, s2); 

    // Merge s2 to s1;
    int v = mSets[s2].startIdx;
    if (v == cEndOfElement) return s1; // return if s2 is empty;
    
    int savedStartIdx = v;
    int pv = 0;
    while (v != cEndOfElement) {
        mElems[v].sid = s1;
        mSets[s1].numElems++;
        pv = v;
        v = mElems[v].nextIdx;
    }

    mElems[pv].nextIdx = mSets[s1].startIdx;
    mSets[s1].startIdx = savedStartIdx;
    
    mSets[s2].numElems = 0;
    mSets[s2].startIdx = cEndOfElement;
    return s1;
}

// 
// Merge all elememnts in set which contains elem v to set which contains elem u;
// Always merge small set to larger one;
// Runtime Complexity: O(n);
//
int DisjointSetsArray::UnionByElement(int u, int v) {
    int vsid = FindSet(v), usid = FindSet(u), sid = usid;
    if (mSets[usid].numElems < mSets[vsid].numElems) {
        // merge u to v;
        sid = vsid;
        vsid = usid;
    }

    assert(mSets[vsid].startIdx != cEndOfElement);
    v = mSets[vsid].startIdx;
    int savedStart = v;
    assert(v != cEndOfElement);

    int pv = 0;
    while (v != cEndOfElement) {
        mElems[v].sid = sid;
        mSets[sid].numElems++;
        pv = v;
        v = mElems[v].nextIdx;
    }

    mElems[pv].nextIdx = mSets[sid].startIdx;
    mSets[sid].startIdx = savedStart;
    
    mSets[vsid].numElems = 0;
    mSets[vsid].startIdx = cEndOfElement;
    return sid;
}

//
//============= DisjointSetsTree =================
//
//
// Runtime Complexity: O(log n)
//
int DisjointSetsTree::FindSet(int u) {
    if (mElems.find(u) != mElems.end()) {
        // get the leaf node and track back to the root node which contains Set ID;
        Element* t = mElems[u];
        vector<Element*> nodes;
        int sid;
        while (1) {
            if (t->parent) {
                nodes.push_back(t);
                t = t->parent;
            } else {
                sid = t->sid; // t is root
                break;
            }
        }
        for (auto& x:nodes) 
            x->parent = mSets[sid]->root;
        return sid;
    } else 
        return cInvalidSetId;
}

// 
// Merge set with smaller number of elements to larger
// Runtime Complexisty: O(1);
int DisjointSetsTree::Union(int s1, int s2) {
    int n1 = mSets[s1]->numElems;   
    int n2 = mSets[s2]->numElems;   
    if (n1 < n2) {
        int tmp = s1;
        s1 = s2;
        s2 = tmp;
    }
    // Merge s2 to s1; just make s2's root as s1's child
    Set* ps1 = mSets[s1], *ps2 = mSets[s2];
    ps2->root->parent = ps1->root;
    ps1->numElems += ps2->numElems;

    // clear s2 
    mSets.erase(s2);
    // delete ps2;
    return s1;
}

int DisjointSetsTree::MakeSet(int u) {
    int sid = GetFreeSetID();
    Element* e = new Element(u, sid);
    mElems[u] = e;
    Set* s = new Set(sid, 1, e);
    mSets[sid] = s;
    return sid;
}
