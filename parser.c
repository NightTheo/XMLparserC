//
// Created by Théo Omnès on 13/05/2021.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "parser.h"

char *getFirstStartTag(char * string) {
    char *open, *close;
    open = strchr(string, '<');
    close = strchr( string, '>');
    char *tag = malloc(sizeof(char)*(close-open));
    if (tag == NULL) return NULL;
    strncpy(tag, open, close - open + 1);
    tag[close - open + 1] = '\0';
    return tag;
}

char * getElementName(char * tag) {
    char *firstSpace;
    char *name = malloc(sizeof(char)*64);
    if (name == NULL) return NULL;
    int8_t end = isElementSelfClosing(tag) ? 3 : 2;
    strncpy(name, tag+1, strlen(tag)-end); // -3 if self-closing, else -2
    firstSpace = strchr(name, ' ');
    if(firstSpace != NULL)
        *firstSpace = '\0';

    //check if the name starts with xml => error: forbidden
    return name;
}

int8_t isElementSelfClosing(char* tag){
    return tag[strlen(tag)-2] == '/' ? 1 : 0;
}

char * generateEndTag(char * tagName){
    char *closeTag = malloc(sizeof(char)*32);
    if(closeTag == NULL) return NULL;

    sprintf(closeTag, "</%s>", tagName);
    return closeTag;

}

char * getElement(char *startTag, char *string){
    if(isElementSelfClosing(startTag)){
        char * element = malloc(sizeof(char)*strlen(startTag));
        if(element == NULL) return NULL;
        return strcpy(element, startTag);
    }
    char * tagName = getElementName(startTag);
    char * closeTag = generateEndTag(tagName);
    char * element = malloc(sizeof(char)*250);
    if(element == NULL) return NULL;

    char * positionOpenTab = strstr(string, startTag);
    char * positionCloseTab = strstr(string, closeTag);

    strncpy(element, positionOpenTab, positionCloseTab - positionOpenTab + strlen(closeTag));

    free(tagName); free(closeTag);
    tagName = closeTag = NULL;
    return element;
}

char * getInnerElement(char *element){
    if(isElementSelfClosing(element))
        return malloc(sizeof(char)*0); // empty string

    char * startTag = getFirstStartTag(element);
    char * nameTag = getElementName(startTag);
    char * endTag = generateEndTag(nameTag);

    char * inner = malloc(sizeof(char) * (strlen(element) - strlen(startTag) - strlen(endTag)));
    if(inner == NULL) return NULL;

    strncpy(inner, element+strlen(startTag), strlen(element) - strlen(startTag) - strlen(endTag));

    free(startTag); free(nameTag); free(endTag);
    startTag = nameTag = endTag = NULL;
    return inner;
}

char * getInnerTag(char *tag){
    char *tagName = getElementName(tag);
    uint8_t end = isElementSelfClosing(tag) ? 2 : 3;
    uint8_t sizeInner = strlen(tag) - strlen(tagName) - 2 - end;
    char *inner = malloc(sizeof(char) * sizeInner);
    if(inner == NULL) return NULL;

    strncpy(inner, tag + strlen(tagName) + 2, sizeInner);
    free(tagName);
    return inner;
}

void getAttributes(char *tag){
    char *innerTag = getInnerTag(tag);
    char *space = innerTag;
    uint8_t nbAttributes = 0;
    while ((space = strstr(space, "\" ")+2) != NULL) {
        nbAttributes++;
        printf("*%s*\n", space);
        space++;
    }
    free(innerTag);
}


char **createArrayString(int8_t sizeArray, int16_t sizeString){
    char **array = malloc(sizeof(char*) * sizeArray);
    if(array == NULL) return NULL;

    for(int i = 0; i < sizeArray; i++){
        array[i] = malloc(sizeof(char)*sizeString);
        if(array[i] == NULL)
            freeStringArray(array, i);
    }
}

void freeStringArray(char **stringArray, int index){
    for(int i = 0; i < index; i++)
        free(stringArray[i]);
    free(stringArray);
    stringArray = NULL;
}

