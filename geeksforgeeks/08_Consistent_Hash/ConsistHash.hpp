#include <iostream> 
#include <string> 
#include <unordered_map> 
#include "RBTree.hpp"
using namespace std;

typedef unsigned long HASH_KEY_TYPE; // 8 bytes
//typedef string HASH_KEY_TYPE; // 8 bytes
typedef HASH_KEY_TYPE (*consistHashFunc)(const string data);

class ConsistHash {
public:
    struct Node {
        string          iden;
        unsigned int    numVnodes;
        Node(string x, unsigned int y): iden(x), numVnodes(y) {}
    };
    struct vNode {
        HASH_KEY_TYPE   key;
        Node*           node;
        vNode(HASH_KEY_TYPE x, Node* y):key(x), node(y) {}
    };
private:
    HASH_KEY_TYPE (*mhashFuncPtr)(const string data);
    // store all the vnodes; 
    // How to do vnode to primary node mapping
    RBTree<HASH_KEY_TYPE> *mRBTree; 
    unordered_map<string, Node*> m;
protected:
    string node2String(Node *x, int i);
public:
    void init(consistHashFunc phashFunc = nullptr);
    bool addNode(const string data, unsigned int numVnodes = 1);
    bool delNode(const string data);
    bool delNode(Node* pNode);
    Node* lookup(const string data);
};
