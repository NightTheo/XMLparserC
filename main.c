#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = stringSimpleElement();
    printf("\n%s", string);
    char *element = getElementName(string);
    char closeTag[32];
    sprintf()

    printf("\n*%s*", element);

    return 0;
}
