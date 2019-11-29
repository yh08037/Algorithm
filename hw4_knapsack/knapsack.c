#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>


#define MAX_LEN 64


void   read_txt_1(int* weight, int* value, int* max_weight, int* number);
void   read_txt_2(int* weight, int* value, int* max_weight_1, int* max_weight_2, int* number);

double knapsack(int* weight, int* value, int* x, int max_weight, int number);
double knapsack_one_split(int* weight, int* value, int* x, int max_weight, int number);
double knapsack_one_duplicate(int* weight, int* value, int* x, int max_weight, int number);
double knapsack_multiple(int* weight, int* value, int* x, int max_weight_1, int max_weight_2, int number);

int    backtrack(int*** benefit, int temp_1, int temp_2, int n, int* weight, int* value, int* x);

void   print_result(int* x, double result, int number);
void   print_result_2(int* x, double result, int number);
void   validate_result(int* weight, int* value, int* x, int max_weight, int number, double result);
void   validate_result_2(int* weight, int* value, int* x, int max_weight_1, int max_weight_2, int number, double result);

int**  create_table(int height, int width);
void   destroy_table(int** arr, int height);
int*** create_table_3D(int a, int b, int c);
void   destroy_table_3D(int*** arr, int a, int b);
int    maximum(int a, int b, int c);


int main(void) {

  int    number, max_weight;
  int    max_weight_1, max_weight_2;  // for knapsack_multiple
  int    weight[MAX_LEN] = {0};
  int    value[MAX_LEN] = {0};
  int    x_1[MAX_LEN] = {0};  // 0 : not in       1: in
  int    x_2[MAX_LEN] = {0};  // 2 : splited
  int    x_3[MAX_LEN] = {0};  // 3 : duplicated
  int    x_4[MAX_LEN] = {0};  // 4 : knapsack 1   5 : knapsack 2
  double result;

	int i;


  /* read input file for problem 1, 2, 3 */

  read_txt_1(weight, value, &max_weight, &number);


  /* problem 1. standard 0-1 knapsack problem */

  result = knapsack(weight, value, x_1, max_weight, number);

  print_result(x_1, result, number);
  validate_result(weight, value, x_1, max_weight, number, result);
  printf("\n");


  /* problem 2. 0-1 knapsack with one item split */

  result = knapsack_one_split(weight, value, x_2, max_weight, number);

  print_result(x_2, result, number);
  validate_result(weight, value, x_2, max_weight, number, result);
  printf("\n");


  /* problem 3. knapsack with one duplicate item */

  result = knapsack_one_duplicate(weight, value, x_3, max_weight, number);

  print_result(x_3, result, number);
  validate_result(weight, value, x_3, max_weight, number, result);
  printf("\n");


  /* problem 4. knapsack with two identical knapsack */

  read_txt_2(weight, value, &max_weight_1, &max_weight_2, &number);

  result = knapsack_multiple(weight, value, x_4, max_weight_1, max_weight_2, number);

  print_result_2(x_4, result, number);
  validate_result_2(weight, value, x_4, max_weight_1, max_weight_2, number, result);
  printf("\n");


  return 0;
}


