#include "Check_functions.h"

// Является ли символ буквой
bool isLetter(char input)
{
    return (input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z');
}

bool isBinary(char *input)
{
    return (!strcmp(input,"0") || !strcmp(input,"1"));
}

// Является ли символ оператором или его частью
bool isOperator(char input)
{
    return (input == '+' || input == '|' || input == '^' || input =='#' || input =='-' || input == '='
            || input == '>' || input == '&' || input == '~' || input == '!');
}

bool isDigit(char input){
    return (input >= '0' && input <='9');
}

bool check(char* arr, enum check_expression* check_enum){
    for (int i = 0;arr[i];){
        // Проверка переменной, является ли ее длина допустимой
        if (isLetter(arr[i])){
            int j = 1;
            while (isLetter(arr[i+1])|| isDigit(arr[i+1])){
                j++;
                i++;
            }
            if (j > 3){
                *check_enum = Too_Long_Variable;
                return false;
            }
        }
        // Проверка нет ли ситуаций когда два оператора идут друг за другом
        // но два оператор отрицания - исключение, он может располагать после другого оператора
        if (isOperator(arr[i])&&isOperator(arr[i+1])&&(arr[i+1]!='!')&&(arr[i+1]!='>')){
            *check_enum = Uncorrect_operators;
            return false;
        }

        // Проверка, нет ли ситуаций, когда после оператора не стоит переменной или скобочки
        // x+y+  - неправильное выражение
        if (isOperator(arr[i]) && arr[i+1]!='!'
                && (arr[i+1]!='>')&& (arr[i+1]!='(')
                &&(!isLetter(arr[i+1]))&&(!isDigit(arr[i+1]))){
            *check_enum = Operator_without_variable;
            return false;
        }
        if (isOperator(arr[i])&& (arr[i]!='!')){
            if (i == 0){
                *check_enum = Operator_without_variable;
                return false;
            }
            else if (!isLetter(arr[i-1])&& !isDigit(arr[i-1])&& arr[i-1] != '!'
                     && arr[i-1] != '-'&& arr[i-1] != ')' && arr[i-1] != '('){
                *check_enum = Operator_without_variable;
                return false;
            }
        }

        // Оператор отрицания не может быть после перемнной или скобки ')'
        if (i>0 && arr[i] == '!' && (arr[i-1] == ')'
                || (isLetter(arr[i-1])||isDigit(arr[i-1])))){
            *check_enum = Operator_not_error;                                  // x!y - недопустимое выражение
            return false;
        }
        i++;
    }
    if (arr[0] != '\0'){
        *check_enum = All_is_good;
        return true;
    }
    else return false;
}
