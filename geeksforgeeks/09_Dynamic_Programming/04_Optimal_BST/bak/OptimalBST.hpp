/*
 *
 * Assumptions:  K1 <= K2 <= K3 <= K4 <= K5;
 * In other words, we can always sort all keys firstly and get according p[] and q[]. 
 * We can only conclude with below formulas with this assumption.
 * 
 * E.g. when we pick a r between [i,j] as the root of sub optimal tree, the left subTree keys [i, r-1] and 
 * right subTree keys [r+1, j] are still a BST that can possibly form an sub optimal BST;
 *
 *               K2
 *            /      \
 *          K1         K4
 *        /    \     /    \
 *      d0      d1  K3      K5
 *                 /  \    /   \
 *               d2   d3  d4    d5  
 *
 * d[i]: represents all values between K[i] and K[i+1]; 
 * d[0]: all the values smaller than K[1];
 * d[5]: all the values larger than K[5];
 *
 *   i  |  0     1     2     3     4     5
 * -----------------------------------------
 * p[i] |       0.15  0.10  0.05  0.10  0.20     // Probability that a search will be K[i]
 * q[i] | 0.05  0.10  0.05  0.05  0.05  0.10     // Probability that a search will be d[i]
 *
 * Sum {p[1] + ... + p[n]} + Sum {q[0] + ... + q[n]} =  1 ----------------------------------------(15.10)
 *
 * Cost of an optimal BST:
 * E[Cost in T] = Sum { (depth(K[1])+1)*p[1] + ... + (depth(K[n])+1)*p[n] } +
 *                Sum { (depth(d[0])+1)*q[0] + ... + (depth(d[n])+1)*q[n] }
 *              = Sum {p[1] + ... + p[n]} + Sum {depth(K[1])*p[1] + ... + depth(K[n])*p[n]} +
 *                Sum {q[0] + ... + q[n]} + Sum {depth(d[0])*q[0] + ... + depth(d[n])*q[n]}  // <<< using 15.10
 *              = 1 + Sum {depth(K[1])*p[1] + ... + depth(K[n])*p[n]} + 
 *                    Sum {depth(d[0])*q[0] + ... + depth(d[n])*q[n]}   --------------------------(15.11)
 *
 * Subproblem:
 * Find an optimal BST containing keys K[i], K[i+1], ... , K[j], whose cost is e[i][j], with K[r] as root:
 * 
 * For a subTree (BST) with keys K[i], ... K[j], let's define sum of probabilities is:
 * w[i][j] = Sum { p[i] + ... + p[j] } + Sum { q[i-1] + q[i] + ... + q[j] };    ------------------(15.12)
 *
 * e[i][j] = q[i-1]                                     j = i-1;
 *         = min{ e[i][r-1] + e[r+1][j] + w[i][j] }     i <= j && i <= r <= j;  ------------------(15.14)
 *
 * The key K[r] will be the root for subtree whose cost is e[i][j];
 *
 * Detailed Prove see CLRS: Chapter 15.5:
 * When j>=i, we need to select a root K[r] from among K[i]...K[j] and then make an optimal BST with 
 * K[i]...K[r-1] as left subtree and K[r+1]...K[j] as right subtree. What happens to the cost of a 
 * subtree when it becomes a subtree of a node? The depth of each node in the subtree increases by 1.
 * By equation (15.11), the cost of this subtree increases by the sum of all the probabilities in the 
 * subtree, which is w[i][j] represented in 15.12;
 *
 * Thus if K[r] is the root of an optimal BST containing keys K[i]...K[j], we have:
 *      e[i][j] = p[r] + (e[i][r-1] + w[i][r-1]) + (e[r+1][j] + w[r+1][j]);
 * since:
 *      w[i][j] = w[i][r-1] + p[r] + w[r+1][j];
 * so e[i][j] can be rewritten as:
 *      e[i][j] = e[i][r-1] + e[r+1][j] + w[i][j];   ---------------------------------------------(15.13)
 * The above assumes we know which is K[r]. To choose the root which gives the lowest cost, we need to visit all the
 * possible r, and compute the smallest e[i][j]. 
 * */

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

