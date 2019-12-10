#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define MAX_WEIGHT 16384

enum VisitMode { Visited, NotVisited };


typedef struct tagVertex {
  int               x, y;
  int               Visited;
  int               Index;
  struct tagVertex* Next;
  struct tagEdge*   AdjacencyList;
} Vertex;

typedef struct tagEdge {
  struct tagEdge* Next;
  double          Weight;
  Vertex*         From;
  Vertex*         Target;
} Edge;

typedef struct tagGraph {
  Vertex* Vertices;
  int     VertexCount;
} Graph;

Graph*  CreateGraph();
void    DestroyGraph( Graph* G );

Vertex* CreateVertex( int x, int y);
void    DestroyVertex( Vertex* V );

Edge*   CreateEdge( Vertex* From, Vertex* Target, double Weight );
void    DestroyEdge( Edge* E );

void   AddVertex( Graph* G, Vertex* V );
void   AddEdge( Vertex* V, Edge* E );
void   ResetVisited( Graph* G );

void   printVertex(void* item);
void   DFS( Vertex* V, int depth, double length, int max_len, Stack* stack);
void   ResetVisited( Graph* G );



#endif // GRAPH_H
