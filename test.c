//
// Created by Théo Omnès on 13/05/2021.
//

#include <stdio.h>
#include "test.h"
#include "parser.h"

void start() {
    printf("-----  XMLparser  -----\n");
}

char * simpleString(){
    return "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
}

char * stringProlog(){
    return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
}

char * stringSimpleElement() {
    return "<firstname>Anna</firstname>";
}

char * stringPerson(){
    return "<person>\n"
           "  <gender>female</gender>\n"
           "  <firstname>Anna</firstname>\n"
           "  <lastname>Smith</lastname>\n"
           "</person>";
}

char * stringPersonWithAttribute() {
    return "<person gender=\"female\">\n"
           "  <firstname>Anna</firstname>\n"
           "  <lastname>Smith</lastname>\n"
           "</person>";
}

char *stringSelfClosingElementOneAttribute() {
    return "<book category=\"web\"/>";
}

char *stringSelfClosingElementTwoAttributes() {
    return "<book category=\"web\" title=\"Clean Code\"/>";
}

char *stringSelfClosingElementThreeAttributes() {
    return "<book category=\"web\" title=\"Clean Code\" author=\"Robert C. Martin\"/>";
}

void printStringArray(char** array, int sizeArray){
    printf("\n--String Array--\n");
    for(int i = 0; i < sizeArray; i++)
        printf("%d*%s*\n",i, array[i]);
    printf("--end of array--\n");
}

char *simpleProlog() {
    return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
}

char *noteWithProlog() {
    return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
           "<note>\n"
           "  <to>Tove</to>\n"
           "  <from>Jani</from>\n"
           "  <heading>Reminder</heading>\n"
           "  <body>Don't forget me this weekend!</body>\n"
           "</note>";
}

void printElement(struct Element element){
    printf("\nname: *%s*", element.name == NULL ? NULL : element.name );
    printf("\ntext: *%s*", element.text == NULL ? NULL : element.text );
    printf("\nattributes: ");
    if(element.attributes == NULL) printf("*(null)*");
    else printStringArray(element.attributes, 3);
    printf("\nbrother: *%s*", element.littleBrother == NULL ? NULL : element.littleBrother->name );
    printf("\nelderChild: *%s*", element.elderChild == NULL ? NULL : element.elderChild->name );
}