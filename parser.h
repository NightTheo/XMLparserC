//
// Created by Théo Omnès on 13/05/2021.
//
#include <stdint.h>

#ifndef XMLPARSER_PARSER_H
#define XMLPARSER_PARSER_H

typedef struct Attribute Attribute;
typedef struct Children Children;
typedef struct Element Element;

struct Attribute{
    char *key;
    char *value;
    struct Attribute *next;
};

struct Element {
    char *name;
    char *text;
    char **attributes;
    Element *littleBrother;
    Element *elderChild;
};

void XMLparseString(char *xml);
Element *browseXMLRecursively(char *element, Element *brother);
Element *newElement(char *name, char *text, char **attributes, Element *littleBrother, Element *elderChild);
Element *newElementFromString(char *stringElement, Element *brother);
uint8_t countElements(char* string);
char *getFirstStartTag(char * string); //m
char * getElementNameByTag(char * tag); //m
char *getElementName(char *element); //m
int8_t isElementSelfClosing(char* tag);
char * generateEndTag(char * tagName); //m
char * getElement(char *openTag, char *string); //m
char * getFirstElement(char *string); //m
char * getInnerElement(char *element); //m
char **getAttributesByTag(char *tag); //m
char **getAttributes(char *element); //m
char **createArrayString(int8_t sizeArray, int16_t sizeString); //m
void freeStringArray(char **stringArray, int index);
int getNbAttributes(char *tag);
char *copyString(char *string); //m
char **splitString(char *separators, char *string, int sizeArray, int sizeString); //m
int countCharInString(char delimiter, char *string);
char **splitInnerTag(char **splitEqual, int sizeSplitArray); //m
char **joinSplittedTag(int nbAttributes, char**splitTag); //m
char * getInnerTag(char *tag); //m
int8_t prologExists(char *string);
char *getProlog(char *string); //m


#endif //XMLPARSER_PARSER_H
