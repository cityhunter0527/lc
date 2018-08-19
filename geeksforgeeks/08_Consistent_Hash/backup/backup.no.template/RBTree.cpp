#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <assert.h>
#include "RBTree.hpp"
using namespace std;

// 
// Based on: // http://www.geeksforgeeks.org/red-black-tree-set-2-insert/
// 1. Insert new key to tree rooted at node n;
// 2. Return new root of this subTree;
// 3. If p->val is already in the tree, nothing will happen;
//
RBTree::TreeNode* RBTree::BSTInsert(TreeNode* n, TreeNode* p) {
    // if p->val is not in the tree yet, insert p;
    if (n == nullptr) return p;
    if (p->val < n->val) { 
        n->left = BSTInsert(n->left, p);
        n->left->parent = n;
    } else if (p->val > n->val) {
        n->right = BSTInsert(n->right, p);
        n->right->parent = n;
    }
    // We are here when:
    // 1. p has been inserted;
    // 2. p->val equals to n->val, so just return n;
    return n;
}

// 
// 1) Perform standard BST insertion and make the color of newly inserted nodes as RED.
// 2) If x is root, change color of x as BLACK (Black height of complete tree increases by 1).
// 3) Do following if color of x's parent is not BLACK or x is not root.
// 
// ....a) If x's uncle is RED (Grand parent must have been black from property 4)
// ........i)   Change color of parent and uncle as BLACK.
// ........ii)  Color of grand parent as RED.
// ........iii) Change x = x's grandparent, repeat steps 2 and 3 for new x.
//
// ....b) If x's uncle is BLACK, then there can be four configurations for x, x's parent (p) and x's grandparent (g) (This is similar to AVL Tree)
// ........i)   Left Left Case (p is left child of g and x is left child of p)
// ........ii)  Left Right Case (p is left child of g and x is right child of p)
// ........iii) Right Right Case (Mirror of case a)
// ........iv)  Right Left Case (Mirror of case c)
//
void RBTree::fixViolation(TreeNode* x) {
    TreeNode* parent = nullptr, *grand_parent = nullptr;
    // We are done if either x is root, or x is BLACK or x's parent is BLACK 
    while ((x != root) && (x->parent->color == RED) && (x->color == RED)) { 
        parent = x->parent;
        grand_parent = x->parent->parent;
        if (parent == grand_parent->left) {  
            TreeNode* uncle = grand_parent->right;
            // Case-0: 3.a x's uncle is RED
            if (uncle && (uncle->color == RED)) { 
                parent->color = BLACK;
                uncle->color = BLACK;
                grand_parent->color = RED;
                x = grand_parent; // <<< x could be root now;
            } else {   // <<< 3.b x's uncle is BLACK; if uncle is null, null is also BLACK;
                // Case-1: 3.b.ii Left Right Case
                if (x == parent->right) {
                    leftRotate(parent);
                    // x has become the new parent so restore parent with x so that 
                    // later "swap" after right rotate in Case-2 could work;
                    parent = x; 
                } 
                // Case-2: 3.b.i Left Left Case
                rightRotate(grand_parent);
                swap(parent->color, grand_parent->color);
                x = parent; // let x be parent so that we got the chance to exit while loop;
            }
        } else {
            TreeNode* uncle = grand_parent->left;
            // Case-0: 3.a x's uncle is RED
            if (uncle && (uncle->color == RED)) { 
                parent->color = BLACK;
                uncle->color = BLACK;
                grand_parent->color = RED;
                x = grand_parent;
            } else { // 3.b x's uncle is BLACK
                // Case-3: 3.b.iv Right Left Case
                if (x == parent->left) {
                    rightRotate(parent);
                    // x has become the new parent so restore parent with x so that 
                    // later "swap" after right rotate in Case-4 could work;
                    parent = x;
                }

                // Case-4: 4.b.iii Right Right Case
                leftRotate(grand_parent);
                swap(parent->color, grand_parent->color);
                x = parent; // let x be parent so that we got the chance to exit while loop;
            }
        }
    }
    root->color = BLACK;
}

