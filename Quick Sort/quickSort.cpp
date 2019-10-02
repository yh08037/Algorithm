#include "quickSort.h"

/* =================== quickInsertion ===================
    Sort data[1...last] using insertion sort. The list is divided into
    sorted and unsorted lists. With each pass, the first element in the
    unsorted list is inserted into the sorted list. Thins is a special
    version of the insertion sort modified for use with quick sort.
        Pre  data must contain at least one element
             first is an index to first element in data
             last is an index to first element in data
        Post data has been rearranged
*/
void quickInsertion(int data[], int first, int last) {
// Local Definitions
    int hold;
    int walker;

// Statements
    for (int current = first + 1; current <= last; current++) {
        hold = data[current];
        walker = current - 1;
        while (walker >= first && hold < data[walker]) {
            data[walker + 1] = data[walker];
            walker = walker - 1;
        }  // while
        data[walker + 1] = hold;
    }  // for
    return;
}  // quickInsertion


/* =================== medianLeft ===================
    Find the median value of ans array, sortData[left..right], and place
    it in the location sortData[left].
        Pre  sortData is array of at leadt three elements
             left and right are boundaries of array
        Post median value placed at sortData[left]
*/
void medianLeft(int sortData[], int left, int right) {
// Local Definitions
    int mid;
    int hold;

// Statements
    mid = left + (right - left) / 2;
    if (sortData[left] > sortData[mid]) {
        hold           = sortData[left];
        sortData[left] = sortData[mid];
        sortData[mid]  = hold;
    }
    if (sortData[left] > sortData[right]) {
        hold            = sortData[left];
        sortData[left]  = sortData[right];
        sortData[right] = hold;
    }
    if (sortData[mid] > sortData[right]) {
        hold            = sortData[mid];
        sortData[mid]   = sortData[right];
        sortData[right] = hold;
    }

    // Median is in middle. Exchange with left
    hold           = sortData[mid];
    sortData[mid]  = sortData[left];
    sortData[left] = hold;

    return;
}   // medianLeft


/* =================== quickSort ===================
    Array. sortData[left..right] sorted using recursion.
        Pre  sortData is an array of data to be sorted
             left identifies first element of sortData
             right identifies last element of sortData
        Post sortData array is sorted
*/
void quickSort(int sortData[], int left, int right) {
#define MIN_SIZE 16

// Local Definitions
    int sortLeft;
    int sortRight;
    int pivot;
    int hold;

// Statements
    if ((right - left) > MIN_SIZE) {
        medianLeft(sortData, left, right);
        pivot = sortData[left];
        sortLeft = left + 1;
        sortRight = right;
        while (sortLeft <= sortRight) {
            // Find key on left that belongs on right
            while (sortData[sortLeft] < pivot)
                sortLeft = sortLeft + 1;
            // Find key on right that belongs on left
            while (sortData[sortRight] >= pivot)
                sortRight = sortRight - 1;
            if (sortLeft <= sortRight) {
                hold                = sortData[sortLeft];
                sortData[sortLeft]  = sortData[sortRight];
                sortData[sortRight] = hold;
                sortLeft = sortLeft + 1;
                sortRight = sortRight - 1;
            }  // if
        }  // while
        // Prepare for the next pass
        sortData[left] = sortData[sortLeft - 1];
        sortData[sortLeft - 1] = pivot;
        if (left < sortRight)
            quickSort(sortData, left, sortRight - 1);
        if (sortLeft < right)
            quickSort(sortData, sortLeft, right);
    }  // if right
    else
        quickInsertion(sortData, left, right);
    return;
}
