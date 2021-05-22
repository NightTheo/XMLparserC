//
// Created by Théo Omnès on 13/05/2021.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "parser.h"


XML *XMLparseString(char *xmlString){
    XML *xml = malloc(sizeof(XML));
    if(xml == NULL) return NULL;
    char *cursor = xmlString;
    char *prologTag = getProlog(xmlString);
    if(prologTag == NULL)
        xml->prolog = NULL;
    else {
        //xml->prolog = getAttributesByTag(prologTag);
        cursor += strlen(prologTag);
        free(prologTag);
    }
    if(countElements(cursor) != 1){
        puts("Error, ONE root element is required");
        return NULL;
    }
    xml->root = newElementsTree(cursor, NULL);
    return xml;

}

void cleanXML(XML **xml){
    XML *tmpXml = *xml;
    if(!xml) return;
    if(tmpXml->root) cleanElementsTree(&tmpXml->root);
    // free prolog
    free(tmpXml);
    xml = NULL;
}

Element *newElementsTree(char *element, Element *brother){
    char *inner = getInnerElement(element);
    int nbSubElements = countElements(inner);
    Element *node = newElementFromString(element, brother);
    if(nbSubElements == 0){ // no children
        node->text = inner;
        return node;
    }
    else{   // has children
        setElementChildren(node, inner);
    }
    free(inner);
    return node;
}

void setElementChildren(Element *father, char *innerElement){
    char *curElement = getFirstElement(innerElement);
    Element *child = newElementFromString(curElement, NULL);
    char *cursor = innerElement + strlen(curElement);
    free(curElement);

    while((curElement = getFirstElement(cursor)) != NULL){
        child = newElementsTree(curElement, child); // set the precedent child found to the brother of the new one
        father->child = child;
        cursor = strstr(cursor, curElement);
        cursor += strlen(curElement)-1;
        free(curElement);
    }
}

void cleanElementsTree(Element **node){
    Element *remove = *node;
    if(!node) return;
    if(remove->brother) cleanElementsTree(&remove->brother);
    if(remove->child) cleanElementsTree(&remove->child);
    freeElement(node);
}

void freeElement(Element **node){
    if(*node != NULL){
        Element *remove = *node;
        if(remove->name) free(remove->name);
        if(remove->text) free(remove->text);
        free(remove);
        node = NULL;
    }
}

Element *newElement(char *name, char *text, char **attributes, Element *littleBrother, Element *elderChild){
    Element *newElement = malloc(sizeof(Element) * 1);
    if(newElement == NULL) return NULL;

    newElement->name = name;
    newElement->text = text;
    //newElement->attributes = attributes;
    newElement->brother = littleBrother;
    newElement->child = elderChild;

    return newElement;
}

Element *newElementFromString(char *stringElement, Element *brother){
    char *inner = getInnerElement(stringElement);
    int nbSubElements = countElements(inner);
    char *name = getElementName(stringElement);
    //char **attributes = getAttributes(stringElement);
    char *text;
    if(nbSubElements > 0){
        text = NULL;
        free(inner);
    }else
        text = inner;

    return newElement(name, text, NULL, brother, NULL);
}

uint8_t countElements(char* string){
    char *ptr1 = string;
    char *ptr2 = string;
    char *curElement;
    int count = 0;
    while((curElement = getFirstElement(ptr1)) != NULL){
        count++;
        ptr2 = strstr(ptr1, curElement);
        ptr1 = ptr2;
        ptr1 += strlen(curElement);
        free(curElement);
    }
    return count;
}

char *getFirstStartTag(char * string) {
    char *open, *close;
    open = strchr(string, '<');
    close = strchr( string, '>');
    if(open == NULL || close == NULL)
        return NULL;

    if(close-open < 0){ // find '>' before '<'
        close = strchr(close+1, '>');   // find the next '>'
        if(close == NULL) return NULL;
    }
    char *tag = malloc(sizeof(char)*(close-open));
    if (tag == NULL) return NULL;
    strncpy(tag, open, close - open + 1);
    tag[close - open + 1] = '\0';
    return tag;
}

char * getElementNameByTag(char * tag) {
    char *firstSpace;
    char *name = malloc(sizeof(char)*64);
    if (name == NULL) return NULL;
    int8_t end = isElementSelfClosing(tag) ? 3 : 2;
    strncpy(name, tag+1, strlen(tag)-end); // -3 if self-closing, else -2
    name[strlen(tag)-end] = '\0';
    firstSpace = strchr(name, ' ');
    if(firstSpace != NULL)
        *firstSpace = '\0';

    return name;
}

char *getElementName(char *element){
    char *tag = getFirstStartTag(element);
    if(tag == NULL) return NULL;
    char *name = getElementNameByTag(tag);
    if(name == NULL) return NULL;
    free(tag);
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
        char * element = malloc(sizeof(char)*strlen(startTag)+1);
        if(element == NULL) return NULL;
        return strcpy(element, startTag);
    }
    char * tagName = getElementNameByTag(startTag);
    char * closeTag = generateEndTag(tagName);
    char * element = malloc(sizeof(char)*250);
    if(element == NULL) return NULL;

    char * positionOpenTab = strstr(string, startTag);
    char * positionCloseTab = strstr(string, closeTag);
    if(positionOpenTab == NULL || positionCloseTab == NULL){
        free(tagName); free(closeTag);
        return NULL;
    }

    strncpy(element, positionOpenTab, positionCloseTab - positionOpenTab + strlen(closeTag));
    element[positionCloseTab - positionOpenTab + strlen(closeTag)] = '\0';

    free(tagName); free(closeTag);
    tagName = closeTag = NULL;
    return element;
}

