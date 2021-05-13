//
// Created by Théo Omnès on 13/05/2021.
//

#ifndef XMLPARSER_PARSER_H
#define XMLPARSER_PARSER_H

char *getElementOpenTag(char * string);
char * getElementName(char * tag);
int8_t isElementSelfClosing(char* tag);


#endif //XMLPARSER_PARSER_H
