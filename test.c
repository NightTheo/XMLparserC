//
// Created by Théo Omnès on 13/05/2021.
//

#include <stdio.h>
#include "test.h"

void start() {
    printf("-----  XMLparser  -----\n");
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
