#ifndef __BPLUS_TREE_H__
#define __BPLUS_TREE_H__

#include <iostream>
#include <vector>

template <typename KeyType, 
          typename ValueType,
          typename KeyComparator>
class BaseNodePage {

};

class InternalNodePage : public BaseNodePage {

};

class LeafNodePage : public BaseNodePage {

};

class BPlusTree {
public:
private:
    BPlusTreeNode *mRoot;
};

#endif
