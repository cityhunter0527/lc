#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

struct Page {
    vector<int> v;
    Page(vector<int> x):v(x) {}
};

class Solution {
public:
    size_t getTotalNumElems(vector<Page>& arr) {
        size_t sum = 0;
        for (auto& x:arr) {
            sum += x.v.size();
        }
        return sum;
    }

    void EvenDistribute(vector<Page>& arr) {
        if (arr.size() == 0) return;
        int n = getTotalNumElems(arr);
        int x = n/arr.size();
        helper(arr, x, 0);
    }
   
    void helper(vector<Page>& arr, int x, int i) {
        if (i >= arr.size()) return;
        if (arr[i].v.size() == x) 
            return helper(arr, x, i+1);
        int a = arr[i].v.size();
        int k = i + 1;  
        if (a < x) {
            // Copy the missing elements from next vectors
            while(k < arr.size()) {
                if (arr[k].v.size() >= x-a) {
                    // Copy the ones we need to meet x, then we are done;
                    arr[i].v.insert(arr[i].v.end(), arr[k].v.begin(), arr[k].v.begin() + x-a);
                    arr[k].v.erase(arr[k].v.begin(), arr[k].v.begin() + x-a);
                    break;
                } else  {
                    // Copy the whole vector and move to next vector;
                    arr[i].v.insert(arr[i].v.end(), arr[k].v.begin(), arr[k].v.end());
                    arr[k].v.resize(0);
                    a = arr[i].v.size();
                    k++;
                }
            }
            assert(k < arr.size());
        } else {
            // move a-x to next vector;
            arr[k].v.insert(arr[k].v.begin(), arr[i].v.begin()+x, arr[i].v.end());
            arr[i].v.resize(x);
        }
        // Done with i and move on;
        helper(arr, x, i+1);
    }
};

int main() {
    vector<Page>  arr;
    arr.push_back(Page(vector<int>{1,2,3,4,5,6}));
    arr.push_back(Page(vector<int>{7,8}));
    arr.push_back(Page(vector<int>{9,10,11}));
    arr.push_back(Page(vector<int>{12}));
    arr.push_back(Page(vector<int>{13,14}));
    arr.push_back(Page(vector<int>{15,16}));
    arr.push_back(Page(vector<int>{17,18,19,20,21,22,23,24, 25,26,27,28}));

    Solution s;
    s.EvenDistribute(arr);

    int i = 0;
    for (auto& x:arr) {
        cout << "Page-" << i << ": ";
        for (auto& y:x.v) 
            cout << y << ", ";
        cout << endl;
        i++;
    }
    return 1;
}
