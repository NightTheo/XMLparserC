#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {

    start();
    char * string = noteWithProlog();
    puts(string);

    XML *xml = XMLparseString(string);
    freeElementRecursively(&(xml->root));
    return 0;
}
