#include <iostream>
using namespace std;

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int mid = l + (r-l)/2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid+1, r);
        merge(arr, l, mid, r);
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
      
}

int main() {
    int vect[] = {12, 1, 33, 4, 7, 9, 10, 220, 15, 91, 34, 129};

    return 1;
}