//     
//    p                        x
//   / \     Right(p)         / \
//  x   T3  ==========>      T1  p
// / \                          / \
//T1  T2                       T2  T3
void RBTree::rightRotate(TreeNode* p) {
    TreeNode* parent = p->parent;
    TreeNode* x = p->left;

    p->left = x->right;
    if (p->left != nullptr)
        p->left->parent = p;

    x->parent = parent;
    if (parent == nullptr) 
        root = x;
    else if (p == parent->left)
        parent->left = x;
    else
        parent->right = x;
    
    x->right = p;
    p->parent = x;
}

//    p                      x
//   / \     Left(p)        / \
//  T1  x   =========>     p   T3
//     / \                / \
//    T2  T3             T1  T2
void RBTree::leftRotate(TreeNode* p) {
    TreeNode* parent = p->parent;
    TreeNode* x = p->right;
    
    p->right = x->left;
    if (p->right != nullptr)
        p->right->parent = p;
    
    x->parent = parent;
    if (parent == nullptr) 
        root = x;
    else if (p == parent->left)
        parent->left = x;
    else
        parent->right = x;
    
    x->left = p;
    p->parent = x;
}

// Description:
//     Replaces subTree rooted at node u with the subTree rooted at node v.
//     Node u's parent becomes v's parent, and u's parent ends up having v as its child accordingly.
//
// Note:
//     transplant doesn't update v.left and v.right; 
//     Doing so or not doing so is the responsibility of transplant's caller;
void RBTree::transplant(TreeNode* u, TreeNode* v) {
    assert (u != nullptr);
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left) 
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

// return node if we've got a match.
// return null if there is node whose val equals to key.
RBTree::TreeNode* RBTree::BSTLookup(TreeNode* r, const KEY_TYPE key) {
    if (r == nullptr) return r;
    if (r->val == key) return r;
    else if (r->val > key)
        return BSTLookup(r->left, key);
    else 
        return BSTLookup(r->right, key);
}

// 
// Based on MIT: <<Introduction to Algorithms>>: Chapter 13 Read-Black Tree
// Delete a node whose value equals to key
// We maintain node y as the node either removed (y has only one child) from the tree or moved within the tree(y has two children).
// We also store y's original color in yOrigColor since y might change;
// 1. if y has only one child
// ....a. We just replace y with its left or right child;
// 2. if y has two children:
// ....a. Replace z with y (successor) and copy z's color, so no black height change from root to y.
// ....b. Remove y in its original position by replacing y w/ y->right (since y is minimum of z->right, 
// .......y must have not left child. y->right child could be NULL); 
// .......And if y's original color is black, we know we've lost black height by one. 
// ........In this case, call "removeFixup":
// ........1) x which is y->right will be used to replace y's position. 
// ........2) y's black color will be moved to x, leave x in "doubly black" or "red-and-black" condition.
// ........3) This function's mission is to make x and x's sibling have same black height (removing doubly BLACK property of x).
// ...........Repeat the while as necessary when we need to keep fixing up x->parent and x->parent's sibling;
//
void RBTree::remove(const KEY_TYPE key) {
    TreeNode* z = BSTLookup(root, key);
    if (z == nullptr) return;
    TreeNode* y = z, *x = nullptr, *px = nullptr;
    Color yOrigColor = y->color;

    // y only has one child
    if (y->left == nullptr) {
        x = z->right;
        px = z->parent; // <<<< px
        transplant(z, z->right); // remove z
    } else if (y->right == nullptr) {
        x = z->left;
        px = z->parent; // <<<< px
        transplant(z, z->left);  // remove z
    } else { // y has Two children
        // Get smallest node that's larger than z to replace z;
        y = minimum(z->right);
        yOrigColor = y->color;
        x = y->right;
        px = y->parent; // <<<< px
        if (y->parent == z) {
            px = y; // need to make px point to y, instead of z;
        } else {
            transplant(y, y->right); // remove y in its original place and then replace z with y;
            // replace z with y: copy right child;
            y->right = z->right;
            y->right->parent = y;
        }

        // Do replace z with y;
        transplant(z, y);
        // replicae z with y: copy left child.
        y->left = z->left;
        y->left->parent = y;
        // Copy color
        y->color = z->color; 
    }
    // after removing y, x is now either doubly black or red-and-black, need to fix it;
    // if px is null, it means the last node is deleted so no need to do any fix; 
    if (px && (yOrigColor == BLACK)) removeFixup(x, px); 
}

