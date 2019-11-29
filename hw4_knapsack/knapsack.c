#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 64


void read_txt_1(int* weight, int* value, int* max_weight, int* number);
void read_txt_2(int* weight, int* value, int* max_weight, int* number);

double knapsack(int* weight, int* value, int* x, int max_weight, int number);
double knapsack_one_split(int* weight, int* value, int* x, int max_weight, int number);
double knapsack_one_duplicate(int* weight, int* value, int* x, int max_weight, int number);
double knapsack_2(int* weight, int* value, int* x, int max_weight, int number);

void  print_result(int* x, double result, int number);
void validate_result(int* value, int* x, double result, int number);
int** create_table(int height, int width);
void  destroy_table(int** arr, int height);


int main(void) {

  int    number, max_weight;
  int    weight[MAX_LEN] = {0};
  int    value[MAX_LEN] = {0};
  int    x_1[MAX_LEN] = {0};  // 0 : not in       1: in
  int    x_2[MAX_LEN] = {0};  // 2 : splited
  int    x_3[MAX_LEN] = {0};  // 3 : duplicated
  int    x_4[MAX_LEN] = {0};  // 4 : knapsack 1   5 : knapsack 2
  double result;


  /* read input file for problem 1, 2, 3 */

  read_txt_1(weight, value, &max_weight, &number);


  /* problem 1. standard 0-1 knapsack problem */

  result = knapsack(weight, value, x_1, max_weight, number);

  print_result(x_1, result, number);
  validate_result(value, x_1, result, number);


  /* problem 2. 0-1 knapsack with one item split */

  result = knapsack_one_split(weight, value, x_2, max_weight, number);

  print_result(x_2, result, number);
  validate_result(value, x_2, result, number);


  /* problem 3. knapsack with one duplicate item */

  result = knapsack_one_duplicate(weight, value, x_3, max_weight, number);

  print_result(x_3, result, number);
  validate_result(value, x_3, result, number);


  /* problem 4. knapsack with two identical knapsack */

  // read_txt_1(weight, value, &max_weight, &number);
  //
  // result = knapsack_one_duplicate(weight, value, x_4, max_weight, number);
  //
  // print_result(x_4, result, number);
  // validate_result(value, x_1, result, number);
  //


  return 0;
}


void read_txt_1(int* weight, int* value, int* max_weight, int* number) {

  char  input_file_name[] = "input6.txt";
  FILE* input_file;
  int   temp_w, temp_v;


  /* read input file */

  *number = 0;
  input_file = fopen(input_file_name, "r");

  while ( 1 ) {
    fscanf(input_file, "%d %d", &temp_w, &temp_v);

    if ( temp_v == -1 ) {
      *max_weight = temp_w;
      break;
    }

    (*number)++;
    weight[*number] = temp_w;
    value[*number] = temp_v;
  }

  fclose(input_file);
}


