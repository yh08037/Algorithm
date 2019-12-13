#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




void    insertion_sort(int* x, int* y, int len);

double  greedy(int* x, int* y, int* result, int num_city, int max_len);

double* create_gain_array(int* x, int* y, int* result, int num_city);
double  get_gain(int* x, int* y, int* result, int index, int num_city);
double  distance(int* x, int* y, int i1, int i2);
double  get_path_length(int* x, int* y, int* result, int num_city);
void    update_gain(int* x, int* y, int* result, double* gain_array, int index, int num_city);

int     argmax(double* arr, int len);
void    fprint_path(FILE* fp, int* x, int* y, int* result, int num_city);





int main() {
  int    *x, *y, *result;
  int    num_city, i, test, total_city;
  int    max_len[] = {200, 400, 600, 800, 1000, 1500};
  double path_length;
  FILE   *input, *output;
    

  /* file input */

  input = fopen("hw5ex1.txt", "r");

    
  /* create arrays */

  fscanf(input, "%d", &num_city);

  x =      (int*)calloc(num_city, sizeof(int));
  y =      (int*)calloc(num_city, sizeof(int));
  result = (int*)calloc(num_city, sizeof(int));

  
  /* read input file */

  for ( i = 0; i < num_city; i++ ) 
    fscanf(input, "%d %d\n", &x[i], &y[i]);
  fclose(input);


  /* sort vertice array by x */

  insertion_sort(x, y, num_city);
  


  /* test algorithm */

  output = fopen("output.txt", "w");

  for ( test = 0; test < 6; test++ ) {
    path_length = greedy(x, y, result, num_city, max_len[test]);
    fprintf(output, "%d %.1lf\n", max_len[test], path_length);
    fprint_path(output, x, y, result, num_city);
    fprintf(output, "\n");


    /* for validation */
    
    // total_city = 0;
    // for ( i = 0; i < num_city; i++ )
    //   total_city += result[i];
    // printf("%d : %d\n", max_len[test], total_city);
  }

  fclose(output);


  /* free arrays */

  free(x);
  free(y);
  free(result);
  
  return 0;
}






void insertion_sort(int* x, int* y, int len) {
  int i, j;
  int temp1, temp2;

  for ( i = 1; i < len; i++ ) {
    temp1 = x[i];
    temp2 = y[i];

    for ( j = i ; j > 0 && temp1 < x[j-1]; j-- ) {
      x[j] = x[j-1];
      y[j] = y[j-1];
    }

    x[j] = temp1;
    y[j] = temp2;
  }
}





double greedy(int* x, int* y, int* result, int num_city, int max_len) {
  int     i, max_gain_index;
  double  path_length;
  double* gain_array;


  /* array allocation and initialization */

  for ( i = 0; i < num_city; i++ ) result[i] = 1;
  
  gain_array = create_gain_array(x, y, result, num_city);

  path_length = get_path_length(x, y, result, num_city);
  

  /* update arrays */

  while ( path_length > max_len ) {

    /* choose index which has maximum gain */
    max_gain_index = argmax(gain_array, num_city);

    /* and remove it from path */
    result[max_gain_index] = 0;

    /* and update gain array for changed path */
    update_gain(x, y, result, gain_array, max_gain_index, num_city);
    
    /* get current path length */
    path_length = get_path_length(x, y, result, num_city); 
  }

  free(gain_array);

  return path_length;
}


double* create_gain_array(int* x, int* y, int* result, int num_city) {
  int     i;
  double* gain_array;

  gain_array = (double*)calloc(num_city, sizeof(double));
  
  for ( i = 0; i < num_city; i++ ) 
    gain_array[i] = get_gain(x, y, result, i, num_city);

  return gain_array;
}


double get_gain(int* x, int* y, int* result, int index, int num_city) {
  int left, right;
  double gain;

  if ( index == 0 || index == num_city-1 ) return -1;
  if ( result[index] == 0 ) return -1;


  for ( left = index-1; left >= 0; left-- ) 
    if ( result[left] ) break;
  
  for ( right = index+1; right < num_city; right++ )
    if ( result[right] ) break;


  if ( left < 0 || right > num_city-1 ) return -1;


  gain = distance(x, y, left, index) + distance(x, y, index, right) 
        - distance(x, y, left, right);

  return gain;
}


double distance(int* x, int* y, int i1, int i2) {
  double x1 = (double) x[i1];
  double y1 = (double) y[i1];
  double x2 = (double) x[i2];
  double y2 = (double) y[i2];

  return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}


double get_path_length(int* x, int* y, int* result, int num_city) {
  int prev, curr;
  double length;

  prev = 0;
  length = 0;

  for ( curr = 1; curr < num_city; curr++ ) {
    if ( result[curr] ) {
      length += distance(x, y, prev, curr);
      prev = curr;
    }
  }

  return length;
}


void update_gain(int* x, int* y, int* result, double* gain_array, int index, int num_city) {
  int left, right;

  for ( left = index-1; left >= 0; left-- ) 
    if ( result[left] ) break;
  
  for ( right = index+1; right < num_city; right++ )
    if ( result[right] ) break;

  gain_array[index] = get_gain(x, y, result, index, num_city);
  gain_array[left]  = get_gain(x, y, result, left,  num_city);
  gain_array[right] = get_gain(x, y, result, right, num_city);  
}





int argmax(double* arr, int len) {
  int i, max_idx;
  
  max_idx = 0;
  
  for ( i = 0; i < len; i++ )
    if ( arr[max_idx] < arr[i] )
      max_idx = i;
  
  return max_idx;
}


void fprint_path(FILE* fp, int* x, int* y, int* result, int num_city) {
  int i;

  for ( i = 0; i < num_city; i++ ) {
    if ( result[i] ) {
      fprintf(fp, "%d %d\n", x[i], y[i]);
    }
  }
}