#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define SCALE 1



void   insertion_sort(int* x, int* y, int len);

int    distance(int* x, int* y, int i1, int i2);
double real_distance(int* x, int* y, int i1, int i2);

int    DP(int* x, int* y, int* last, int max_len, int num_city);

int**  create_table(int height, int width);
void   destroy_table(int** arr, int height);




int main() {
  int *x, *y, *result;
  int num_city, i, test;
  int max_city;
  int max_len[] = {200, 400, 600, 800, 1000, 1500};
  double path_len;

  FILE* fp = fopen("hw5ex1.txt", "r");

    
  /* create x, y array */

  fscanf(fp, "%d", &num_city);

  x = (int*)calloc(num_city+1, sizeof(int));
  y = (int*)calloc(num_city+1, sizeof(int));
  result = (int*)calloc(num_city+1, sizeof(int));

  
  /* read input file */

  for ( i = 1; i <= num_city; i++ ) 
    fscanf(fp, "%d %d\n", &x[i], &y[i]);
  fclose(fp);


  /* sort vertice array by x */

  insertion_sort(x, y, num_city);


  /* dp */

  for ( test = 0; test < 1; test++) {
    max_city = DP(x, y, result, max_len[test], num_city);

    path_len = 0;
    int prev = 1;

    for ( i = 2; i <= num_city; i++ ) {
      if ( result[i] ) {
        path_len += real_distance(x, y, prev, i);
        prev = i;
      }
    }
    
    printf("%d %.1lf %d\n", max_len[test], path_len, max_city);
    for ( i = 1; i <= num_city; i++ ) 
      if ( result[i] ) 
        printf("%d %d\n", x[i], y[i]);
    printf("\n\n");

    memset(result, 0, sizeof(int)*(num_city+1));
  }


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


int distance(int* x, int* y, int i1, int i2) {
  return (int) (real_distance(x, y, i1, i2) * SCALE + 0.5);
}


double real_distance(int* x, int* y, int i1, int i2) {
  double x1 = (double) x[i1];
  double y1 = (double) y[i1];
  double x2 = (double) x[i2];
  double y2 = (double) y[i2];

  return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}


int DP(int* x, int* y, int* result, int max_len, int num_city) {

  int    **table, **last;
  int    *mem;
  int    k, i, temp_k, n;
  double max_table;

  int dist = 0;

  max_len *= SCALE;



  /* generate table table */

  table = create_table(max_len+1, num_city+1);
  last  = create_table(max_len+1, num_city+1);

  mem   = (int*)calloc(num_city+1, sizeof(int));


  /* knapsack : filling table */

  for ( k = 0; k <= max_len; k++ ) {
    table[k][0] = 0;
    last[k][0] = 1;
  }

  for ( i = 1; i <= num_city; i++) {
    table[0][i] = 0;
    last[0][i] = 1;

    for ( k = 0; k <= max_len; k++ ) {

      dist = max_len; // 일단 큰값

      for ( n = 0; n <= k; n++ ) {
        if ( distance(x, y, last[n][i-1], i) == k - n ) {
          dist = k - n;
          printf("%d ", dist);
          break;
        }
      }
      // printf("\n");
      
      if ( dist <= k ) {
        if ( 1 + table[k-dist][i-1] > table[k][i-1] ) {
          table[k][i] = 1 + table[k-dist][i-1];
          last[n][i] = i;
        }
        else {
          table[k][i] = table[k][i-1];
          last[n][i] = last[n][i-1];
        }
      }
      else {
        table[k][i] = table[k][i-1];
        last[n][i] = last[n][i-1];
      }
    }
  }


  /* memorize max table */

  max_table = table[max_len][num_city];


  /* backtracking */ 

  // temp_k = max_len;

  // for ( i = num_city; i > 0; i-- ) {
  //   if ( table[temp_k][i-1] != table[temp_k][i] ) {
  //     temp_k -= mem[i];
  //     result[i] = 1;
  //   }
  // }


  /* print table : for validation */

  for ( k = 0; k <= max_len; k++ ) {
    // for ( i = 1; i <= num_city; i++ ) {
    //   printf("%3d", table[k][i]);
    // }

    // printf("     ");
    for ( i = 1; i <= num_city; i++ ) {
      printf("%3d", last[k][i]);
    }
    printf("?\n");
  }


  /* free table table */

  destroy_table(table, max_len+1);
  free(mem);


  return max_table;
}



int** create_table(int height, int width) {
  int **arr, i;

  arr = (int**) calloc(height, sizeof(int*));
  for( i = 0; i < height; i++ )
      arr[i] = (int*) calloc(width, sizeof(int));

  return arr;
}


void destroy_table(int** arr, int height) {
  int i;

  for( i = 0; i < height; i++ )
    free(arr[i]);
  free(arr);
}