double knapsack(int* weight, int* value, int* x, int max_weight, int number) {

  int**  benefit;
  int    w, i, temp_w;
  double max_benefit;


  /* generate benefit table */

  benefit = create_table(max_weight+1, number+1);


  /* knapsack : filling table */

  for ( w = 0; w <= max_weight; w++ )
    benefit[w][0] = 0;

  for ( i = 1; i <= number; i++) {
    benefit[0][i] = 0;
    for ( w = 0; w <= max_weight; w++ ) {
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

  for ( i = number; i > 0; i-- ) {
    if ( benefit[temp_w][i-1] != benefit[temp_w][i] ) {
      // printf("(%d) ", temp_w);
      temp_w -= weight[i];
      x[i] = 1;
    }
  }


  /* print table : for validation */

  // for ( w = 0; w <= max_weight; w++ ) {
  //   for ( i = 0; i <= number; i++ ) {
  //     printf("%3d", benefit[w][i]);
  //   }
  //   printf("\n");
  // }


  /* memorize max benefit */

  max_benefit = benefit[max_weight][number];


  /* free benefit table */

  destroy_table(benefit, max_weight+1);


  return max_benefit;
}


double knapsack_one_split(int* weight, int* value, int* x, int max_weight, int number) {

    int**  x_list;
    double max_benefit, result;
    int    max_benefit_index, i;


    /* generate x_list table */

    x_list = create_table(number+1, number+1);


    /* try all cases */

    for ( i = 1; i <= number; i++ ) {
      weight[i] *= 2; value[i] *= 2;
    }
    max_weight *= 2;

    max_benefit = knapsack(weight, value, x, max_weight, number);
    max_benefit_index = 0;

    for ( i = 1; i <= number; i++ ) {
      weight[i-1] *= 2; value[i-1] *= 2;
      weight[i] /= 2;   value[i] /= 2;
      weight[number+1] = weight[i];
      value[number+1]  = value[i];


      result = knapsack(weight, value, x_list[i], max_weight, number+1);

      if ( max_benefit < result ) {
        max_benefit = result;
        max_benefit_index = i;
      }
    }


    /* mark x array from x_list of maximum benefit */

    if ( max_benefit_index != 0 ) {
      for ( i = 1; i <= number; i++ )
        x[i] = x_list[max_benefit_index][i];

      x[max_benefit_index] = 2;

      /* verify x array with x[number+1] */

      // if ( x[max_benefit_index] && x[number+1] )
      //   x[max_benefit_index] = 1; // two halved item == just one item
      // else if ( x[max_benefit_index] || x[number+1] )
      //   x[max_benefit_index] = 2; // only one halved item is included
    }


    /* reset weight, value */

    for ( i = 1; i < number; i++ ) {
      weight[i] /= 2; value[i] /= 2;
    }
    max_weight /= 2;
    weight[number+1] = 0;
    value[number+1]  = 0;


    /* free x_list table */

    destroy_table(x_list, number+1);

    return max_benefit/2;
}


double knapsack_one_duplicate(int* weight, int* value, int* x, int max_weight, int number) {

  int**  x_list;
  double max_benefit, result;
  int    max_benefit_index, i;


  /* generate x_list table */

  x_list = create_table(number+1, number+1);


  /* try all cases */

  max_benefit = knapsack(weight, value, x, max_weight, number);
  max_benefit_index = 0;

  for ( i = 1; i <= number; i++ ) {
    weight[number+1] = weight[i];
    value[number+1]  = value[i];

    result = knapsack(weight, value, x_list[i], max_weight, number+1);

    if ( max_benefit < result ) {
      max_benefit = result;
      max_benefit_index = i;
    }
  }


  /* mark x array from x_list of maximum benefit */

  if ( max_benefit_index != 0 ) {
    for ( i = 1; i <= number; i++ )
      x[i] = x_list[max_benefit_index][i];

    x[max_benefit_index] = 3;

    /* verify x array with x[number+1] */

    // if ( x[max_benefit_index] && x[number+1] )
    //   x[max_benefit_index] = 3; // two duplicated items
    // else if ( x[max_benefit_index] || x[number+1] )
    //   x[max_benefit_index] = 1; // only one item
  }


  /* reset weight, value */

  weight[number+1] = 0;
  value[number+1]  = 0;


  /* free x_list table */

  destroy_table(x_list, number+1);

  return max_benefit;
}



double knapsack_2(int* weight, int* value, int* x, int max_weight, int number) {



  return 1;
}


void print_result(int* x, double result, int number){
  int i;

  for ( i = 1; i <= number; i++ ) {
    switch ( x[i] ) {
      case 1: printf("%d ", i);     break;
      case 2: printf("%dx0.5 ", i); break;
      case 3: printf("%dx2 ", i);   break;
    }
  }
  if ( result - (int)result == 0 )
    printf("%d\n",(int)result);
  else
    printf("%.1lf\n", result);
}


void validate_result(int* value, int* x, double result, int number) {
  int    i;
  double sum_of_value = 0;

  for ( i = 1; i <= number; i++ ) {
    switch ( x[i] ) {
      case 1: sum_of_value += value[i];     break;
      case 2: sum_of_value += value[i] / 2; break;
      case 3: sum_of_value += value[i] * 2; break;
    }
  }

  if ( result == sum_of_value )
    printf("ok.\n");
  else
    printf("wrong answer : %.1lf != %.1lf\n", result, sum_of_value);
}


int** create_table(int height, int width) {
  int **arr;

  arr = (int**) calloc ( height, sizeof(int*) );
  for( int i = 0; i < height; i++ )
      arr[i] = (int*) calloc ( width, sizeof(int) );

  return arr;
}


void destroy_table(int** arr, int height) {
  int i;

  for( i = 0; i < height; i++ )
    free(arr[i]);
  free(arr);
}
