//
// Created by Théo Omnès on 13/05/2021.
//

#ifndef XMLPARSER_TEST_H
#define XMLPARSER_TEST_H

void start();
char * stringSimpleElement();
char * stringPerson();
char * stringPersonWithAttribute();
char *stringSelfClosingElementOneAttribute();
char *stringSelfClosingElementTwoAttributes();
char *stringSelfClosingElementThreeAttributes();
void printStringArray(char** array, int sizeArray);
char *simpleProlog();
char *noteWithProlog();



#endif //XMLPARSER_TEST_H
