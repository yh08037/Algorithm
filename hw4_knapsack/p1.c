#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BUFFER_SIZE 256
#define MAX_LEN 128



int main(void) {

  char  input_file_name[BUFFER_SIZE] = "input2.txt";
  FILE* input_file;
  int   temp_w, temp_v;
  int   number, max_weight;
  int   weight[MAX_LEN] = {0};
  int   value[MAX_LEN] = {0};
  int** benefit;
  int   x[MAX_LEN] = {0};


  input_file = fopen(input_file_name, "r");


  /* read input file */

  number = 0;

  while ( 1 ) {
    fscanf(input_file, "%d %d", &temp_w, &temp_v);

    if ( temp_v == -1 ) {
      max_weight = temp_w;
      break;
    }

    number++;
    weight[number] = temp_w;
    value[number] = temp_v;
  }

  fclose(input_file);


  /* generate tabel */
  benefit = (int**) malloc( sizeof(int*) * (max_weight+1) );
  for ( int i = 0; i < max_weight+1; i++ )
    benefit[i] = (int*) malloc( sizeof(int) * (number+1) );


  /* knapsack */

  for ( int w = 0; w <= max_weight; w++ )
    benefit[w][0] = 0;

  for ( int i = 1; i <= number; i++) {
    benefit[0][i] = 0;
    for ( int w = 0; w <= max_weight; w++ ) {
      if ( weight[i] <= w ) {
        if ( value[i] + benefit[w-weight[i]][i-1] > benefit[w][i-1] )
          benefit[w][i] = value[i] + benefit[w-weight[i]][i-1];
        else
          benefit[w][i] = benefit[w][i-1];
      }
      else
        benefit[w][i] = benefit[w][i-1];
    }
  }


  /* backtracking */

  temp_w = max_weight;

  for ( int i = number; i > 0; i-- ) {
    if ( benefit[temp_w][i-1] != benefit[temp_w][i] ) {
      printf("(%d) ", temp_w);
      temp_w -= weight[i];
      x[i] = 1;
    }
  }
  printf("\n");


  /* print answer */

  for ( int i = 1; i <= number; i++ )
    if ( x[i] ) printf("%d ", i);
  printf("%d\n", benefit[max_weight][number]);


  /* free table */

  for ( int i = 0; i < max_weight+1; i++ )
    free(benefit[i]);
  free(benefit);

  return 0;
}
