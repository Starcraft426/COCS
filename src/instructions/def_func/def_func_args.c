#include "../instructions.h"

bool test_inst_def_func_args(phrase_t* phrase, function_list_t* function_list) {
    if (phrase->phraseId != NO_ID) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, DEFINITION_FONCTION_ARGUMENT_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }

    phrase->phraseId = DEFINITION_FONCTION_ARGUMENT;
    // phrase->constant = true;
    function_t* new_func = new_function(result[0], phrase);

    for (int i = 1; i < len; i++) {
        addToVariableList(new_func->env, new_variable(result[i], new_val_t(UNDEFINED)));
    }
    new_func->function_arg_count = len - 1;
    phrase->function = new_func;
    addToFunctionList(function_list, new_func);

    free(result);
    return true;
}
