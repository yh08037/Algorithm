#include "heapSort.h"

/* =================== heapSort ===================
    Sort an array, [list0 .. last], using a heap.
        Pre  list must contain at least one item.
             num  contains the number of elements in list.f
        Post list has been sorted smallest to largest.
*/
void heapSort(int list[], int num) {
// Local Definitions
    int sorted;     // index of last element in list
    int holdData;   // temp variable for swap

// Statements
    // Create heap
    for (int walker = 1; walker < num; walker++)
        reheapUp(list, walker);

    // Heap created. Now sort it.
    sorted = num - 1;
    while (sorted > 0) {
        holdData     = list[0];
        list[0]      = list[sorted];
        list[sorted] = holdData;
        // same as std::swap(list[0], list[sorted]);
        sorted--;
        reheapDown(list, 0, sorted);
    }   // while
    return;
}   // heapSort


/* =================== reheapUp ===================
    Reestablishes heap by moving data in child up to
    correct location heap array.
        Pre  heap is array containing an invalid heap
             newNode is index location to new data in heap
        Post newNode has been inserted into heap
*/
void reheapUp(int* heap, int newNode) {
// Local Definitions
    int parent;
    int hold;   // temp variable for swap

// Statements
    // it not at root of heap
    if (newNode) {
        parent = (newNode - 1) / 2;
        if (heap[newNode] > heap[parent]) {
            hold          = heap[parent];
            heap[parent]  = heap[newNode];
            heap[newNode] = hold;
            // same as std::swap(heap[newNode], heap[parent]);
            reheapUp(heap, parent);
        }   // if heap[]
    }   // if newNode
    return;
}   // reheapUp


/* =================== reheapDown ===================
    Reestablishes heap by moving data in root down to its
    correct location in the heap.
        Pre  heap is array containing an invalid heap
             root is root of heap or subheap
             last is ans index to the last element in heap
        Post heap has been resorted
*/
void reheapDown(int* heap, int root, int last) {
// Local Definitions
    int hold;
    int leftKey;
    int rightKey;
    int largeChildKey;
    int largeChildIndex;

// Statements
    if ((root * 2 + 1) <= last) {
        // There is at least one child
        leftKey = heap[root * 2 + 1];
        if ((root * 2 + 2) <= last)
            rightKey = heap[root * 2 + 2];
        else
            rightKey = -1;

        // Determine which child is larger
        if (leftKey > rightKey) {
            largeChildKey = leftKey;
            largeChildIndex = root * 2 + 1;
        }   // if leftKey
        else {
            largeChildKey = rightKey;
            largeChildIndex = root * 2 + 2;
        }   // else

        // Test if root > larger subtree
        if (heap[root] < heap[largeChildIndex]) {
            // parent < children
            hold       = heap[root];
            heap[root] = heap[largeChildIndex];
            heap[largeChildIndex] = hold;
            reheapDown(heap, largeChildIndex, last);
        }   // if root <
    }   // if root
    return;
}   // reheapDown
