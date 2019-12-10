#include "graph.h"
#include <stdio.h>

// void printVertex(void* item) {
//   Vertex* vertex = (Vertex*) item;
//   printf("(%d, %d)\n", vertex->x, vertex->y);
// }


int main() {
    Vertex* a = CreateVertex(1, 2);
    Vertex* b = CreateVertex(3, 4);
    Vertex* c = CreateVertex(5, 6);
    Vertex* d = CreateVertex(7, 8);
    Stack* s = CreateStack(10);

    Push(s, a);
    Push(s, c);
    Push(s, d);
    Push(s, b);

    PrintStack(s, printVertex);

    Pop(s);

    PrintStack(s, printVertex);



    free(a);
    free(b);
    free(c);
    free(d);
    free(s);
    
    return 0;
}