/*
 * 50. Pow(x, n)
 * Implement pow(x, n).
 * */
#include <iostream>
#include <climits>
using namespace std;

class Solution {
public:

    // binary search
    double myPow(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return x;
        unsigned int i = 1;
        double org = x;
        unsigned int abs_n = abs(n);
        while (i < abs_n) {
            x *= x;
            i *= 2;
        }
        
        // keep doing binary search for left;
        x = x / myPow(org, i - abs_n);
        return n>0? x:1.0/x;
    }

#if 0
    // binary search
    double myPow(double x, int n) {
        unsigned int i = 1;
        double org = x;
        unsigned int abs_n = n<0 ? -(unsigned int)(n) : (unsigned int)(n);
        while (i < abs_n) {
            x *= x;
            i *= 2;
        }
        
        for (unsigned int j = i; j > abs_n; j--)
            x = x/org;

        return n>0? x:1.0/x;
    }
#endif
};

int main () {
    Solution s; 
    cout<< s.myPow(1, -2147483648)<<endl;
    cout<< s.myPow(8, 3)<<endl;
    cout<< s.myPow(4.70975, -6)<<endl;
    cout<< s.myPow(0.00001, 2147483647)<<endl;
    return 1;
}
