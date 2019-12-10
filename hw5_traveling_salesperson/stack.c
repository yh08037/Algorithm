#include "stack.h"

Stack* CreateStack(int size) {
  Stack* newStack;
  void** newArray;

  if ( !(newStack = (Stack*)malloc(sizeof(Stack))) )
    return NULL;

  if ( !(newArray = (void*)malloc(sizeof(void*)*size)) ) {
    free(newStack);
    return NULL;
  }

  newStack->data = newArray;
  newStack->size = size;
  newStack->top = -1;

  return newStack;
}


void Push(Stack* stack, void* item) {
  if ( stack->top != stack->size - 1 )
    stack->data[++stack->top] = item;
}


void* Pop(Stack* stack) {
  if ( stack->top != -1 )
    return stack->data[stack->top--];
  return NULL;
}


void* Top(Stack* stack) {
  if ( stack->top != -1 )
    return stack->data[stack->top];
  return NULL;
}


void DestroyStack(Stack* stack) {
  ClearStack(stack);
  free(stack);
}


void ClearStack(Stack* stack) {
  stack->top = -1;
}

void PrintStack(Stack* stack, void (*print)(void*)) {
  int i;
  for ( i = 0; i <= stack->top; i++ ) 
    print((stack->data)[i]);
}