// Description:
//     This funciton's mission is to make x and its sibling have same BLACK height;
//     If it needs to repeating the while loop by x->parent, then repeat it to keep fixing
//     up BLACK height between x->parent and x->parent's sibling.
//
// x is either "doubly black" or "red-and-black"
// General idea is to try to remove one black color of the sibling subtree
// ....Fixup red-black tree with given node x;
// ....Basically by visiting x's sibling node w, and try to reduce black height of w by either recoloring and/or rotation.
// ....Recusively rest x to x's parent if current to do it in bottom up manner to adjust new x's sibling's black height.
// ........1) Case-1: x's sibling w is red, can be converted to Case-2/3/4;
// ............a. Since w is red, w's both children must be black (property-4);
// ............b. Switch color of w and x->parent;
// ............c. Perform leftRotate of x.p w/o violate any red-black properties.
// ............d. The new sibling of x will be one of w's children prior to the rotation (1.c), which is black 
// ............e. Repeating while loop to enter into case 2, 3 or 4.
// ............Note: (R) means node is RED; If no (R), means node is BLACK;
//                 B                                         D
//               /   \             Case-1               /         \
//            x A      D(R) w    ==========>           B(R)         E    
//             / \    /  \                           /   \         /  \
//           T1  T2  C     E                      x A     C(new w) T5 T6  
//                  / \   / \                      / \   / \
//                 T3 T4 T5  T6                   T1 T2 T3 T4 
// ........2) Case-2: x's sibling w is black and both w's children are black
// ............a. Since w and its children are all BLACK, we can take one black off on both x and w;
// ............b. So x becomes single BLACK, w becomes RED;
// ............c. Now subTree x and w are BLACK height equal, to compensate this (BLACK height decreased by 1), 
// ...............we need to push one BLACK to x's parent, which makes x->parent doubly black or red-and-black. 
// ............d. Now we repeat the while loop by setting x to x->parent (to make sure new x and its sibling w are black equal); 
// ............Note: In below graph, c means node is RED or BLACK;
//                  B  c                         (new x) B  c
//               /     \           Case-2             /     \
//           x  A       D  w     ===========>       A         D (R)
//             / \    /   \                       /   \     /   \
//            T1 T2  C     E                     T1   T2   C     E
//                  / \   / \                             / \   / \
//                 T3 T4 T5  T6                          T3 T4 T5  T6
// ........3) Case-3: x's sibling w is black, w's left child is red and right child is black, can be converted to case-4
// ............a. We can switch color w and its left child and perform rightRotate w/o violate any RB Tree property.
// ............b. x is new sibling w is now a black node with a red right child, which fall through to Case-4.
//                  B  c                                 B  c
//               /     \           Case-3             /     \
//           x  A       D  w     ===========>    x  A         C new w
//             / \    /   \                       /   \     /   \
//            T1 T2  C(R)  E                     T1   T2   T3    D (R)
//                  / \   / \                                   / \
//                 T3 T4 T5  T6                                T4  E
//                                                                / \
//                                                               T5  T6
// ........4) Case-4: x's sibling w is black, w's right child is red
// ............a. In this case, we can just remove one BLACK on x to make x singly BLACK by:
// ...............make some color changes and perform a leftRotate on x->parent w/o violating any RB Tree property.
// ...............Meanwhile, black height from x->parent to any leaf node stays the same as when x is doubly black. 
// ...............That's why we don't need to repeat the while loop to fixing up by adjusting x->parent's sibling. 
// ............b. Set w's color as x->parent's color. Set x->parent's color as BLACK; Set w->right's color as BLACK;
// ............c. Perform leftRotate on x->parent;
// ............d. Setting x to root to exit while loop;
//                 B  c                                   D  c
//              /     \            Case-4              /     \
//         x  A         D  w     ===========>        B          E
//          /  \      /   \                        /   \       / \
//         T1  T2    C c'  E (R)                  A     C c'  T5  T6
//                  / \   /  \                   / \   / \
//                 T3 T4 T5  T6                 T1 T2 T3  T4
// ....After while loop, set x's color to BLACK because we are here because either x is root or x's color is RED;
// ........a. If x is root, it means we exit from Case-2 or Case-4(Case-1 and Case-3 won't change x)
// ............1. For Case-2, according to 2.d, x and w have same BLACK height and root (new x) now have doubly black. 
// ...............Root's doubly BLACK can simply be changed to single BLACK as root doesn't have sibling (no need to 
// ...............make root to have same BLACK height as its sibling).
// ............2. For Case-4, according to 4.a, there is no need to repeating while loop, we are done.
// ........b. If x has RED color, we can simply change x's color to BLACK as we know x to all the leaf has one black 
// ...........less than x's sibling. That's why are entering this "removeFixup" in the first place.
// ...........By changing x from RED to BLACK, we add one black more so that x and x's sibling now have same black height;
// 
// Note:
// ....0. In the while loop (while x is BLACK), x is always doubly black (non-root), so x's sibling w must not be NULL. 
// ...... Because if w is nullptr, the number of blacks on the simple path from px (x's parent) to the 
// ...... leaf (null) w will be smaller than the blacks on the sample path from px to x;
// ....1. "x" could be NIL so we pass px which is x's parent. And need to update "px" in the while loop in Case-2;
void RBTree::removeFixup(TreeNode* x, TreeNode* px) {
    TreeNode* w = nullptr; 
    // null's color is also black, so we need to include case for x equals to nullptr;
    while (x != root && ((x == nullptr) || (x && x->color == BLACK))) {
        // since x's color is BLACK, this makes x doubly BLACK;
        if (x == px->left) {
            w = px->right;
            // w must not be null, see Note.0
            if (w->color == RED) {
                // Case-1: convert to Case-2/3/4;
                w->color = BLACK;
                px->color = RED;
                leftRotate(px);
                w = px->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK)) {
                // Case-2: take one black off on both x and w;
                // x becomes single BLACK, w becomes RED;
                // x's parent becomes either doubly black or red-and-black;
                w->color = RED;
                x = px;          // reset x for next while loop
                px = px->parent; // reset px for next while loop
            } else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    // Case-3: Do right rotate and fall through to Case-4;
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = px->right;
                }
                // Case-4: left rotate;
                w->color = px->color;
                px->color = BLACK;
                if (w->right) w->right->color = BLACK; 
                leftRotate(px);
                x = root; // set to root so that we could exit while loop;
            }
        } else { // <<<< Symmetric: switch "left" to "right", "right" to "left";
            w = px->left;
            if (w->color == RED) {
                // Case-1
                w->color = BLACK;
                px->color = RED;
                rightRotate(px); // <<< should do rightRotate here, instead of leftRotate
                w = px->left;
            }
            if ((w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK)) {
                // Case-2
                w->color = RED;
                x = px;           // reset x for next while loop;
                px = px->parent;  // reset px for next while loop;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    // Case-3
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = px->left;
                }
                // Case-4
                w->color = px->color;
                px->color = BLACK;
                if (w->left) w->left->color = BLACK;
                leftRotate(px);
                x = root;
            }
        }
    }
    x->color = BLACK; // add one black back to that x and x's sbling now have same black height;
}

