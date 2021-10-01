#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include "Make_postfix.h"

struct Stack {
    unsigned size;
    struct token* array;
    int top;                                            // индекс последнего элемента в стэке
};

struct Stack* createStack(unsigned size);

int isEmpty(struct Stack* stack);                       // функция проверки стэка на то является ли он пустым

void push(struct Stack* stack, struct token data);      // добавление элемента (последним)

struct token pop(struct Stack* stack);                  // получение и удаление элемента из стэка

struct token next(struct Stack* stack);                 // получение последнего элемента

#endif // STACK_H
