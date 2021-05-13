//
// Created by Théo Omnès on 13/05/2021.
//

#ifndef XMLPARSER_PARSER_H
#define XMLPARSER_PARSER_H

char *getElementOpenTag(char * string);
char * getElementName(char * tag);
int8_t isElementSelfClosing(char* tag);
char * generateCloseTag(char * tagName);
char * getElement(char *openTag, char *string);

#endif //XMLPARSER_PARSER_H
