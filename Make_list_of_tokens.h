#ifndef MAKE_LIST_OF_TOKENS_H_
#define MAKE_LIST_OF_TOKENS_H_
#include "Functions.h"
#include "Check_functions.h"
#include "malloc.h"
#include "list.h"

list_t make_token_list(char * arr,enum check_expression* check_enum, unsigned* lengh);

#endif // MAKE_LIST_OF_TOKENS_H_
