#include "../expressions.h"

bool test_expr_func_call(phrase_t* phrase, function_list_t* func_list, environnement_t* env) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, APPEL_VALEUR_FONCTION_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase, env);
    }

    phrase->phraseId = APPEL_VALEUR_FONCTION;

    phrase->function = new_function(result[0], phrase);
    free(result);
    return true;
}
