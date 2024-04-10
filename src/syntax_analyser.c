#include "syntax_analyser.h"


bool analyse(phrase_t* phrase, char* syntax, char** arg_list, int* list_len, bool ignore_spaces) {
    
    int list_size = 1;
    *list_len = 0;

    int index = 0;
    int index_const = 0;
    
    int mode = 0;
    bool in_string = false;
    
    char* variable = malloc(sizeof(char));
    int var_len = 0;
    int var_size = 1;

    while (phrase->text[index] != '\0' && syntax[index_const] != '\0') {
        if (syntax[index_const] == '$') {
            mode = 1;
        }

        if (mode>0) {
            if ((!ignore_spaces && phrase->text[index] == ' ') || phrase->text[index] == '.' || phrase->text[index] == '?' || phrase->text[index] == ',') {
                mode = 0;


                if (var_size == var_len + 1) {
                    var_size *= 2;
                    variable = realloc(variable, var_size * sizeof(char));
                }
                variable[var_len] = '\0';

                if (*list_len == list_size) {
                    list_size *= 2;
                    arg_list = realloc(arg_list, list_size * sizeof(char*));
                }
                arg_list[*list_len] = variable;
                variable = malloc(sizeof(char));
                var_len = 0;
                var_size = 1;
                (*list_len)++;
                index_const++;
            } else {
                if (var_size == var_len + 1) {
                    var_size *= 2;
                    variable = realloc(variable, var_size * sizeof(char));
                }
                variable[var_len] = phrase->text[index];
                index++;
                var_len++;
            }
        } else {
            if (phrase->text[index] != syntax[index_const]) {
                break;
            }
            index++;
            index_const++;
        }
    }

    free(variable);
    if (phrase->text[index] != '\0' || syntax[index_const] != '\0') {
        free_l(arg_list, *list_len);
        return false;
    }

    return true;
}

void free_l(char** l, int len) {
    for (int i = 0; i < len; i++) {
        free(l[i]);
    }
    free(l);
}