#include "Make_list_of_tokens.h"

list_t make_token_list(char * arr, enum check_expression* check_enum, unsigned* len){
    size_t len_of_array = 0;

    list_t l;
    list_init(&l);

    // Создаем связанный список токенов
    while (*arr != '\0'){
        unsigned lengh = 0;
        if (isLetter(arr[lengh])){                          // Переменная не может начинаться с цифры, если была найдена буква,то
            lengh++;                                        // Находим длину переменной
            while (isLetter(arr[lengh])|| isDigit(arr[lengh])){
                lengh++;
            }
            struct token Tok;
            Tok._mas = (char*)malloc(lengh * sizeof (char) + 1);
            if (Tok._mas){
                strncpy(Tok._mas,arr,lengh);
                Tok._mas[lengh] = '\0';
                Tok._type = VARIABLE;
                list_append(&l,Tok);
                arr+=lengh;
                len_of_array++;
                continue;
            } else {
                list_delete(&l);
                *len = 0;
                return l;
            }
        }
        if (arr[lengh] == ')'){
            struct token Tok;
            Tok._mas = (char*)malloc(sizeof (char) * 2);
            if (Tok._mas){
                Tok._mas[lengh] = arr[lengh];
                lengh++;
                Tok._mas[lengh] = '\0';
                Tok._type = RIGHTBRAKE;
                list_append(&l,Tok);
                arr+=lengh;
                len_of_array++;
                continue;
            }else {
                list_delete(&l);
                *len = 0;
                return l;
            }
        }
        if (arr[lengh] == '('){
            struct token Tok;
            Tok._mas = (char*)malloc(sizeof (char) * 2);
            if (Tok._mas){
                Tok._mas[lengh] = arr[lengh];
                lengh++;
                Tok._mas[lengh] = '\0';
                Tok._type = LEFTBRAKE;
                list_append(&l,Tok);
                arr+=lengh;
                len_of_array++;
                continue;
            }else {
                list_delete(&l);
                *len = 0;
                return l;
            }
        }
        lengh = is_oper(arr);
        // Если найден оператор
        if (lengh){
            struct token Tok;
            Tok._mas = (char*)malloc(lengh * sizeof (char) + 1);
            if (Tok._mas){
                strncpy(Tok._mas,arr,lengh);
                Tok._mas[lengh] = '\0';
                Tok._type = OPERATOR;
                list_append(&l,Tok);
                arr+=lengh;
                len_of_array++;
                continue;
            } else {
                list_delete(&l);
                *len = 0;
                return l;
            }
        } else if (!lengh){                         // Если даже оператор не был найден, то либо некорректный символ
            *check_enum = Uncorrect_expression;     // Либо некорректная запись переменной или оператора
        }
    }
    *len = len_of_array;
    return l;
}
