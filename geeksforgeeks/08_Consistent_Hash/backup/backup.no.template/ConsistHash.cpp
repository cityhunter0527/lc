#include "ConsistHash.hpp"
#include "sha256.hpp"

// experimental result shows this function performs much worse than 
// below hashDefaultU32 and hashDefaultU64;
HASH_KEY_TYPE hashDefault2(const string data) {
    string digest = sha256(data);
    HASH_KEY_TYPE hash = 0;
    
    // simply sample the 8 bytes from the 32 bytes seems not perform quite well
    // as regard of key distribution.
    hash += ((unsigned long)(digest[3]&0xFFUL) << 56)
          | ((unsigned long)(digest[7]&0xFFUL) << 48)
          | ((unsigned long)(digest[11]&0xFFUL) << 40)
          | ((unsigned long)(digest[15]&0xFFUL) << 32)
          | ((unsigned long)(digest[19]&0xFFUL) << 24)
          | ((unsigned long)(digest[23]&0xFFUL) << 16)
          | ((unsigned long)(digest[27]&0xFFUL) << 8)
          | ((unsigned long)(digest[31]&0xFFUL));

    return hash;
}

HASH_KEY_TYPE hashDefaultU32(const string data) {
    int i;
    string digest = sha256(data);
    HASH_KEY_TYPE hash = 0;
    
    for(i = 0; i < 4; i++)
    {   
        hash += ((unsigned int)(digest[i*4 + 3]&0xFFU) << 24)
              | ((unsigned int)(digest[i*4 + 2]&0xFFU) << 16)
              | ((unsigned int)(digest[i*4 + 1]&0xFFU) << 8)
              | ((unsigned int)(digest[i*4 + 0]&0xFFU));
    }
    return hash;
}

// the U64(8 byte) version doesn't perform well than U32(4 byte);
HASH_KEY_TYPE hashDefaultU64(const string data) {
    int i;
    string digest = sha256(data);
    HASH_KEY_TYPE hash = 0;
    
    for(i = 0; i < 4; i++)
    {   
        hash += ((unsigned long)(digest[i*8 + 7]&0xFFUL) << 56)
              | ((unsigned long)(digest[i*8 + 6]&0xFFUL) << 48)
              | ((unsigned long)(digest[i*8 + 5]&0xFFUL) << 40)
              | ((unsigned long)(digest[i*8 + 4]&0xFFUL) << 32)
              | ((unsigned long)(digest[i*8 + 3]&0xFFUL) << 24)
              | ((unsigned long)(digest[i*8 + 2]&0xFFUL) << 16)
              | ((unsigned long)(digest[i*8 + 1]&0xFFUL) << 8)
              | ((unsigned long)(digest[i*8 + 0]&0xFFUL));
    }
    return hash;
}
void ConsistHash::init(consistHashFunc phashFunc) {
    if (phashFunc != nullptr) 
        mhashFuncPtr = phashFunc;
    else {
        //mhashFuncPtr = hashDefaultU64; 
        mhashFuncPtr = hashDefaultU32; 
        //mhashFuncPtr = hashDefault2; 
    }
    mRBTree = new RBTree();
}

string ConsistHash::node2String(Node *x, int i) {
    return x->iden + "-" + to_string(i);
}

bool ConsistHash::addNode(const string data, unsigned int numVnodes) {
    Node *pNode = new Node(data, numVnodes);
    m[data] = pNode;
    for (unsigned int i = 0; i < numVnodes; i++) {
        string vdata = node2String(pNode, i);
        
        HASH_KEY_TYPE key = mhashFuncPtr(vdata);

        if (mRBTree->search(key) == nullptr) {
            vNode *pvNode = new vNode(key, pNode);
            mRBTree->insert(key, (void*) pvNode);
        } else {
            cout << "Unexpected Error: " << key  << ", " << vdata << endl;
            return false;
        }
    }
    return true;
}

bool ConsistHash::delNode(const string data) {
    return delNode(m[data]);
}

bool ConsistHash::delNode(Node* x) {
    for (int i = 0; i < x->numVnodes; i++) {
        string vdata = node2String(x, i);
        HASH_KEY_TYPE key = mhashFuncPtr(vdata);
        vNode* pvNode = (vNode*)mRBTree->search(key);
        if (pvNode != nullptr && pvNode->node == x && pvNode->key == key) {
            mRBTree->remove(key);
            delete pvNode;
        } else {
            cout << "Unexpected Error: " << pvNode << ", " << pvNode->node << ", " << pvNode->key << endl;
            return false;
        }
    }
    return true;
}

ConsistHash::Node* ConsistHash::lookup(const string data) {
    HASH_KEY_TYPE key = mhashFuncPtr(data); 
    vNode* x = (vNode*)mRBTree->lookup(key);
    if (x != nullptr) {
        return x->node;
    }
    return nullptr;
}
