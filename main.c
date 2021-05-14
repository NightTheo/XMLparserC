#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = stringSelfClosingElementTwoAttributes();
    char *tag = getFirstStartTag(string);
    printf("\n%s\n", tag);
    char * element = getElement(tag, string);

    getAttributes(tag);

    free(tag); free(element);
    return 0;
}