class TreeNode {
 public:
     int val;
     TreeNode* left;
     TreeNode* right;
     TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class OptimalBST {
private:
    vector<vector<int>>   e;
    vector<vector<int>>   w;
    vector<vector<int>>   root;
    int                   numKeys;
    bool                  verbose;
private:
    void Print2DVec(vector<vector<int>>& v) {
        for (auto x:v) {
            for (auto y:x) {
                cout << setw(5) << y << ",";
            }
            cout << endl;
        }
    }
    void resize(vector<vector<int>>& v, int m, int n, int defaultVal = 0) {
        v.resize(m);
        for (auto& x:v) x.resize(n, defaultVal);
    }
    // Goal is to compute e[1][n]:
    //  [i][j]         min                      r            Dependancy
    // e[1][1] = e[1][0] + e[2][1] + w[1][1]    1            
    // e[1][2] = e[1][0] + e[2][2] + w[1][2]    1            [2][2] 
    //           e[1][1] + e[3][2] + w[1][2]    2            
    // e[1][3] = e[1][0] + e[2][3] + w[1][3]    1            [3][3] [2][3]
    //           e[1][1] + e[3][3] + w[1][3]    2       
    //           e[1][2] + e[4][3] + w[1][3]    3       
    // e[1][4] = e[1][0] + e[2][4] + w[1][4]    1            [4][4] [3][4] [2][4]
    //           e[1][1] + e[3][4] + w[1][4]    2
    //           e[1][2] + e[4][4] + w[1][4]    3
    //           e[1][3] + e[5][4] + w[1][4]    4
    //
    //    1  2  3  4  .  .  .  n+1
    // 0  x
    // 1  ?  x
    // 2  ?  ?  x
    // 3  ?  ?  ?  x         
    // .              .
    // .                 .
    // .                    .
    // n  ?  ?  ?  ?  .  .  .   x
    //
    void OptimalBSTInternal(vector<int>& q, vector<int>& p, int n) {
        for (int i = 1; i <= n+1; i++) {
            e[i][i-1] = q[i-1];
            w[i][i-1] = q[i-1];
        }

        // Goal is to compute e[1][n]:
        for (int j = 1; j <= n; j++) {
            for (int i = j; i >= 1; i--) {
                // calculate e[i][j]
                // e[1][1]                      
                // e[2][2], e[1][2]             
                // e[3][3], e[2][3], e[1][3]
                // ...
                // [n][n], [n-1][n], ... ,[1][n]
                //
                // w[i][j] only depend on w[i][j-1], since j is increasing, we always have w[i][j-1] calculated before w[i][j];
                w[i][j] = w[i][j-1] + p[j] + q[j];
                e[i][j] = INT_MAX;
                for (int r = i; r <= j; r++) {
                    int t = e[i][r-1] + e[r+1][j] + w[i][j]; // pick r as root; compute cost and see if it is the smallest;
                    if (t < e[i][j]) {
                        e[i][j] = t;                         // if it is the smallest, replace it in e[i][j];
                        root[i][j] = r;                      // then update the root node index;
                    }
                }
            }
        }
        if (verbose) {
            cout << "e" << endl;
            Print2DVec(e);
            cout << "w" << endl;
            Print2DVec(w);
            cout << "root" << endl;
            Print2DVec(root);
        }
    }
public:
    // 
    // n: 
    //     Number of keys. Keys are indexed from 1...n;
    // q[i]:
    //     Probability that a search will hit d[i]  
    // p[i]:
    //     Probability that a search will hit K[i]  
    OptimalBST(vector<int>& q, vector<int>& p, int n, bool verb = false):numKeys(n), verbose(verb) {
        // e[1...n+1][0...n]
        resize(e, n+2, n+2);
        // w[1...n+1][0...n]
        resize(w, n+2, n+2);
        // root[1...n][1...n]
        resize(root, n+1, n+1);
        OptimalBSTInternal(q, p, n);
    }
    int GetOptCost() {
        return e[1][numKeys];
    }
    TreeNode* GetOptBST(vector<int>& keys) {
        if (keys.size() != numKeys) {
            cout << "Conflict numKeys: " << numKeys << "with input keys[]: " << keys.size() << endl;
            return nullptr;
        }
        return ConstructOptBST(1, numKeys, keys);
    }
    // Construct the BST based on "root";
    TreeNode* ConstructOptBST(int i, int j, vector<int>& keys) {
        if (i > j) return nullptr;
        int r = root[i][j];
        TreeNode* x = new TreeNode(keys[r-1]);
        x->left = ConstructOptBST(i, r-1, keys);
        x->right = ConstructOptBST(r+1, j, keys);
        return x;
    }
};


