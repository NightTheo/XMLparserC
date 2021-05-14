#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = noteWithProlog();

    char *prolog = getProlog(string);
    if(prolog == NULL)
        puts("Pas de prologue");
    else {
        char **attributesProlog = getAttributes(prolog);

        printStringArray(attributesProlog, getNbAttributes(prolog));

        freeStringArray(attributesProlog, getNbAttributes(prolog));
        free(prolog);
    }
    return 0;
}
