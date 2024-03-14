#include "../instructions.h"

void test_inst_exec_func_args(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str = cut_a_b(phrase->text, 20, 22);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXECUTION_FONCTION_ARGUMENT_S)){
        //printf("execution de la fonction %s avec arguments\n", result_str[1]);
        phrase->phraseId = EXECUTION_FONCTION_ARGUMENT;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free_pointers(result_str);
}
