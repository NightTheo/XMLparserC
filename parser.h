//
// Created by Théo Omnès on 13/05/2021.
//

#ifndef XMLPARSER_PARSER_H
#define XMLPARSER_PARSER_H

char *getFirstStartTag(char * string);
char * getElementName(char * tag);
int8_t isElementSelfClosing(char* tag);
char * generateEndTag(char * tagName);
char * getElement(char *openTag, char *string);
char * getInnerElement(char *element);
void getAttributes(char *tag);
char **createArrayString(int8_t sizeArray, int16_t sizeString);
void freeStringArray(char **stringArray, int index);

#endif //XMLPARSER_PARSER_H
