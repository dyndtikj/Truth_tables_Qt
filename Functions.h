#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string.h>
#include <malloc.h>
#include "Check_functions.h"
#include "list.h"

void removeWhiteSpace(char* arr);

void CreateCopyTokenArray(struct token* distant, list_t* postfix_list, unsigned lengh);

char** array_of_unique_variables(list_t tokens, unsigned lengh,unsigned* unique_count);

unsigned is_oper(char* arr);

#endif // FUNCTIONS_H_INCLUDED
