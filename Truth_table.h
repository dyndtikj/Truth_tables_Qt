#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include "Check_functions.h"
#include "Functions.h"
#include "Stack.h"

// Рекурсивная функция, которая генерирует все возможные двоичные наборы для данного количества переменных
// И после рассчетов заполняет массив output со значениями булевой функции
void truthTable(list_t* postfix_list, int* output, unsigned index,unsigned number_of_variables,unsigned lengh_of_tokens);

// Функция задает двоичные значения переменным
void parseVariables(struct token* token_arr,unsigned lengh_of_tokens, char* binary);

// Функция для рассчета значения булевой функции при определенном двоичном наборе
void evaluate(struct token* token_arr, int* output, int index,unsigned number_of_variables,unsigned lengh_of_tokens);

#endif // TRUTH_TABLE_H
