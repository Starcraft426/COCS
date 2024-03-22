#include "interpreter.h"

#include "constants.h"
#include "custom_error.h"
#include <string.h>


void interpreter(function_t* function, function_list_t* functions, val_t* result, int layer) {
    if (layer > MAX_RECUSION_DEPTH) {
        custom_error("limite de récursion atteinte", NULL);
    }

    phrase_t* phraseActuelle = function->ast;

    while (phraseActuelle != NULL) {
        // printf("'%s' %d %d %d\n",phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->argsLen, phraseActuelle->interpreterArgsIndex);
        if (phraseActuelle->interpreterArgsIndex < phraseActuelle->argsLen && !phraseActuelle->constant) {
            phraseActuelle->interpreterArgsIndex++;
            phraseActuelle = phraseActuelle->args[phraseActuelle->interpreterArgsIndex - 1];
        } else {
            switch (phraseActuelle->phraseId) {
                case EXECUTION_FONCTION: {
                    function_t* new_func = copy_function(phraseActuelle->function);
                    interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    free_function_t(new_func);

                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case EXECUTION_FONCTION_ARGUMENT: {
                    function_t* new_func = copy_function(phraseActuelle->function);

                    // initialise les arguments
                    for (int i = 0; i < phraseActuelle->argsLen; i++) {
                        copy_val(new_func->env->variable_list[i]->valeur, phraseActuelle->args[i]->valeur);
                    }

                    interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    free_function_t(new_func);

                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case RENVOI_FONCTION: {
                    if (result != NULL && phraseActuelle->argsLen > 0) {
                        copy_val(result, phraseActuelle->args[0]->valeur);
                    }
                    return;
                    break;
                }
                
                case AFFICHE_STR: {
                    printf("%s\n", phraseActuelle->args[0]->text);
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                
                case MAIN_PHRASE: {
                    if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                        phraseActuelle->interpreterInnerIndex++;
                        phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                    } else {
                        phraseActuelle = phraseActuelle->parentPhrase;
                    }
                    break;
                }

                case AFFICHE_EXPR:{
                    if (phraseActuelle->valeur != NULL){
                        if (phraseActuelle->valeur->type == BOOL){
                            if(get_bool(phraseActuelle->valeur)){
                                printf("Vrai\n");
                            }else{
                                printf("Faux\n");
                            }

                        }else if (phraseActuelle->valeur->type == INT){
                            char* str = str_from_int(phraseActuelle->valeur->value);
                            printf("%s\n", str);
                            free(str);
                        
                        }else if (phraseActuelle->valeur->type == FLOAT){
                            char* str = str_from_float(phraseActuelle->valeur->value);
                            printf("%s\n", str);
                            free(str);
                            
                        }else{
                            custom_error("Type non supporté pour l'affichage", phraseActuelle);
                        }
                    }
                    break;
                }

                default:
                    printf("erreur: %d\n", phraseActuelle->phraseId);
                    return;
                    break;
            }
        }
    }
}
