//
// Created by Théo Omnès on 13/05/2021.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "parser.h"

char *getElementOpenTag(char * string) {
    char *open, *close;
    char *tag = malloc(sizeof(char)*32);
    if (tag == NULL) return NULL;
    open = strchr(string, '<');
    close = strchr( string, '>');
    strncpy(tag, open, close - open + 1);
    tag[close - open + 1] = '\0';
    return tag;
}

char * getElementName(char * tag) {
    char *name = malloc(sizeof(char)*32);
    if (name == NULL) return NULL;
    int8_t end = isElementSelfClosing(tag) ? 3 : 2;
    strncpy(name, tag+1, strlen(tag)-end); // -3 if self-closing, else -2
    //check if the name starts with xml => error: forbidden
    return name;
}

int8_t isElementSelfClosing(char* tag){
    if(tag[strlen(tag)-2] == '/')
        return 1;
    else
        return 0;
}


