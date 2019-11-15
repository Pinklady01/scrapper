//
// Created by Marion Mota on 05/11/2019.
//
#include <string.h>
#include <stdlib.h>
#include "struct_src.h"


StringArray *createStringArray(){
    StringArray *newString = malloc(sizeof(StringArray));
    newString->capacity = 20;
    newString->tab = malloc(sizeof(char*)*newString->capacity);
    newString->counter = 0;

    return newString;
}

void addContentString(StringArray *name,char *content){
    if(name->counter == name->capacity){
        name->capacity *=2;
        char **tab = malloc(sizeof(char*)*name->capacity);
        for (int i = 0;i<name->counter;i++){
            tab[i] = name->tab[i];
        }
        free(name->tab);
        name->tab = tab;
    }
    char *newString = malloc(sizeof(char)*strlen(content));
    strcpy(newString,content);
    name->tab[name->counter++] = newString;
}





