#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"



void insertion_sort(Vertex** arr, int len);

double distance(Vertex* v1, Vertex* v2);



int main() {
  
  // FILE* fp = fopen("hw5ex3.txt", "r");
  FILE* fp = fopen("input.txt", "r");

  int x, y;
  int i, j, num_city;
  int path_length;

  Graph *graph;
  Vertex *start, *curr;
  Vertex **array;
  Stack* stack;


  /* create vertice array */

  fscanf(fp, "%d", &num_city);

  if ( !(array = (Vertex**)malloc(num_city * sizeof(Vertex*))) ) {
    printf("allocation failed.\n");
    return -1;
  } 


  /* read input file */

  for ( i = 0; i < num_city; i++ ) { 
    fscanf(fp, "%d %d\n", &x, &y);
    array[i] = CreateVertex(x, y);
  }
  fclose(fp);


  /* sort vertice array by x */

  insertion_sort(array, num_city);


  /* create graph */

  graph = CreateGraph();

  for ( i = 0; i < num_city; i++ ) {
    curr = array[i];
    AddVertex(graph, curr);

    for ( j = 0; j < i; j++ ) {
      AddEdge(array[j], CreateEdge(array[j], curr, distance(array[j], curr)));
      if ( array[j]->x == curr->x )
        AddEdge(curr, CreateEdge(curr, array[j], distance(curr, array[j])));
    }
  }

  start = array[0];


  stack = CreateStack(num_city);
  
  DFS(graph, start, 0, 0, 200, stack);  ResetVisited(start); ClearStack(stack); printf("\n");

  // Dijkstra(graph, start);


  DestroyStack(stack);
  DestroyGraph(graph);
  free(array);

  return 0;
}



double distance(Vertex* v1, Vertex* v2) {
  return sqrt(pow(v1->x-v2->x, 2) + pow(v1->y-v2->y, 2));
}


void insertion_sort(Vertex** arr, int len) {
  int i, j;
  Vertex* temp;

  for ( i = 1; i < len; i++ ) {
    temp = arr[i];

    for ( j = i ; j > 0 && temp->x < arr[j-1]->x; j-- )
      arr[j] = arr[j-1];

    arr[j] = temp;
  }
}