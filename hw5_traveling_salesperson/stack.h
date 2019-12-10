#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct {
  void** data;
  int size;
  int top;
} Stack;

Stack* CreateStack(int size);
void Push(Stack* stack, void* item);
void* Pop(Stack* stack);
void* Top(Stack* stack);
void DestroyStack(Stack* stack);
void ClearStack(Stack* stack);
void PrintStack(Stack* stack, void (*print)(void*));

#endif
