/* Directions: complete the code by filling in "FILL" parts
 *   adding functions and variables is allowed
 *   do not change print and file load/save
 *   do not use your compiler-specific libraries
 * Note: TIME in seconds is measured
 * FILL parts: insertion and merge sort on heavy arrays
 */

/* Insertion sort and merge sort on arrays of heavy load of items
 * COMP319 Algorithms, Fall 2019
 * School of Electronics Engineering, Kyungpook National University
 * Instructor: Gil-Jin Jang
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>	// to measure time

#define MEASURE_TIME    // to measure execution time

/////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
/* time measurement example */
/*
   clock_t start, end;
   double cpu_time_used;

   start = clock();
   ... // Do the work.
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   */

/* from GJANG: not sure if the above works with Windows */
#endif

#define CHECK_IF_SORTED
#ifdef CHECK_IF_SORTED
#endif

/////////////////////////////////////////////////////////////
// file load and save of heavy load of items
/////////////////////////////////////////////////////////////
long *readkeys_textfile( const char infile[], int *pN )
  // returns an array of long integers, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
  long *A, tmp;
  int i;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return NULL;
  }
  else {
    // check for number of elements
    if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
      fprintf(stderr, "cannot read number of elements %s\n",infile);
      return NULL;
    }
    else {
      A = (long*)malloc(sizeof(long)*(*pN));
      for (i=0; i<(*pN); i++) {
	if ( fscanf(fp, "%ld", &tmp) != 1 ) {
	  fprintf(stderr, "cannot read value at %d/%d\n",i+1,(*pN));
	  *pN = i;	// read data items
	  return A;
	}
	else A[i] = tmp;
      }
    }
    fclose(fp);
    return A;
  }
}

/////////////////////////////////////////////////////////////
// definition basic function of heavy load of items
/////////////////////////////////////////////////////////////
#define LOAD_SIZE	4096
struct HLoad {
  long key;
  long ManyItems[LOAD_SIZE];
};

void fill_hload(struct HLoad *pH, long key)
{
  int i;
  pH->key = key;
  // fill ManyItems with the key
  for (i=0; i<LOAD_SIZE; i++) pH->ManyItems[i] = key;
}

void copy_hload(struct HLoad *dst, struct HLoad *src)
{
  dst->key = src->key;
  memcpy(dst->ManyItems, src->ManyItems, sizeof(long)*LOAD_SIZE);
}

long pick_random_item( struct HLoad *pH )
  // pick an item from HeavyItem randomly
  // to check if items are maintained correctly
  // if key is changed only, values in the itmes may not match key
{
  return pH->ManyItems[rand()%LOAD_SIZE];
}

/////////////////////////////////////////////////////////////
// more functions for heavy load of items
/////////////////////////////////////////////////////////////
void print_heavyload_items_randomly( struct HLoad HL[], int N )
{
  int i;
  printf("[");
  for (i=0; i<N; i++) printf("%ld ",pick_random_item(HL+i));
  printf("]\n");
}

struct HLoad *longArray2HLoadArray(long A[], int N)
{
  struct HLoad *HL;
  int i;

  HL = (struct HLoad*)malloc(sizeof(struct HLoad)*N);
  for (i=0; i<N; i++) {
    fill_hload(HL+i,A[i]);
  }

  return HL;
}

struct HLoad *readkeys_textfile_heavyload( const char infile[], int *pN )
{
  struct HLoad *HL;
  long *A;

  A = readkeys_textfile(infile, pN);
  if ( A != NULL && *pN > 0 ) {
    HL = longArray2HLoadArray(A,*pN);
    free(A);
    return HL;
  }
  else return NULL;	// failed
}

void savekeys_textfile_heavyload( const char outfile[],
    struct HLoad HL[], int N )
  // save the given array of long integers, with its sie N
  // to file whose name given by outfile[]
{
  int i;
  FILE *fp;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file for write %s\n",outfile);
  }
  else {
    // save number of elements
    fprintf(fp, "%d\n",N);
    for (i=0; i<N; i++) fprintf(fp, "%ld ",pick_random_item(HL+i));
    fprintf(fp,"\n");
    fclose(fp);
  }
}