RBTree::TreeNode* RBTree::minimum(TreeNode* u) {
    if (u == nullptr) return nullptr;
    while (u->left) {
        u = u->left;
    }
    return u;
}

void RBTree::insert(const KEY_TYPE key, void* data) {
    TreeNode* p = new TreeNode(key, data);
    root = BSTInsert(root, p);
    // if p is not root and p is not added to any place, meaning p's value is already found in tree.
    // Then we will just return because duplicate keys in BST is not allowed.
    if ( p != root && p->left == nullptr && p->right == nullptr && p->parent == nullptr) {
        delete p;
        return;
    }
    fixViolation(p);
}

vector<int> RBTree::levelOrder() {
    vector<int> result;
    result.clear();
    if (root == nullptr) return result;
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* p = nullptr;
    while (!q.empty()) {
        p = q.front();
        result.push_back(p->val);
        q.pop();
        if (p->left)
            q.push(p->left);
        if (p->right)
            q.push(p->right);
    }
    return result;
}

vector<int> RBTree::inOrder() {
    vector<int> result;
    result.clear();
    stack<TreeNode*> s;
    TreeNode* p = root;
    while (!s.empty() || p) {
        if (p) {
            s.push(p);
            p = p->left;
        } else {
            p = s.top();
            s.pop();
            result.push_back(p->val);
            p = p->right;
        }
    }
    return result;
}

