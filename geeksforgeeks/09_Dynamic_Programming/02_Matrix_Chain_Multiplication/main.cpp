#include "MatrixChainMultipl.hpp"
#include <iomanip>

class MatrixChainTest {
private: 
   int flen; 
public: 
    MatrixChainTest() {flen = 6;}
    bool tc1();
    bool tc2();
    bool tc3();
    bool tc4();
};

bool MatrixChainTest::tc1() {
    vector<int> p = {10, 100, 5, 50};
    MatrixChainMultipl mcm;
    vector<vector<int>> m, s;
    cout << setw(flen) << mcm.MatrixChainOrder(p, m, s) << ": ";
    mcm.PrintOptimalParents(s, 1, p.size()-1);
    cout << endl;
    return true;
}

bool MatrixChainTest::tc2() {
    //vector<int> p = {200, 5, 10, 100, 30, 5, 50, 80, 5};
    vector<int> p = {200, 5, 10, 100, 30, 5, 50};
    // 71500
    // (A1((A2(A3(A4A5)))A6))
    //    A1    A2     A3      A4     A5    A6
    //  200x5  5x10  10x100  100x30  30x5  5x50
    //
    // 100*30*5 + 10*100*5 + 5*10*5 + 5*5*50 + 200*5*50 = 
    //
    MatrixChainMultipl mcm;
    vector<vector<int>> m, s;
    cout << setw(flen) << mcm.MatrixChainOrder(p, m, s) << ": ";
    mcm.PrintOptimalParents(s, 1, p.size()-1);
    cout << endl;
    return true;
}
bool MatrixChainTest::tc3() {
    vector<int> p = {200, 5, 10, 100, 30, 5, 50, 80, 5};
    // 
    // 46625
    // (A1((A2(A3(A4A5)))(A6(A7A8))))
    //    A1    A2     A3      A4     A5    A6    A7     A8
    //  200x5  5x10  10x100  100x30  30x5  5x50  50x80  80x5
    //  
    //  A7A8 = 50*80*5    
    //  A6(A7A8) = 5*50*5 
    //  
    //  A4A5 = 100*30*5
    //  A3(A4A5) = 10*100*5
    //  A2(A3(A4A5)) = 5*10*5
    //  
    //  (A2(A3(A4A5)))(A6(A7A8)) = 5*5*5
    //  A1(A2(A3(A4A5)))(A6(A7A8)) = 200*5*5
    //
    MatrixChainMultipl mcm;
    vector<vector<int>> m, s;
    cout << setw(flen) << mcm.MatrixChainOrder(p, m, s) << ": ";
    mcm.PrintOptimalParents(s, 1, p.size()-1);
    cout << endl;
    return true;
}

bool MatrixChainTest::tc4() {
    vector<int> p = {30,35,15,5,10,20,25};
    MatrixChainMultipl mcm;
    vector<vector<int>> m, s;
    cout << setw(flen) << mcm.MatrixChainOrder(p, m, s) << ": ";
    mcm.PrintOptimalParents(s, 1, p.size()-1);
    cout << endl;
    return true;
}

int main() {
    MatrixChainTest mct;
    mct.tc1();
    mct.tc2();
    mct.tc3();
    mct.tc4();
    return 0;
}

