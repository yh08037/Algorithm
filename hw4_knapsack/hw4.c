#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BUFFER_SIZE 256
#define MAX_LEN 256





int main(void) {

  char  input_file_name[BUFFER_SIZE] = "input1.txt";
  char  output_file_name[BUFFER_SIZE] = "output.txt";
  FILE* input_file, output_file;
  int   temp_w, temp_v;
  int   number, max_weight;
  int   weight[MAX_LEN] = {0};
  int   value[MAX_LEN] = {0};
  int   benefit[MAX_LEN][MAX_LEN] = {0};


  input_file = fopen(input_file_name, "r");

  // output_file = fopen(output_file_name, "w");


  /* read input file */

  number = 1;

  while ( 1 ) {
    fscanf(input_file, "%d %d", &temp_w, &temp_v);

    if ( temp_v == -1 ) {
      max_weight = temp_w;
      break;
    }

    weight[number] = temp_w;
    value[number] = temp_v;
    number++;
  }

  number--;


  /* knapsack */

  for ( int w = 0; w <= max_weight; w++ )
    benefit[w][0] = 0;

  for ( int i = 1; i <= number; i++) {
    benefit[0][i] = 0;
    for ( int w = 0; w <= max_weight; w++ ) {
      if ( weight[i] <= w ) {
        if ( value[i] + benefit[w-weight[i]][i-1] > benefit[w][i-1] ) {
          benefit[w][i] = value[i] + benefit[w-weight[i]][i-1];
        }
        else {
          benefit[w][i] = benefit[w][i-1];
        }
      }
      else {
        benefit[w][i] = benefit[w][i-1];
      }
    }
  }

  for (int w=0; w<=max_weight; w++) {
    for (int i=0; i<=number; i++) {
      printf("%d ", benefit[w][i]);
    }
    printf("\n");
  }





  fclose(input_file);
}
