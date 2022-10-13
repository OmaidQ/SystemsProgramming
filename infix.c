#include "infix.h"

double evaluate_infix_expression(char ** args, int nargs) 
{
  char** postfix = malloc(sizeof(char*)*nargs);
  struct double_stack*stack = double_stack_new(nargs);
  int count = 0;
  for(int i = 0; i < nargs; i++)
  {
      if(is_operand(args[i]))
      {
          postfix[count] = args[i];
          count++;
      }
      else if(is_operator(args[i]))
      {
          while(stack_has_higher_op(stack, args[i], args))
          {
              int item = double_stack_pop(stack);
              postfix[count] = args[item];
              count++;
          }
          double_stack_push(stack,i);
      }
      else if(is_left_bracket(args[i])){
          double_stack_push(stack,i);
      }
      else if(is_right_bracket(args[i])){
          while(!topOfStack_has_left_bracket(stack, args))
          {
              int item = double_stack_pop(stack);
              postfix[count] = args[item];
              count++;
          }
          int item = double_stack_pop(stack);
          assert(is_left_bracket(args[item]));
      }
  }
  while(!double_stack_is_empty(stack))
  {
    int item = double_stack_pop(stack);
    postfix[count] = args[item];
    count++;
  }
  double_stack_free(stack);
  return evaluate_postfix_expression(postfix, count);
}
bool topOfStack_has_left_bracket(struct double_stack * stack, char** args){
    if(double_stack_is_empty(stack)){
     return false;
    }
    int index = double_stack_pop(stack);
    if((strcmp(args[index], "(")) == 0)
    {
        double_stack_push(stack, index);
        return true;
    }
    double_stack_push(stack, index);
    return false;
}
bool stack_has_higher_op(struct double_stack * stack, char * token, char** args){
    if(double_stack_is_empty(stack)){
     return false;
    }
    int index = double_stack_pop(stack);
    if(is_operator(args[index]))
    {
        if((strcmp(args[index], token)) == 0) //args[index] >= token[0]
        { 
          double_stack_push(stack, index);
          return true;
        }
        else if ((strcmp(args[index], "+")) == 0 && (strcmp(token, "-")) == 0) // read from Left to right in stack, +- , + has greater precedence
        {
          double_stack_push(stack, index);
          return true;
        }
        else if ((strcmp(args[index], "/")) == 0 && (strcmp(token, "X")) == 0) // read from Left to right in stack, /X , / has greater precedence
        {
          double_stack_push(stack, index);
          return true;
        }
        else if (args[index][0] > token[0]) //comparing ascii codes (e.g X > /, - > + which tests all other remaining cases)
        {
          double_stack_push(stack, index);
          return true;
        }
    }
    double_stack_push(stack, index);
    return false;
}
bool is_left_bracket(char * token){ 
    if((strcmp(token, "(")) == 0)
    {
        return true;
    }
    return false;
}
bool is_right_bracket(char * token){
    if((strcmp(token, ")")) == 0)
    {
        return true;
    }
    return false;
}
bool is_operand(char * token){ 
  if(token[0] == '-')
  {
      if((isdigit(token[1])) > 0)
      {
          return true;
      }
  }
  else if((isdigit(token[0])) > 0)
  {
      return true;
  }
  return false;
}

