#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = stringSimpleElement();
    printf("\n*%s", string);
    char *tag = getElementOpenTag(string);
    printf("\n*%s", tag);
    char *name = getElementName(tag);
    printf("\n*%s", name);
    //char *element = getElementName(string);
    //char closeTag[32];


    //printf("\n*%s*", element);

    free(tag); free(name);
    return 0;
}