/////////////////////////////////////////////////////////////
// insertion sort
// GJ: already implemented
// Note: changes from standard arraysort
//   Assignment: key = i ==> copy_hload(&keyload, &(HA[i]))
//   Comparison: A[j] > key ==> HA[j].key > keyload.key
/////////////////////////////////////////////////////////////
void insertion_sort_heavy( struct HLoad HA[], int N )
{
  int i, j;
  struct HLoad keyload;
  for (i=1; i<N; i++) {
    //key = i;
    //for (j=i-1; j >= 0 && A[j] > key ; j--) A[j+1] = A[j];
    //A[j+1] = key;
    copy_hload(&keyload,HA+i);
    for (j=i-1; j >= 0 && HA[j].key > keyload.key ; j--) {
      copy_hload(HA+(j+1),HA+j);
    }
    copy_hload(HA+(j+1),&keyload);
  }
}

/////////////////////////////////////////////////////////////
// merge sort
// GJ Note: from merge sort in your arraysort.c
//   change the assignment with copy_hload(),
//   and value comparison with key value comparison
/////////////////////////////////////////////////////////////
/* GJ: may add any additional functions */


void merge_heavy(struct HLoad A[], struct HLoad Tmp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;

    for (int k = left; k <= right; k++) {
      if      (i > mid)             copy_hload(Tmp+k, A+(j++));
      else if (j > right)           copy_hload(Tmp+k, A+(i++));
      else if (A[j].key < A[i].key) copy_hload(Tmp+k, A+(j++));
      else                          copy_hload(Tmp+k, A+(i++));
    }
}


void split_merge_heavy( struct HLoad A[], struct HLoad Tmp[],
    int left, int right )
{
  if ( right <= left ) return;
  int mid = left + (right - left) / 2;
  split_merge_heavy(Tmp, A, left, mid);
  split_merge_heavy(Tmp, A, mid+1, right);
  merge_heavy(A, Tmp, left, mid, right);     // change the role of A and Tmp.
}

// A: arrays to be sorted, and to store output (fully sorted)
// Tmp: temporary space, size is at least right-left+1
// Tmp[0] is for A[left] (sorted) ... Tmp[right-left] is for A[right] (sorted)
void merge_sort_heavy( struct HLoad A[], struct HLoad Tmp[],
    int left, int right )
{
  for (int i = left; i <= right; i++)
    copy_hload(Tmp+i, A+i);
  split_merge_heavy(Tmp, A, left, right);
}


/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
/* File name by Argument input -> scanf read
 * Input file name can be typed in the terminal
 * Update on 9/24: element size is changed to long,
 * to distinguish array index easily
 * Update on 9/25: file reading is moved to a function readkeys_textfile()
 */
int main()
{
  int numElements;
  struct HLoad *HA;	// to store data to be sorted
  struct HLoad *HTmp;	// merge sort only

  /* for file name, max length 1023 including path */
  char infile[1024], outfile[1024];
  int method;

#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
#endif

  /* file name given by keyboard */
  /* file name given by keyboard */
  printf("Input file name? ");
  scanf("%s",infile);
  printf("Output file name? ");
  scanf("%s",outfile);

  printf("Method (1: insertion, 2: merge)? ");
  scanf("%d",&method);

  start = clock();

  /* read text file of integers:
   * number_of_intergers integer1 integer2 ... */
  HA = readkeys_textfile_heavyload(infile, &numElements);

  if ( HA != NULL && numElements > 0 ) {
    // print all if not too many
    if ( numElements < 100 )	// GJ: comment out this line to always display
    {
      print_heavyload_items_randomly(HA, numElements);
      printf("%d Loaded\n", numElements);
    }

    switch ( method ) {
      case 1:	// insertion sort
	insertion_sort_heavy(HA, numElements);
	break;
      case 2:	// merge sort
	HTmp = (struct HLoad*)malloc(sizeof(struct HLoad)*numElements);
	merge_sort_heavy(HA, HTmp, 0, numElements-1);
	free(HTmp);
	break;
      default:
	break;
    }

    // print all if not too many
    if ( numElements < 100 )	// GJ: comment out this line to always display
    {
      print_heavyload_items_randomly(HA, numElements);
    }

    // save results
    savekeys_textfile_heavyload(outfile, HA, numElements);

    // once allocated, should be freed after use
    free(HA);
  }

#ifdef MEASURE_TIME
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("TIME %.5f seconds\n",cpu_time_used);
#endif

  return 0;
}
