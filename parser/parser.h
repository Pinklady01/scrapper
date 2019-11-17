//
// Created by Marion Mota on 05/11/2019.
//

#ifndef SCRAPPER_PARSER_H
#define SCRAPPER_PARSER_H

#include "../conf_funcs.h"
#include "struct_src.h"

int calculateFileSize(char *);
void fillFileFromHTML(char *,action*);
int searchEndingChar(int,char *,char *);
char *searchContentBetween2positions(char *,int,int);
void createDirectoryIfNotExist(char *,action*);
char *substr(char *src,int pos,int len);
int mysSrcmp(char *, char *);
void writeFile(char*,char*);
void readStruct(StringArray* ,char* ,action* );
void createDirectoryFromPath(char *,action* );
int verifPath(char*,action*);
char* searchStringBetweenTwoChar(char*,char*, char);
char* createPathFile(char* ,action*);
int isURL(char*);

#endif //SCRAPPER_PARSER_H

