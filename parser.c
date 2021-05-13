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

char * generateCloseTag(char * tagName){
    char *closeTag = malloc(sizeof(char)*32);
    if(closeTag == NULL) return NULL;

    sprintf(closeTag, "</%s>", tagName);
    return closeTag;

}

char * getElement(char *openTag, char *string){
    if(isElementSelfClosing(openTag)){
        char * element = malloc(sizeof(char) * strlen(openTag));
        return strcpy(element, openTag);
    }

    char * tagName = getElementName(openTag);
    char * closeTag = generateCloseTag(tagName);
    char * element = malloc(sizeof(char)*250);
    if(element == NULL) return NULL;

    char * positionOpenTab = strstr(string, openTag);
    char * positionCloseTab = strstr(string, closeTag);

    strncpy(element, positionOpenTab, positionCloseTab - positionOpenTab + strlen(closeTag));

    free(tagName); free(closeTag);
    tagName = closeTag = NULL;
    return element;
}


