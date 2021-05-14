#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = stringPersonWithAttribute();
    char *tag = getFirstOpenTag(string);
    char * element = getElement(tag, string);
    printf("\n*%s*", element);

    char * inner = getInnerElement(element);
    printf("\ninner: *%s*", inner);

    free(tag); free(element); free(inner);
    return 0;
}
