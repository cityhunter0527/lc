#include "tree.h"

int main() {
    TreeNode<std::string>*       x = new TreeNode<std::string>("cat");
    Tree<std::string>           t(x);
    
    std::vector<std::string>  o = t.in_order_traversal();
    return 1;
}
