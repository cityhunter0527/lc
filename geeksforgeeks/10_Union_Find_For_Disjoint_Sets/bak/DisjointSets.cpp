#include "DisjointSets.hpp"
#include <assert.h>

DisjointSets::DisjointSets(int n) {
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
    // set id equals to vector index
    for (int i = 1; i < mSets.size(); i++) {
        if (mSets[i].numElems == 0) {
            assert(mSets[i].startIdx == cEndOfElement);
            return i;
        }
    }
    return cInvalidSetId; // this should never happen;
}

int DisjointSets::FindSet(int u) {
    return mElems[u].sid;
}

int DisjointSets::MakeSet(int u) {
    int sid = GetFreeSetID();
    assert(sid != cInvalidSetId);
    
    mSets[sid].numElems = 1;
    mSets[sid].startIdx = u;

    assert(mElems[u].sid == cInvalidSetId);
    mElems[u].sid = sid;

    assert(mElems[u].nextIdx == cEndOfElement);
    return sid;
}

// merge all elememnts in set which contains elem v to set which contains elem u;
// O(n);
int DisjointSets::Union(int u, int v) {
    assert(v != cEndOfElement);
    assert(mElems[u].sid != cInvalidSetId);
    assert(mElems[v].sid != cInvalidSetId);
    
    int vsid = FindSet(v);

    assert(mSets[vsid].startIdx != cEndOfElement);
    v = mSets[vsid].startIdx;
    int savedStart = v;
    assert(v != cEndOfElement);

    int sid = FindSet(u), pv = 0;
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
