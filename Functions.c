#include "Functions.h"

void removeWhiteSpace(char* arr)
{
    size_t j = 0;
    for (size_t i = 0;arr[i];i++){                              // Посимвольно копируем, если это не символ пробела или табуляции
        if (arr[i] != ' ' && arr[i] != '\t') {
            arr[j++] = arr[i];
        }
    }
    arr[j] = '\0';
}

// Память для массива, в который копируем должна резервироваться ранее
void CreateCopyTokenArray(struct token* distant, list_t* postfix_list, unsigned lengh){
    for (size_t i = 0; i < lengh; i++) {
        distant[i]._type = list_get(postfix_list, i)._type;
        distant[i]._mas = (char*)malloc(sizeof (char)*strlen(list_get(postfix_list, i)._mas));
        strcpy(distant[i]._mas,list_get(postfix_list, i)._mas);
    }
}

char** array_of_unique_variables(list_t Token_list, unsigned lengh,unsigned* unique_count){
    unsigned count = 0;
    char** unique_variables_array = NULL;

    for (unsigned i = 0; i < lengh; i++){
        if (list_get(&Token_list, i)._type == VARIABLE){
            bool should_be_in_array = true;
            for (unsigned j = 0; j < count ;j++){                               // Если переменная уже есть в массиве уникальных переменных
                if (strcmp(list_get(&Token_list, i)._mas,unique_variables_array[j])== 0 ){     // То выставляем флаг, что ее не нужно добавлять
                    should_be_in_array = false;
                    break;
                }
            }
            if (should_be_in_array){
                unique_variables_array = (char**)realloc(unique_variables_array,(sizeof(char*))*(count+1));
                if (unique_variables_array == NULL) exit(EXIT_FAILURE);
                else {
                    unique_variables_array[count] = (char*)malloc(sizeof(char)*strlen(list_get(&Token_list, i)._mas));
                    if (unique_variables_array[count]){
                        strcpy(unique_variables_array[count++] , list_get(&Token_list, i)._mas);
                    }
                    else exit(EXIT_FAILURE);
                }
            }
        }
    }
    *unique_count = count;
    return unique_variables_array;
}

// Получаем на вход строку и проверяем есть ли в начале этой строки подстрока оператора
unsigned is_oper(char* arr){
    char* operators[] ={ "+", "&", "^", "|", "!", "#", "->", "=" };
    for (unsigned i = 0 ; operators[i]; i++){
        if (memcmp(arr, operators[i], strlen(operators[i])) == 0){
            return strlen(operators[i]);
        }
    }
    return 0;                       // Оператор не найден
}

//char** array_of_unique_variables(struct token * tokens, unsigned lengh,unsigned* unique_count){
//    unsigned count = 0;
//    char** unique_variables_array = NULL;

//    for (unsigned i = 0; i < lengh; i++){
//        if (tokens[i]._type == VARIABLE){
//            bool should_be_in_array = true;
//            for (unsigned j = 0; j < count ;j++){                               // Если переменная уже есть в массиве уникальных переменных
//                if (strcmp(tokens[i]._mas,unique_variables_array[j])== 0 ){     // То выставляем флаг, что ее не нужно добавлять
//                    should_be_in_array = false;
//                    break;
//                }
//            }
//            if (should_be_in_array){
//                unique_variables_array = (char**)realloc(unique_variables_array,(sizeof(char*))*(count+1));
//                if (unique_variables_array == NULL) exit(EXIT_FAILURE);
//                else {
//                    unique_variables_array[count] = (char*)malloc(sizeof(char)*strlen(tokens[i]._mas));
//                    if (unique_variables_array[count]){
//                        strcpy(unique_variables_array[count++] , tokens[i]._mas);
//                    }
//                    else exit(EXIT_FAILURE);
//                }
//            }
//        }
//    }
//    *unique_count = count;
//    return unique_variables_array;
//}
