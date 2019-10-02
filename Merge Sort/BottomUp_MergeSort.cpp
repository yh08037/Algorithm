#include <iostream>
using namespace std;


void BottomUpMerge(int A[], int iLeft, int iRight, int iEnd, int B[]) {
    int i = iLeft, j = iRight;
    for (int k = iLeft; k < iEnd; k++) {
        if (i < iRight && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}

void CopyArray(int B[], int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

void BottomUpMergeSort(int A[], int B[], int n) {
    for (int width = 1; width < n; width = 2 * width) {
        for (int i = 0; i < n; i = i + 2 * width) {
            BottomUpMerge(A, i, min(i+width, n), min(i+2*width, n), B);
        }
        CopyArray(B, A, n);
    }
}


int main() {
    int a[] = {50, 73, 97, 39, 60,  3, 26, 31, 41, 91, 24,  6, 47,
               77, 48, 93, 90, 72, 56, 70, 30, 78, 96, 17, 58, 79,
               29, 34,  1, 75,  2, 69,  9, 100, 19, 85, 18, 83, 8,
               68, 51, 33, 20, 57, 42, 14, 87, 10, 23, 76, 94, 49,
               52, 98, 66, 38, 40,  7, 28, 36, 27, 15, 67, 86, 12,
               63, 44,  4, 74, 62, 16, 32, 59, 65, 88, 46, 11, 22,
               64, 55, 92, 13, 35, 21, 82, 71,  5, 89, 37, 95, 53,
               81, 25, 99, 43, 45, 80, 54, 84, 61};
    int b[100];

    BottomUpMergeSort(a, b, 100);

    for (auto it : a)
        cout << it << " ";
}
