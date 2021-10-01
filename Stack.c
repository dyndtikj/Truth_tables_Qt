#include "Stack.h"

/* Создается стэк, выделяется память
 * Инициализируется переменная - size (размер)
 * Переменная top = -1 так как стэк пустой, после первого добавления top = 0
 */
struct Stack* createStack(unsigned size)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof (struct Stack));
    if (stack == NULL)  exit(EXIT_FAILURE);

    stack->size = size;
    stack->array = (struct token*) malloc(sizeof (struct token) * stack->size);
    if (stack->array == NULL)  exit(EXIT_FAILURE);

    stack->top = -1;
    return stack;
}

int isEmpty(struct Stack* stack)
{
    return (stack->top == -1);
}

void push(struct Stack* stack, struct token data)
{
    stack->array[++stack->top] = data;  // Сначала увеличиваем на 1 индекс последнего элемента и затем помещаем данные в массив
}

// 'Вынимаем' последний элемент и значение индекса последнего элемента уменьшаем на 1
struct token pop(struct Stack* stack)
{
    if (!isEmpty(stack)) {
        return (stack->array[stack->top--]);
    }
    else exit(1);
}

// Получение последнего элемента стэка
struct token next(struct Stack* stack)
{
    return (stack->array[stack->top]);
}
