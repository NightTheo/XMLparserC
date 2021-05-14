#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = stringSelfClosingElementThreeAttributes();

    char *tag = getFirstStartTag(string);
    char *element = getElement(tag, string);
    char **attributes = getAttributes(tag);

    puts(element);
    printStringArray(attributes, getNbAttributes(tag));

    free(tag); free(element); free(attributes);
    return 0;
}
