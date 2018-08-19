/*
 * 204. Count Primes
 *
 * Description:
 *
 * Count the number of prime numbers less than a non-negative number, n.
 *
 * Hint:
 * Let's start with a isPrime function. To determine if a number is prime, 
 * we need to check if it is not divisible by any number less than n. 
 * The runtime complexity of isPrime function would be O(n) and hence counting 
 * the total prime numbers up to n would be O(n2). Could we do better?
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Sieve of Eratosthenes algorithm
    int countPrimes(int n) {
        vector<bool> prime(n, true);
        prime[1] = false;
        prime[0] = false;
        int l = sqrt(n);
        for (int i = 2; i <= l; i++) {
            if (prime[i]) {
                for (int j = i*i; j < n; j += i) {
                    prime[j] = false;
                }
            }
        }
        return count(prime.begin(), prime.end(), true);
    }
};

int main() {
    Solution s;
    int v = s.countPrimes(499979);
    cout << v << endl;
    v = s.countPrimes(5);
    cout << v << endl;
    return 1;
}
