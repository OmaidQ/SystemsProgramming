#ifndef __INFIX_H__
#define __INFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h> 

#include "stack.h"
#include "postfix.h"

double evaluate_infix_expression(char ** expr, int nargs);
bool topOfStack_has_left_bracket(struct double_stack * stack, char** args);
bool stack_has_higher_op(struct double_stack * stack, char * token, char** args);
bool is_left_bracket(char * token);
bool is_right_bracket(char * token);
bool is_operand(char * token);

#endif
