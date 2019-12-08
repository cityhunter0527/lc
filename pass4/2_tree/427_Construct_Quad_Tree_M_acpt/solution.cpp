// 
// 427. Construct Quad Tree
//
/* We want to use quad trees to store an N x N boolean grid. Each cell in the grid can only be true or false. 
 * The root node represents the whole grid. For each node, it will be subdivided into four children nodes until 
 * the values in the region it represents are all the same.

Each node has another two boolean attributes : isLeaf and val. isLeaf is true if and only if the node is a leaf node. 

The val attribute for a leaf node contains the value of the region it represents.

Your task is to use a quad tree to represent a given grid. The following example may help you understand the problem better:

Given the 8 x 8 grid below, we want to construct the corresponding quad tree:

It can be divided according to the definition above:


The corresponding quad tree should be as following, where each node is represented as a (isLeaf, val) pair.

For the non-leaf nodes, val can be arbitrary, so it is represented as *.


Note:

N is less than 1000 and guaranteened to be a power of 2.
If you want to know more about the quad tree, you can refer to its wiki.
*/

#include <iostream>
#include <vector>
using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool    val;
    bool    isLeaf;
    Node*   topLeft;
    Node*   topRight;
    Node*   bottomLeft;
    Node*   bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    Node* dfs(vector<vector<int>>& grid, size_t x, size_t y, size_t n) {
        Node* p = new Node();
        if (n == 1) {
            p->val = (grid[x][y] == 1);
            p->isLeaf = true;
            p->topLeft = nullptr;
            p->topRight = nullptr;
            p->bottomLeft = nullptr;
            p->bottomRight = nullptr;
            return p;
        }

        p->topLeft      = dfs(grid, x,        y,        n/2);
        p->topRight     = dfs(grid, x,        y + n/2,  n/2);
        p->bottomLeft   = dfs(grid, x + n/2,  y,        n/2);
        p->bottomRight  = dfs(grid, x + n/2,  y + n/2,  n/2);

        if (p->topLeft->isLeaf && 
            p->topRight->isLeaf && 
            p->bottomLeft->isLeaf && 
            p->bottomRight->isLeaf &&
            p->topLeft->val == p->topRight->val && 
            p->topLeft->val == p->bottomLeft->val && 
            p->topLeft->val == p->bottomRight->val) {
            // children are all leaf and have same val, merge all child to parent;
            p->isLeaf = true;
            p->val = p->topLeft->val;
            delete p->topLeft;
            p->topLeft = nullptr;
            delete p->topRight;
            p->topRight = nullptr;
            delete p->bottomLeft;
            p->bottomLeft = nullptr;
            delete p->bottomRight;
            p->bottomRight = nullptr;
        } else {
            p->isLeaf = false;
        }

        return p;
    }

    Node* construct(vector<vector<int>>& grid) {
        return dfs(grid, 0, 0, grid.size());
    }
};

int main() {
    vector<int> v1 = {1,1,1,1,0,0,0,0};
    vector<int> v2 = {1,1,1,1,1,1,1,1};
    vector<vector<int>>  grid;

    grid.emplace_back(v1);
    grid.emplace_back(v1);
    grid.emplace_back(v2);
    grid.emplace_back(v2);
    grid.emplace_back(v1);
    grid.emplace_back(v1);
    grid.emplace_back(v1);
    grid.emplace_back(v1);
    
    Solution s;
    Node* r = s.construct(grid);

    return 0;
}
