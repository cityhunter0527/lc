#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_set>
using namespace std;

class Solution {
protected:
    // input: left <= pivotIndex <= right;
    // move all elements smaller than num[pivotIndex] to left, 
    // move all elements larger than num[pivotIndex] to right.
    // return the new pivot index that splits two part.
    int partition(vector<int>& num, int l, int r, int pivotIndex) {
        int pivotValue = num[pivotIndex];
        swap(num[pivotIndex], num[r]);   
        int i, j; 
        // i points to the first element whose value is larger than pivotValue;
        for (i = l, j = l; j < r; j++) {
            if (num[j] < pivotValue)
                swap(num[i++], num[j]);
        }
        // move pivot into the final place
        swap(num[i], num[r]);
        return i;
    }
    
    // 
    // Return k-th smallest element of num with left ... right inclusive; 
    // Each round: left <= k <= right
    // The search space [left, right] is changing for recursive round - but the array
    // is still the same size. Thus k doesn not need to be updated with each round.
    //
    int quickSelect(vector<int>& num, int left, int right, int k) {
        if (left == right) return num[left];
        srand(time(nullptr));
        int pivot = left + rand()%(right-left);
        pivot = partition(num, left, right, pivot);
        if (pivot == k) return num[pivot];
        if (pivot > k)
            return quickSelect(num, left, pivot-1, k);
        else 
            return quickSelect(num, pivot+1, right, k);
    }

    int quickSelectIterative(vector<int>& num, int left, int right, int k) {
        while (left < right) {
            srand(time(nullptr));
            int pivot = left + rand()%(right-left); // much much faster than just pivot = right;
            pivot = partition(num, left, right, pivot);
            if (pivot == k) return num[pivot];
            else if (pivot > k) right = pivot - 1;
            else left = pivot + 1;
        }
        return num[left];
    }

public: 
    //int quickSelect(vector<int>& num, int k) { return quickSelect(num, 0, num.size()-1, k);}
    int quickSelect(vector<int>& num, int k) { return quickSelectIterative(num, 0, num.size()-1, k);}
};

vector<int> getUniqueRandomKeys(int num, int range) {
        vector<int> res;
        srand(time(nullptr));
        unordered_set<int> s;
        int i = 0;
        if (num > range) return res;
        while (i < num) {
            int key = rand()%range;
            if (s.find(key) == s.end()) {
                s.insert(key);
                res.push_back(key);
                i++;
            }
        }
        return res;
    }


int main() {
    Solution s;

    vector<int> v = getUniqueRandomKeys(10000, 10000);
    for (int i = 0; i < 100; i++) {
        srand(time(nullptr));
        int k = rand()%1000;
        int o = s.quickSelect(v, k);
        if (k != o) {
            cout << "test failed!" << endl;
            return 0;
        } else {
            cout << "Pass: " << i << endl;
        }
    }
    return 0;
}
