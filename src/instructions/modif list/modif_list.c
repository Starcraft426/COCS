#include "../instructions.h"
#include "../instructions.h"

bool test_inst_modif_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 34, 21);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0],MODIFICATION_LISTE_S)){
        //printf("modification de la liste %s\n", result_str[1]);
        phrase->phraseId = MODIFICATION_LISTE;
        phrase->liste_call = result_str[1];

    } else {
        free(result_str[1]);
    }

    free_pointers(result_str);

    // renvoie true si l'expression est une modif list
    return phrase->phraseId != -1;
}
