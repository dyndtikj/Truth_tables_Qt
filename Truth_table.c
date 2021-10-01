#include "Truth_table.h"
#include <math.h>

// Массив для того, чтобы в него можно было поместить двоичный набор
static char binaryInput[100];
// Индекс следующего рассчитанного набора
static int parsedIndex = 0;


// Рекурсивная функция, которая генерирует все возможные двоичные наборы для данного количества переменных
// Затем создает копию списка, но в виде массива струкур, переменным задает двоичные значения из набора
// С помощью функции evaluate() рассчитывает значение булевой функции и помещает это значение
// В массив output по индексу parsedIndex, затем увеличивая индекс
void truthTable(list_t* postfix_list, int* output, unsigned index,unsigned number_of_variables,unsigned lengh_of_tokens)
{
    if (index == number_of_variables) {
        struct token* parsed = (struct token*) malloc(lengh_of_tokens * sizeof(struct token));
        if (parsed == NULL){
            return;
        } else {
            CreateCopyTokenArray(parsed,postfix_list,lengh_of_tokens);

            parseVariables(parsed, lengh_of_tokens,binaryInput);

            evaluate(parsed, output, parsedIndex++, number_of_variables, lengh_of_tokens);

            for (unsigned i = 0; i < lengh_of_tokens; i++){
                free(parsed[i]._mas);
            }
            free(parsed);
        }

        return;
    } else {
        // Генерация бинарных значений
        binaryInput[index] = '0';
        truthTable(postfix_list, output, index + 1, number_of_variables, lengh_of_tokens);
        binaryInput[index] = '1';
        truthTable(postfix_list, output, index + 1, number_of_variables, lengh_of_tokens);
    }
}

// Функция задает двоичные значения переменным
void parseVariables(struct token* arr,unsigned lengh_of_tokens, char* binary)
{
    unsigned j = 0;
    for (unsigned i = 0; i < lengh_of_tokens; i++){
        if (arr[i]._type == VARIABLE && !isBinary(arr[i]._mas)){
            char* variable = (char*) malloc(sizeof(char)*strlen(arr[i]._mas));
            if (variable == NULL) {
                return;
            }
            else {
                strcpy(variable,arr[i]._mas);

                for (unsigned k = i; k < lengh_of_tokens ; k++ ){
                    if (strcmp(arr[k]._mas,variable) == 0){
                        strncpy(arr[k]._mas,"",strlen(arr[k]._mas));
                        arr[k]._mas[0] = binary[j];
                    }
                }
                j++;
                free(variable);
            }
        }
    }
}


// Расчет значения для булевой функции, представленной в постфиксной записи
// Каждая переменная имеет какое-то двоичное значение, присвоенное в функции parseVariables
void evaluate(struct token* arr, int* output, int index,unsigned number_of_variables,unsigned lengh_of_tokens)
{
    struct Stack* stack = createStack(lengh_of_tokens);

    unsigned i = 0;
    int first, second, result ;

    while (i < lengh_of_tokens) {
    // Если переменная заносим в стэк
        if (arr[i]._type == VARIABLE) {
            arr[i]._mas[0]-=48;        // ascii в int
            push(stack, arr[i]);
        } else if (arr[i]._type == OPERATOR){               // Если отрицание то 'вынимаем' из стэка тольку одну(полседнюю) переменную
            if (strcmp(arr[i]._mas,"~")== 0 || (strcmp(arr[i]._mas,"!")== 0)){
                first = (pop(stack))._mas[0];
                result = ~first & 0x1;

            }
            else {
                first = (pop(stack))._mas[0];                // Для других операторов необходимо получить значения двух переменных
                second = (pop(stack))._mas[0];               // Далее произвести рассчёт

                if (strcmp(arr[i]._mas,"+")== 0){
                    result = second | first;
                }
                if (strcmp(arr[i]._mas,"^")== 0){
                    result = second ^ first;
                }
                if (strcmp(arr[i]._mas,"=")== 0){
                    result = (second == first);
                }
                if (strcmp(arr[i]._mas,"#")== 0){
                    result = ~(second | first)& 0x1;
                }
                if (strcmp(arr[i]._mas,"|")== 0){
                    result = ~(second & first) & 0x1;
                }
                if (strcmp(arr[i]._mas,"&")== 0){
                    result = second & first;
                }
                if (strcmp(arr[i]._mas,"->")== 0){
                    result = (~second & 0x1) | first;
                }
            }
            struct token evaluation_result;                 // Результироющее значение неоюходимо занести в стэк и далее работать с этим значением
            evaluation_result._type = VARIABLE;             // Как с переменной
            evaluation_result._mas = (char*)malloc(sizeof (char));
            evaluation_result._mas[0] = result;
            push(stack, evaluation_result);
         }
        i++;
    }

    // Последний элемент стэка - значение булевой функции при заданном двоичном наборе
    output[index] = (pop(stack))._mas[0];
    free(stack->array);
    free(stack);

    // Если заданного двоичного набора был последним, то для дальнейшей рабооты программы двоичный массив переинициализируем символами 0
    // А индекс следующего элемента который должен быть рассчитан переинициализируем 0
    if (index == pow(2,number_of_variables)-1){
        parsedIndex = 0;
        for (int i = 0; i < 100 ; i++){
            binaryInput[i] = '0';
        }
    }
}   
