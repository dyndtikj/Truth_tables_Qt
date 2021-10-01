#ifndef CHECK_FUNCTIONS_H_INCLUDED
#define CHECK_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum type{
    OPERATOR,
    VARIABLE,
    LEFTBRAKE,
    RIGHTBRAKE
};

struct token{
    enum type _type;
    char* _mas;
};

enum check_expression{
    All_is_good,
    Empty_string,
    Uncorrect_expression,
    Uncorrect_operators,
    Too_Long_Variable,
    Operator_without_variable,
    Operator_not_error,
    Uncorrect_parentheses,
};

bool isLetter(char input);
bool isBinary(char *input);
bool isOperator(char input);
bool isDigit(char input);
bool check(char* arr,enum check_expression* check_enum);

#endif // CHECK_FUNCTIONS_H_INCLUDED
