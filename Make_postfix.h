#ifndef MAKE_POSTFIX_H
#define MAKE_POSTFIX_H

#include "Stack.h"
#include "Check_functions.h"
#include "Functions.h"
#include "Make_list_of_tokens.h"

int precedence(char* input);

list_t make_postfix(list_t* Token_list,unsigned *len_of_arr,enum check_expression* check_enum);

#endif // MAKE_POSTFIX_H
