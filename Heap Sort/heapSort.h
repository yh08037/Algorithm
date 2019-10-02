#ifndef HEAPSORT_H
#define HEAPSORT_H

/* =================== heapSort ===================
    Sort an array, [list0 .. last], using a heap.
        Pre  list must contain at least one item.
             num  contains the number of elements in list.
        Post list has been sorted smallest to largest.
*/
void heapSort(int list[], int num);

/* =================== reheapUp ===================
    Reestablishes heap by moving data in child up to
    correct location heap array.
        Pre  heap is array containing an invalid heap
             newNode is index location to new data in heap
        Post newNode has been inserted into heap
*/
void reheapUp(int* heap, int newNode);

/* =================== reheapDown ===================
    Reestablishes heap by moving data in root down to its
    correct location in the heap.
        Pre  heap is array containing an invalid heap
             root is root of heap or subheap
             last is ans index to the last element in heap
        Post heap has been resorted
*/
void reheapDown(int* heap, int root, int last);

#endif  // HEAPSORT_H
