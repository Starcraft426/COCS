#include "custom_error.h"

#include <stdio.h>
#include <stdlib.h>

void custom_error(char* err_message, phrase_t* phrase) {
    phrase->error = true;
    fprintf(stderr, "\n\n========== ERROR ===========\n\n");
    fprintf(stderr, "Une erreur est survenue avec le message suivant:\n%s\n\n", err_message);
    
    if (phrase != NULL){
        phrase->error = true;
        while (phrase->parentPhrase != NULL) {
            phrase = phrase->parentPhrase;
        }
        fprintf(stderr, "Dans le code suivant: \n");
        printPhrase(phrase);
    }
    exit(1);
}