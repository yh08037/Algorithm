#include <iostream>

using namespace std;

/* =================== insertionSort ===================
    Sort using Insertion Sort. The list is divided into sorted/unsorted list.
    In each pass, first element in unsorted list is inserted into sorted list.
        Pre  list must contain at least one element
             num  contains the number of elements in list.
        Post list has been rearranged
*/
void insertionSort(int list[], int num) {
// Local Definitions
    int hold;   // variable that stores key value of each loop
    int walker;

// Statements
    for (int current = 1; current < num; current++) {
        hold = list[current];
        for (walker = current - 1; walker >= 0 & hold < list[walker]; walker--)
            list[walker + 1] = list[walker];
        list[walker + 1] = hold;
    }   // for current
    return;
}   // insertionSort

int main() {
    int a[] = {50, 73, 97, 39, 60,  3, 26, 31, 41, 91, 24,  6, 47,
               77, 48, 93, 90, 72, 56, 70, 30, 78, 96, 17, 58, 79,
               29, 34,  1, 75,  2, 69,  9, 100, 19, 85, 18, 83, 8,
               68, 51, 33, 20, 57, 42, 14, 87, 10, 23, 76, 94, 49,
               52, 98, 66, 38, 40,  7, 28, 36, 27, 15, 67, 86, 12,
               63, 44,  4, 74, 62, 16, 32, 59, 65, 88, 46, 11, 22,
               64, 55, 92, 13, 35, 21, 82, 71,  5, 89, 37, 95, 53,
               81, 25, 99, 43, 45, 80, 54, 84, 61};

    int n = 100;

    insertionSort(a, n);

    for (auto it : a)
        cout << it << " ";
}
