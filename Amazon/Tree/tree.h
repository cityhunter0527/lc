#include <iostream>
#include <vector>
#include <string>

template <typename T>
class TreeNode {
public:
    T               val;
    TreeNode<T>*    left;
    TreeNode<T>*    right;
    TreeNode(T x):val(x), left(nullptr), right(nullptr) {}
};

template <typename T>
class Tree {
public:
    Tree(TreeNode<T>* x) : root_(x) {}
    std::vector<T> in_order_traversal() {
        std::vector<T> res;
        return res;
    }
private:
    TreeNode<T>*    root_;
};


