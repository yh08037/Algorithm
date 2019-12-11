#include "graph.h"
#include "PriorityQueue.h"

int max_depth = 0;

enum Algorithm {prim, dijkstra};


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
  V->InDegree = 0;
  V->OutDegree = 0;
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

  From->OutDegree++;
  Target->InDegree++;
  
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


void DFS( Graph* G, Vertex* V, int depth, double length, int max_len, Stack* stack) {
  Edge* E = NULL;
  if ( length > max_len ) return;
  // if ( depth + V->OutDegree < max_depth ) return;
  
  Push(stack, V);
  
  V->Visited = Visited;

  if ( V->x == 100 ) {
    if ( max_depth < depth ) {
      max_depth = depth;
      printf("%d %.1lf %d\n", max_len, length, depth + 1);
      PrintStack(stack, printVertex);
    }
    // ResetVisited(V);
    V->Visited = NotVisited;
    Pop(stack);
    return;
  }


  for ( E = V->AdjacencyList; E != NULL; E = E->Next ) {
    if ( E->Target->Visited == NotVisited )
      DFS( G, E->Target, depth + 1, length + E->Weight, max_len, stack);
  }
  // ResetVisited(V);
  V->Visited = NotVisited;
  Pop(stack);
}


void ResetVisited( Vertex* V ) {
  Edge* E = NULL;

  if ( V == NULL )
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



void Prim( Graph* G, Vertex* start ) {
  template( G, start, prim );
}

void Dijkstra( Graph* G, Vertex* start ) {
  template( G, start, dijkstra );
}

void template( Graph* G, Vertex* start, int mode ) {
  int i = 0;

  Node           StartNode = { 0, start };
  PriorityQueue* PQ        = PQ_Create(10);

  Vertex*  CurrentVertex = NULL;
  Edge*    CurrentEdge   = NULL;

  double*  Weights       = (double*) malloc( sizeof(double) * G->VertexCount );
  Vertex** new_Vertices  = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
  Vertex** Fringes       = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
  Vertex** Precedences   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
  Graph*   new_Graph     = CreateGraph();

  Vertex *NewVertex, *TargetVertex;
  Node Popped, NewNode;
  int FromIndex, ToIndex;

  CurrentVertex = G->Vertices;
  while ( CurrentVertex != NULL ) {
    NewVertex = CreateVertex( CurrentVertex->x, CurrentVertex->y );
    AddVertex( new_Graph, NewVertex);

    Fringes[i]     = NULL;
    Precedences[i] = NULL;
    new_Vertices[i] = NewVertex;
    Weights[i]     = MAX_WEIGHT;
    CurrentVertex  = CurrentVertex->Next;
    i++;
  }

  PQ_Enqueue ( PQ, StartNode );

  Weights[start->Index] = 0;

  while( ! PQ_IsEmpty( PQ ) ) {
    PQ_Dequeue(PQ, &Popped);
    CurrentVertex = (Vertex*)Popped.Data;

    Fringes[CurrentVertex->Index] = CurrentVertex;

    CurrentEdge = CurrentVertex->AdjacencyList;

    while ( CurrentEdge != NULL ) {
      TargetVertex = CurrentEdge->Target;

      if ( Fringes[TargetVertex->Index] == NULL &&
           ((mode == prim     && CurrentEdge->Weight < Weights[TargetVertex->Index]) ||
            (mode == dijkstra && Weights[TargetVertex->Index] < Weights[CurrentVertex->Index] + CurrentEdge->Weight) )) {
        NewNode.Priority = CurrentEdge->Weight;
        NewNode.Data = TargetVertex;
        PQ_Enqueue ( PQ, NewNode );

        Precedences[TargetVertex->Index] = CurrentEdge->From;
        switch ( mode ) {
          case prim:     Weights[TargetVertex->Index] = CurrentEdge->Weight; break;
          case dijkstra: Weights[TargetVertex->Index] = Weights[CurrentVertex->Index] + CurrentEdge->Weight; break;
        }
      }

      CurrentEdge = CurrentEdge->Next;
    }
  }

  for ( i=0; i<G->VertexCount; i++ ) {
    if ( Precedences[i] == NULL ) continue;

    FromIndex = Precedences[i]->Index;
    ToIndex   = i;

    switch ( mode ) {
      case prim:
        AddEdge( new_Vertices[FromIndex], CreateEdge( new_Vertices[FromIndex], new_Vertices[ToIndex], Weights[i] ) );
        break;
      case dijkstra:
        printf("(%d, %d) %.2lf\n", new_Vertices[ToIndex]->x, new_Vertices[ToIndex]->y, Weights[i] );
        break;
    }
  }

  // if ( mode == prim )
    // PrintGraph( new_Graph );

  free( Fringes );
  free( Precedences );
  free( new_Vertices );
  free( Weights );
  DestroyGraph( new_Graph );

  PQ_Destroy( PQ );
}

