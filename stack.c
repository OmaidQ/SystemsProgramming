#include "stack.h"

struct double_stack * double_stack_new(int max_size)
{
  struct double_stack * result;
  result = malloc(sizeof(struct double_stack));
  result -> max_size = max_size;
  result -> top = 0;
  result -> items = malloc(sizeof(double)*max_size);
  return result;
}

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
  assert(this -> top < this -> max_size);
  this -> items[this -> top] = value;
  this -> top++;
}

// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
  double popped;
  assert(this -> top > 0);
  this -> top--;
  popped = this -> items[this -> top];
  return popped;
}
bool double_stack_is_empty(struct double_stack * this) {
  if(this -> top == 0){
  return true;
  }
  return false;
}
void double_stack_free(struct double_stack * this){
  free(this -> items);
  free(this);
}