#define COLOR(x) ((string)"(" + ((x)->color == BLACK ? "B" : "R") + ")")
vector<vector<string>> RBTree::printTree() {
    vector<vector<string>> res;
    if (!root) return res;
    deque<TreeNode*> q;
    q.push_back(root);
    q.push_back(nullptr);
    int depth = 0;
    // 1. Get height of this tree by level order traversal;
    while (!q.empty()) {
        TreeNode* t = q.front(); q.pop_front();
        if (t == nullptr) {
            depth++;
            if (!q.empty()) q.push_back(nullptr);
            continue;
        } 
        if (t->left)
            q.push_back(t->left);
        if (t->right)
            q.push_back(t->right);
    }

    //
    // init 2D array based on depth, default value to ""
    // numer of colums should be 2^depth-1.
    //
    res.resize(depth, vector<string>(pow(2, depth)-1, ""));

    // 
    // do another level order traversal and for each node, set its value into 2D array
    //
    q.push_back(root);
    q.push_back(nullptr);
    int curDepth = 0;
    unordered_map<TreeNode*, int> m; // node's address to its id in its row (row is curDepth)
    m[root] = pow(2, depth-1) - 1;
    res[curDepth][m[root]] = to_string(root->val) + COLOR(root);
    curDepth++;
    while(!q.empty()) {
        TreeNode* t = q.front(); q.pop_front();
        int id;
        if(t == nullptr) {
            curDepth++;
            if (!q.empty()) q.push_back(nullptr);
            continue;
        }
        if (t->left) {
            q.push_back(t->left);
            // left child's id is:
            //      parent's id - (total subTree's nodes (complete subTree) / 2) 
            // Total subTree's nodes is 2^(depth-curDepth)
            id = m[t] - pow(2, depth-curDepth)/2;  
            res[curDepth][id] = to_string(t->left->val) + COLOR(t->left);
            m[t->left] = id;
        } 
        if (t->right) {
            q.push_back(t->right);
            // right child's id is: 
            //      parent's id + (total subTree's nodes (complete subTree) / 2)
            // Total subTree's nodes is 2^(depth-curDepth)
            id = m[t] + pow(2, depth-curDepth)/2;
            res[curDepth][id] = to_string(t->right->val) + COLOR(t->right);
            m[t->right] = id;
        }
    }

    return res;
}
