#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = stringPerson();
    printf("\n*%s", string);
    char *tag = getElementOpenTag(string);
    printf("\n*%s", tag);


    char * element = getElement(tag, string);
    printf("\n*%s*", element);

    free(tag); free(element);
    return 0;
}
