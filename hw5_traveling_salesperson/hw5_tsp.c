#include <stdio.h>
#include <stdlib.h>


// #define NUM_CITY 98
#define NUM_CITY 10



void quick_sort(int* x, int* y, int left, int right);
int  _partition(int* x, int* y, int left, int right, int pivot_index);



int main() {
    
    FILE* fp = fopen("input.txt", "r");
    int x[NUM_CITY];
    int y[NUM_CITY];

    int i;


    for ( i = 0; i < NUM_CITY; i++ ) { 
        fscanf(fp, "%d", x + i);
        fscanf(fp, "%d", y + i);
    }
    fclose(fp);



    quick_sort(x, y, 0, NUM_CITY);


    for ( i = 0; i < NUM_CITY; i++ ) {
        printf("%d %d\n", x[i], y[i]);
    }





    return 0;
}




void quick_sort(int* x, int* y, int left, int right) {

  int pivot_index = right; 

  pivot_index = _partition(x, y, left, right-1, pivot_index); 

  if ( left < pivot_index - 1 )
    quick_sort(x, y, left, pivot_index-1); 
  if ( pivot_index + 1 < right )
    quick_sort(x, y, pivot_index+1, right);
}


int _partition(int* x, int* y, int left, int right, int pivot_index) {
  int temp;
  int pivot = x[pivot_index];

  while ( left <= right ) { 
    while ( x[left] < pivot )  left++;
    while ( x[right] > pivot ) right--;

    if ( left <= right ) { 
      temp = x[left]; x[left] = x[right]; x[right] = temp; 
      temp = y[left]; y[left] = y[right]; y[right] = temp; 
      left++; right--;
    }
  }
  
  temp = x[left]; x[left] = x[pivot_index]; x[pivot_index] = temp; 
  temp = y[left]; y[left] = y[pivot_index]; y[pivot_index] = temp; 
  
  return left;
}