char * getFirstElement(char *string){
    char *firstStartTag = getFirstStartTag(string);
    if(firstStartTag == NULL)
        return NULL;
    char *element = getElement(firstStartTag, string);
    free(firstStartTag);
    return element;
}

char * getInnerElement(char *element){
    if(isElementSelfClosing(element))
        return malloc(sizeof(char)*0); // empty string

    char * startTag = getFirstStartTag(element);
    char * nameTag = getElementNameByTag(startTag);
    char * endTag = generateEndTag(nameTag);

    char * inner = malloc(sizeof(char) * (strlen(element) - strlen(startTag) - strlen(endTag)));
    if(inner == NULL) return NULL;

    strncpy(inner, element+strlen(startTag), strlen(element) - strlen(startTag) - strlen(endTag));
    inner[strlen(element) - strlen(startTag) - strlen(endTag)] = '\0';

    free(startTag); free(nameTag); free(endTag);
    startTag = nameTag = endTag = NULL;
    return inner;
}

char * getInnerTag(char *tag){
    char *tagName = getElementNameByTag(tag);
    uint8_t end = isElementSelfClosing(tag) ? 2 : 1;
    uint8_t sizeInner = strlen(tag) - strlen(tagName) - 2 - end;
    char *inner = malloc(sizeof(char) * sizeInner);
    if(inner == NULL) return NULL;

    strncpy(inner, tag + strlen(tagName) + 2, sizeInner);
    inner[sizeInner] = '\0';
    free(tagName);
    return inner;
}

char **getAttributesByTag(char *tag){
    int nbAttributes = getNbAttributes(tag);
    if(nbAttributes == 0)
        return NULL;

    char *innerTag = getInnerTag(tag);
    char **splitEqual = splitString("=", innerTag, nbAttributes+1, 100);
    char **splitTag = splitInnerTag(splitEqual, nbAttributes+1);
    char **attributes = joinSplittedTag(nbAttributes, splitTag);

    free(innerTag); free(splitEqual); free(splitTag);
    return attributes;
}

char **getAttributes(char *element){
    char *tag = getFirstStartTag(element);
    if(tag == NULL) return NULL;
    char **attributes = getAttributesByTag(tag);
    if(attributes == NULL) return NULL;
    free(tag);
    return attributes;
}

/*
 * transform:
 * attribute1
 * "value1" attribute2
 * "value2" attribute3
 * "value3"
 *
 * to:
 * attribute1
 * "value1"
 * attribute2
 * "value2"
 * attribute3
 * "value3"
 * */
char **splitInnerTag(char **splitEqual, int sizeSplitEqualArray){
    int sizeNewArray = 2*sizeSplitEqualArray -2;
    char **split = createArrayString(sizeNewArray, 100);
    strcpy(split[0], splitEqual[0]);

    int nbSpaces, index = 1;
    char *border, end[100];
    for(int i = 1; i < sizeSplitEqualArray-1; i++){
        nbSpaces = countCharInString(' ',splitEqual[i]);
        char **splitSpace = splitString(" ", splitEqual[i], nbSpaces+1, 100);
        strcpy(end, splitSpace[nbSpaces]);
        border = strstr(splitEqual[i], end) -1;
        strncpy(split[index], splitEqual[i], border - splitEqual[i]);
        split[index++][border - splitEqual[i]] = '\0';
        strcpy(split[index++], end);
    }
    strcpy(split[index], splitEqual[sizeSplitEqualArray-1]);
    return split;
}

char **splitString(char *separators, char *string, int sizeArray, int sizeString){
    char **split = createArrayString(sizeArray, sizeString);
    char *copy = copyString(string);
    char * strToken = strtok ( copy, separators);

    uint8_t i = 0;
    while ( strToken != NULL ) {
        strcpy(split[i], strToken);
        strToken = strtok ( NULL, separators);
        i++;
    }
    free(copy);
    copy = NULL;
    return split;
}

char **joinSplittedTag(int nbAttributes, char**splitTag){
    char **attributes = createArrayString(nbAttributes, 100);
    char buffer[100];
    for(int i = 0; i < nbAttributes*2; i+=2){
        sprintf(buffer, "%s=%s", splitTag[i], splitTag[i+1]);
        strcpy(attributes[i/2], buffer);
    }
    return attributes;
}

int countCharInString(char delimiter, char *string){
    int count = 0;
    char *cursor = string;
    while((cursor = strchr(cursor, delimiter)) != NULL){
        count++;
        cursor++;
    }
    return count;
}

int getNbAttributes(char *tag){
    return countCharInString('=', tag);
}


char **createArrayString(int8_t sizeArray, int16_t sizeString){
    char **array = malloc(sizeof(char*) * sizeArray);
    if(array == NULL) return NULL;

    for(int i = 0; i < sizeArray; i++){
        array[i] = malloc(sizeof(char)*sizeString);
        if(array[i] == NULL)
            freeStringArray(array, i);
    }
    return array;
}

void freeStringArray(char **stringArray, int index){
    for(int i = 0; i < index; i++)
        free(stringArray[i]);
    free(stringArray);
    stringArray = NULL;
}

char *copyString(char *string){
    char *new = malloc(sizeof(char) * strlen(string));
    if(new == NULL) return NULL;
    strncpy(new, string, strlen(string));
    new[strlen(string)] = '\0';
    return new;
}

int8_t prologExists(char *string){
    char *prolog = getFirstStartTag(string);
    if(prolog == NULL)
        return 0;
    char *name = getElementNameByTag(prolog);
    int8_t result = strcmp(name, "?xml") == 0 && strcmp(prolog+strlen(prolog)-2, "?>") == 0;
    free(prolog); free(name);
    return result;
}

char *getProlog(char *string){
    if(!prologExists(string))
        return NULL;
    return getFirstStartTag(string);
}
