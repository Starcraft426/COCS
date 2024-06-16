#include "../expressions.h"

bool test_expr_entier(phrase_t* phrase, environnement_t* env) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;
    // printf("%s\n", phrase->text);
    char** result = analyse(phrase, EXPR_ENTIER_S, &len, NUMBER_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase, env);
    }

    int* result_num = eval_number(result[0], (int)strlen(result[0]));

    if (result_num[0]) {
        phrase->phraseId = EXPR_ENTIER;
        phrase->constant = true;
        // printf("%p\n", getValeur(env, phrase->uniqueId));
        set_int(getValeur(env, phrase->uniqueId), result_num[1]);
    } else {
        char* err = malloc((strlen(result[0]) + 32) * sizeof(char));

        strcpy(err, result[0]);
        strcat(err, " isn't recognized as an integer.");

        custom_error(err, phrase, env);
    }
    free(result_num);

    free_l(result, len);

    return true;
};
