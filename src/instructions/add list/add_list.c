#include "../instructions.h"
bool test_inst_add_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, AJOUT_LISTE_S, l, &len, false);

    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }
    
    phrase->phraseId = AJOUT_LISTE;
    phrase->valeur = new_val_t(UNDEFINED);
    set_liste(phrase->valeur, getVariable(function->env, l[0])->valeur->liste);

    return true;
}
