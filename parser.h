//
// Created by Théo Omnès on 13/05/2021.
//
#include <stdint.h>

#ifndef XMLPARSER_PARSER_H
#define XMLPARSER_PARSER_H

typedef struct Attribute Attribute;
typedef struct Children Children;
typedef struct Element Element;
typedef struct XML XML;

struct Attribute{
    char *key;
    char *value;
    struct Attribute *next;
};

struct Element {
    char *name;
    char *text;
    char **attributes;
    Element *brother;
    Element *child;
};


struct XML {
    char **prolog;
    Element *root;
};

XML *XMLparseString(char *xml);
Element *newElementsTree(char *element, Element *brother);
void setElementChildren(Element *father, char *innerElement);
void cleanXML(XML **xml);
void cleanElementsTree(Element **node);
void freeElement(Element **node);
Element *newElement(char *name, char *text, char **attributes, Element *littleBrother, Element *elderChild);
Element *newElementFromString(char *stringElement, Element *brother);
uint8_t countElements(char* string);
char *getFirstStartTag(char * string);
char * getElementNameByTag(char * tag);
char *getElementName(char *element);
int8_t isElementSelfClosing(char* tag);
char * generateEndTag(char * tagName);
char * getElement(char *openTag, char *string);
char * getFirstElement(char *string);
char * getInnerElement(char *element);
char **getAttributesByTag(char *tag);
char **getAttributes(char *element);
char **createArrayString(int8_t sizeArray, int16_t sizeString);
void freeStringArray(char **stringArray, int index);
int getNbAttributes(char *tag);
char *copyString(char *string);
char **splitString(char *separators, char *string, int sizeArray, int sizeString);
int countCharInString(char delimiter, char *string);
char **splitInnerTag(char **splitEqual, int sizeSplitArray);
char **joinSplittedTag(int nbAttributes, char**splitTag);
char * getInnerTag(char *tag);
int8_t prologExists(char *string);
char *getProlog(char *string);


#endif //XMLPARSER_PARSER_H
