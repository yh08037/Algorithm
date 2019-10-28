#include <stdio.h>

struct stack {
  char* array[1024];
  int top;
} stack;

void clean_stack() {
  stack.top = -1;
}

void push(char* str) {
  stack.array[++stack.top] = str;
}

char* pop() {
  if ( stack.top < 0 )
    return NULL;
  return stack.array[stack.top--];
}

void print_stack() {
  for ( int i = 0; i <= stack.top; i++ )
    printf("%s", stack.array[i]);
}

int main() {
  clean_stack();

  char str1[4096] = "hello, world!";
  char str2[4096] = "binary search tree!";


  push(str1);
  print_stack();
  printf("\n");

  push(str2);
  print_stack();
  printf("\n");

  while ( pop() ) {
    print_stack();
    printf("\n");
  }

  return 0;
}
