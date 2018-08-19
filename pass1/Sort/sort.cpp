#include <iostream>
using namespace std;

// --------------------- Quick Sort -----------------------------
// using first elemement as pivot.
// move all element larger to right side.
// move all element smaller to left side. 
// return current pivot index; 
int partition(int v[], int low, int high) {
    int pivot = v[high];
    int i = low; // i always piont to the left most elem which >= pivot
    for (int j = low; j <= high-1; j++) {
        if (v[j] <= pivot) {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[high]);
    return i;
}
void qsort(int v[], int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);
        qsort(v, low, pi-1);
        qsort(v, pi+1, high);
    }
}
// ------------------- End of Quick Sort ----------------------

// ------------------- Merge Sort ----------------------
// arr: [l,m] is sorted
//      [m+1,r] is sorted.
// merge them so that [l,r] is sorted.
void merge(int arr[], int l, int m, int r) {
    int n = r - l + 1;
    int tmp[n];
    int i = l, j = m+1, k = 0;
    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }
    for (int ii = i; ii <= m; ii++)
        tmp[k++] = arr[ii];
    for (int jj = j; jj <= r; jj++)
        tmp[k++] = arr[jj];
    for (int s = l; s <=r; s++) 
        arr[s] = tmp[s-l];
}
void mergesort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergesort(arr, l, m);
        mergesort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
// ------------------- End of Merge Sort ----------------------
int main () {

    int v[] = {2,3,1,5,10,34,12,789,11,222,223};
    //qsort(v, 0, sizeof(v)/sizeof(v[0]) - 1);
    mergesort(v, 0, sizeof(v)/sizeof(v[0]) - 1);
    for (int i = 0; i < sizeof (v)/sizeof(v[0]); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
    return 1;
}

