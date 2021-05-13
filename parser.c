//
// Created by Théo Omnès on 13/05/2021.
//

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "parser.h"

char *getElementOpenTag(char * string) {
    char *open, *close;
    char tag[32];
    open = strchr(string, '<');
    close = strchr( string, '>');
    strncpy(tag, open, close - open);
    return tag;
}

char * getElementName(char * tag) {
    char name[32];
    strncpy(name, tag+1, strlen(tag)-1); // -2 if self-closing
    //check if the name starts with xml => error: forbidden
    return name;
}

int8_t isElementSelfClosing(char* tag){
    printf("%c", tag[strlen(tag)-2]);
}


