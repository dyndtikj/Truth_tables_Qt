#include "Make_postfix.h"

// Больший приоритет - большее возвращаемое значение
int precedence(char* input)
{
    if (strcmp(input,"#")  == 0 ||              // Стрелка Пирса
        strcmp(input,"|")  == 0) return 1;      // Штрих Шеффера
    if (strcmp(input,"=")  == 0) return 2;      // Эквивалентность
    if (strcmp(input,"->") == 0) return 3;      // Импликация
    if (strcmp(input,"+")  == 0 ||              // Или
        strcmp(input,"^")  == 0) return 4;      // Исключающее или (сложение по модулю 2)
    if (strcmp(input,"&")  == 0) return 5;      // И
    if (strcmp(input,"~")  == 0 ||
        strcmp(input,"!")  == 0) return 6;      // Не
    return -1;
}
list_t make_postfix(list_t* Token_list,unsigned *len_of_arr,enum check_expression* check_enum)
{
    int index_in_postfix = 0;
    list_t Postfix_list;
    list_init(&Postfix_list);

    // Создается стэк с длиной, каково количество элементов в массиве структур
    struct Stack* stack = createStack(*len_of_arr);
    if (stack == NULL) {
        return Postfix_list;
    }

    for (unsigned i = 0; i < *len_of_arr; i++){
        struct token Token = list_get(Token_list, i);

        if (Token._type == VARIABLE) {
            list_append(&Postfix_list, Token);
            index_in_postfix++;
            continue;
        }
        if (Token._type ==  LEFTBRAKE) {                       // Если '(' заносим в стэк
            push(stack, Token);
            continue;
        }
        if (Token._type == RIGHTBRAKE) {                       // Если ')', то 'вынимаем' из стэка все пока не дошли до '('

            while (!isEmpty(stack) && next(stack)._type != LEFTBRAKE) {
                list_append(&Postfix_list, pop(stack));
                index_in_postfix++;
            }
            if (isEmpty(stack)) {                               // Если для ')' не нашлось пары в виде '(', то несоотвествие скобок
                *check_enum = Uncorrect_parentheses;
            }
            if (next(stack)._type == LEFTBRAKE){
                free(pop(stack)._mas);
            }
            free(Token._mas);
            continue;
        }
        // Если стэк не пустой и последний элемент не '('
        // То если есть операторы с приоритетностью большей или равной, то необходимо извлечь их из стэка
        // Чтобы при в постфиксной записи выполнить сначала действия с большим приоритетом
        if (Token ._type == OPERATOR)
        {
            while (!isEmpty(stack) && precedence(Token._mas) <= precedence(next(stack)._mas) && next(stack)._type != LEFTBRAKE) {
                if (strcmp(next(stack)._mas,"!") != 0 || strcmp(Token._mas,"!") != 0 ){
                    list_append(&Postfix_list, pop(stack));
                    index_in_postfix++;
                }
                else break;
            }
            push(stack, Token);
            continue;
        }
    }

    // 'Вынимаем' из стэка операторы
    while (!isEmpty(stack)) {
        if (next(stack)._type == LEFTBRAKE ){
            *check_enum = Uncorrect_parentheses;
            for(int i = 0; i <= stack->top ; i++){
                free(stack->array[i]._mas);
            }
            break;
        }
        else {
            list_append(&Postfix_list, pop(stack));
            index_in_postfix++;
        }
    }

    free(stack->array);
    free(stack);

    *len_of_arr = index_in_postfix;
    return Postfix_list;
}
