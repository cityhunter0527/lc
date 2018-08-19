#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Solution-1: Array;
class DisjointSets {
class Set {
public:
    int numElems;
    int startIdx;
}; 
class Elements {
public:
    int sid;
    int nextIdx;
};

// TODO: keep record of first free sid;
private:
    vector<Set>         mSets;
    vector<Elements>    mElems;
    const int cInvalidSetId = INT_MIN;
    const int cEndOfElement = -1;

private:
    int GetFreeSetID(); 

public:
    DisjointSets(int);
    // Return the Set ID containing element v;
    int FindSet(int u); 
    // Return new created Set ID containing element v;
    int MakeSet(int u);
    // Merge two sets containing u and v and return Set ID of the merged set;
    int Union(int u, int v);
};
