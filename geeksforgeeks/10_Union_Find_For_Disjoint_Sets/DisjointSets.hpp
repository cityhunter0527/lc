#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
using namespace std;

class DisjointSets {
public:
    DisjointSets() {}
    virtual ~DisjointSets() {}
    // Return the Set ID containing element v;
    virtual int FindSet(int u) = 0; 
    // Return new created Set ID containing element v;
    virtual int MakeSet(int u) = 0;
    // Merge two sets containing u and v and return Set ID of the merged set;
    virtual int Union(int u, int v) = 0;
    bool isValidSetID(int sid) { return sid != cInvalidSetId; }
protected:
    const int cInvalidSetId = -1;
    const int cEndOfElement = -1;
    const int cStartingSetId = 1;
    int mFreeId = cStartingSetId;
protected:
    int GetFreeSetID(); 
};

// 
// Array representation for Disjoint Sets
// Runtime Complexity: O(n*log n) -- TODO: Why? 
// TODO: Mapping between Element value and index;
//       Mapping between SetID and index;
//
class DisjointSetsArray : public DisjointSets {
class Set {
public:
    int numElems;
    int startIdx;
}; 
class Element {
public:
    int sid;
    int nextIdx;
};

private:
    vector<Set>         mSets;
    vector<Element>    mElems;
public:
    DisjointSetsArray(int);
    DisjointSetsArray();
    // Return the Set ID containing element v;
    int FindSet(int u); 
    // Return new created Set ID containing element v;
    int MakeSet(int u);
    // Merge two sets 
    int Union(int s1, int s2);
    int UnionByElement(int u, int v);
};


class DisjointSetsTree : public DisjointSets {
class Element {
public:
    int val;               // Element Value
    int sid;               // only root node's sid can be trusted;
    Element* parent;       // parent == nullptr means this is root node;
    Element(int v, int s):val(v), sid(s), parent(nullptr) {}
};
class Set {
public:
    int sid;
    int numElems;
    Element* root;
    Set(int s, int n, Element* r): sid(s), numElems(n), root(r) {}
};
private:
    unordered_map<int, Element*>   mElems;  // map from Element to node 
    unordered_map<int, Set*>       mSets;   // map from Set id to Set
public:
    // Return the Set ID containing element v;
    int FindSet(int u); 
    // Return new created Set ID containing element v;
    int MakeSet(int u);
    // Merge two sets containing u and v and return Set ID of the merged set;
    int Union(int s1, int s2);
};
