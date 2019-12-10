#include "graph.h"


Graph* CreateGraph() {
  Graph* graph = (Graph*)malloc( sizeof( Graph ) );

  graph->Vertices = NULL;
  graph->VertexCount = 0;

  return graph;
}

void DestroyGraph( Graph* G ) {
  Vertex* Vertices;

  while ( G->Vertices ) {
    Vertices = G->Vertices->Next;
    DestroyVertex( G->Vertices );
    G->Vertices = Vertices;
  }

  free( G );
}

Vertex* CreateVertex( int x, int y ) {
  Vertex* V = (Vertex*)malloc( sizeof( Vertex ) );

  V->x = x;
  V->y = y;
  V->Next = NULL;
  V->AdjacencyList = NULL;
  V->Visited = NotVisited;
  V->Index = -1;

  return V;
}

void DestroyVertex( Vertex* V ) {
  Edge* edge;

  while ( V->AdjacencyList != NULL ) {
    edge = V->AdjacencyList->Next;
    DestroyEdge( V->AdjacencyList );
    V->AdjacencyList = edge;
  }

  free( V );
}


Edge* CreateEdge( Vertex* From, Vertex* Target, double Weight ) {
  Edge* E   = (Edge*)malloc( sizeof( Edge ) );

  E->From   = From;
  E->Target = Target;
  E->Next   = NULL;
  E->Weight = Weight;

  return E;
}

void DestroyEdge( Edge* E ) {
  free( E );
}

void AddVertex( Graph* G, Vertex* V ) {
  Vertex* VertexList = G->Vertices;

  if ( !VertexList )
    G->Vertices = V;
  else {
    while ( VertexList->Next )
        VertexList = VertexList->Next;

    VertexList->Next = V;
  }

  V->Index = G->VertexCount++;
}

void AddEdge( Vertex* V, Edge* E ) {
  Edge* AdjacencyList;

  if ( !V->AdjacencyList )
    V->AdjacencyList = E;
  else {
    AdjacencyList = V->AdjacencyList;

    while ( AdjacencyList->Next )
      AdjacencyList = AdjacencyList->Next;

    AdjacencyList->Next = E;
  }
}


void printVertex(void* item) {
  Vertex* vertex = (Vertex*) item;
  printf("%d, %d\n", vertex->x, vertex->y);
}


void DFS( Vertex* V, int depth, double length, int max_len, Stack* stack) {
  Edge* E = NULL;

  if ( length > max_len ) return;
  
  Push(stack, V);

  if ( V->x == 100 ) {
    printf("%d %.2lf %3d\n", max_len, length, depth);
    PrintStack(stack, printVertex);
  }

  V->Visited = Visited;

  for ( E = V->AdjacencyList; E != NULL; E = E->Next ) {
    if ( E->Target->Visited == NotVisited )
      DFS( E->Target, depth + 1, length + E->Weight, max_len, stack);
  }
  Pop(stack);
}


void ResetVisited( Graph* G ) {
  Vertex* V = NULL;
  Edge*   E = NULL;

  if ( ( V = G->Vertices ) == NULL )
      return;

  while ( V != NULL ) {
    V->Visited = NotVisited;

    if ( (E = V->AdjacencyList) == NULL ) {
      V = V->Next;
      continue;
    }

    while ( E != NULL ) {
      E->Target->Visited = NotVisited;
      E = E->Next;
    }

    V = V->Next;
  }
}