void read_txt_1(int* weight, int* value, int* max_weight, int* number) {

  char  input_file_name[] = "one_knapsack/input.txt";
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


void read_txt_2(int* weight, int* value, int* max_weight_1, int* max_weight_2, int* number) {

  char  input_file_name[] = "two_knapsack/input.txt";
  // char  input_file_name[] = "input.txt";
  FILE* input_file;
  int   temp_1, temp_2;


  /* read input file */

  *number = 0;
  input_file = fopen(input_file_name, "r");

  while ( 1 ) {
    fscanf(input_file, "%d %d", &temp_1, &temp_2);

    if ( fgetc(input_file) != '\n' ) {
      *max_weight_1 = temp_1;
      *max_weight_2 = temp_2;
      break;
    }

    (*number)++;
    weight[*number] = temp_1;
    value[*number] = temp_2;
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
  }


  /* reset weight, value */

  weight[number+1] = 0;
  value[number+1]  = 0;


  /* free x_list table */

  destroy_table(x_list, number+1);

  return max_benefit;
}


double knapsack_multiple(int* weight, int* value, int* x, int max_weight_1, int max_weight_2, int number) {

  int*** benefit;
	int max_benefit;
  int i, w1, w2, val1, val2;
	int j, k;  // for validation
  int start_1, start_2;
  int temp_1, temp_2;
  int result;



  /* generate benefit table */

  benefit = create_table_3D(number+1, max_weight_1+1, max_weight_2+1);


  /* knapsack : filling table */

  for ( i = 1; i <= number; i++ ) {
   for ( w1 = max_weight_1; w1 >= 0; w1-- ) {
     for ( w2 = max_weight_2; w2 >= 0; w2-- ) {
        val1 = val2 = 0;
        if( weight[i] <= w1 )
          val1 = benefit[i-1][w1 - weight[i]][w2] + value[i];
        if( weight[i] <= w2 )
          val2 = benefit[i-1][w1][w2 - weight[i]] + value[i];
        benefit[i][w1][w2] = maximum(benefit[i-1][w1][w2], val1, val2);
     }
   }
  }



  /* TODO : backtracking */


  start_1 = max_weight_1;
  start_2 = max_weight_2-1;


  result = backtrack(benefit, start_1, start_2, number, weight, value, x);

  // printf("[%d]\n", result);


  /* print table : for validation */

  // for ( i = 0; i <= number; i++ ) {
  //   for ( j = 0; j <= max_weight_1; j++ ) {
  //     for ( k = 0; k <= max_weight_2; k++ ) {
  //       printf("%3d", benefit[i][j][k]);
  //     }
  //     printf("\n");
  //   }
  //   printf("\n");
  // }


  /* memorize max benefit */

  max_benefit = benefit[number][max_weight_1][max_weight_2];


  /* free benefit table */

  destroy_table_3D(benefit, number+1, max_weight_1+1);


  return max_benefit;
}





int backtrack(int*** benefit, int temp_1, int temp_2, int n, int* weight, int* value, int* x ) {

  // printf("(%d %d)\n", temp_1, temp_2);


  if ( n == 0 ) {
    if ( temp_1 == 0 && temp_2 == 0 ) return 1;
    else                              return 0;
  }

  if ( benefit[n-1][temp_1][temp_2] != benefit[n][temp_1][temp_2] ) {


    // put item to sack 1
    if ( temp_1 - weight[n] >= 0 ) {
      if ( benefit[n][temp_1][temp_2] - benefit[n-1][temp_1-weight[n]][temp_2] != value[n] ){
        x[n] = 0;
        return 0;
      }
      if ( backtrack(benefit, temp_1 - weight[n], temp_2, n-1, weight, value, x) ) {
        x[n] = 4;
        return 1;
      }
    }

    // put item to sack 2
    if ( temp_2 - weight[n] >= 0 ) {
      if ( benefit[n][temp_1][temp_2] - benefit[n-1][temp_1][temp_2-weight[n]] != value[n] ){
        x[n] = 0;
        return 0;
      }
      if ( backtrack(benefit, temp_1, temp_2 - weight[n], n-1, weight, value, x) ) {
        x[n] = 5;
        return 1;
      }
    }
  }

  else {  // do not put item
    if ( backtrack(benefit, temp_1, temp_2, n-1, weight, value, x) ) {
      x[n] = 0;
      return 1;
    }
  }

  return 0;
}





void print_result(int* x, double result, int number){
  int i;

  for ( i = 1; i <= number; i++ ) {
    switch ( x[i] ) {
      case 1: printf("%d ", i);						 break;
      case 2: printf("%dx0.5 ", i);        break;
      case 3: printf("%dx2 ", i);					 break;
    }
  }
  if ( result - (int)result == 0 )
    printf("%d\n",(int)result);
  else
    printf("%.1lf\n", result);
}


void print_result_2(int* x, double result, int number) {
  int i;

  for ( i = 1; i <= number; i++ ) {
    if ( x[i] == 4 )
      printf("%d %d ", i, 1);
  }
  for ( i = 1; i <= number; i++ ) {
    if ( x[i] == 5 )
      printf("%d %d ", i, 2);
  }


  if ( result - (int)result == 0 )
    printf("%d\n",(int)result);
  else
    printf("%.1lf\n", result);
}


void validate_result(int* weight, int* value, int* x, int max_weight, int number, double result) {
  int    i;
  double sum_of_value  = 0;
  double sum_of_weight = 0;

  for ( i = 1; i <= number; i++ ) {
    switch ( x[i] ) {
      case 1: sum_of_value  += (double)value[i];
              sum_of_weight += (double)weight[i];
              break;
      case 2: sum_of_value  += ((double)value[i]) / 2;
              sum_of_weight += ((double)weight[i]) / 2;
              break;
      case 3: sum_of_value  += ((double)value[i]) * 2;
              sum_of_weight += ((double)weight[i]) * 2;
              break;
    }
  }

  if ( result != sum_of_value )
    printf("  wrong value  : %.1lf != %.1lf\n", result, sum_of_value);
  else
    printf("  value  : %.1lf == %.1lf\n", result, sum_of_value);

  if ( max_weight < sum_of_weight )
    printf("  wrong weight : %d < %.1lf\n", max_weight, sum_of_weight);
  else
    printf("  weight : %d >= %.1lf\n", max_weight, sum_of_weight);
}


void validate_result_2(int* weight, int* value, int* x, int max_weight_1, int max_weight_2, int number, double result) {
  int    i;
  double sum_of_value;
  double sum_of_weight_1, sum_of_weight_2;

  sum_of_value = sum_of_weight_1 = sum_of_weight_2 = 0;

  for ( i = 1; i <= number; i++ ) {
    switch ( x[i] ) {
      case 4: sum_of_value    += (double)value[i];
              sum_of_weight_1 += (double)weight[i];
              break;
      case 5: sum_of_value    += ((double)value[i]);
              sum_of_weight_2 += ((double)weight[i]);
              break;
    }
  }

  if ( result != sum_of_value )
    printf("  wrong value  : %.1lf != %.1lf\n", result, sum_of_value);
  else
    printf("  value  : %.1lf == %.1lf\n", result, sum_of_value);

  if ( max_weight_1 < sum_of_weight_1 )
    printf("  wrong weight_1 : %d < %.1lf\n", max_weight_1, sum_of_weight_1);
  else
    printf("  weight_1 : %d >= %.1lf\n", max_weight_1, sum_of_weight_1);


  if ( max_weight_2 < sum_of_weight_2 )
    printf("  wrong weight_2 : %d < %.1lf\n", max_weight_2, sum_of_weight_2);
  else
    printf("  weight_2 : %d >= %.1lf\n", max_weight_2, sum_of_weight_2);

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


int*** create_table_3D(int a, int b, int c) {
  int ***arr, i, j;

  arr = (int***) calloc(a, sizeof(int**));
  for ( i = 0; i < a; i++ ) {
    arr[i] = (int**) calloc(b, sizeof(int*));
    for ( j = 0; j < b; j++ ) {
      arr[i][j] = (int*) calloc(c, sizeof(int));
    }
  }

  return arr;
}


void destroy_table_3D(int*** arr, int a, int b) {
  int i, j;

  for ( i = 0; i < a; i++ ) {
    for ( j = 0; j < a; j++ )
      free(arr[i][j]);
    free(arr[i]);
  }
  free(arr);
}


int maximum(int a, int b, int c) {
    int max = a > b ? a : b;
    return c > max ? c : max;
}
