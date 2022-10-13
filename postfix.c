#include "postfix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// evaluate expression stored as an array of string tokens

double evaluate_postfix_expression(char ** args, int nargs) {
     double endResult;
     struct double_stack * stack;
     stack = double_stack_new(nargs);
     
     for (int i = 0; i < nargs; i++) 
     {
         if (is_operator(args[i])) 
         {
         
             double op2 = double_stack_pop(stack);
             
             double op1 = double_stack_pop(stack);
             double result;
            
             char*add = "+";
             char*minus = "-";
             char*multiply = "X";
             char*divide = "/";
             char*power = "^";
           
             if(strcmp(args[i], add) == 0){
             result = op1 + op2;
             }
             else if(strcmp(args[i], minus) == 0){
             result = op1 - op2;
             }
             else if(strcmp(args[i], multiply) == 0){
             result = op1 * op2;
             }
             else if(strcmp(args[i], divide) == 0){
             result = op1 / op2;
             }
             else if(strcmp(args[i], power) == 0){
             result = pow(op1, op2);
             }
             double_stack_push(stack, result); 
         }
         else {
             double_stack_push(stack, atof(args[i]));  // atof(args[i])
         }
     }
     
     endResult = double_stack_pop(stack);
     double_stack_free(stack);
     return endResult;
}
bool is_operator(char * token) { // a string token
 if(((strcmp(token, "+")) == 0) || ((strcmp(token, "-")) == 0) || ((strcmp(token, "X")) == 0) || ((strcmp(token, "/")) == 0) || ((strcmp(token, "^")) == 0)){
  return true;
 }
  return false;
}

