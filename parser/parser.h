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
int mysSrcmp(char *, char *);
void writeFile(char*,char*);
void readStruct(StringArray* ,char* ,action* );
void createDirectoryFromPath(char *,action* );
char* searchStringBetweenTwoChar(char*,char*, char);
char* createPathFile(char* ,action*);
int isURL(char*);
void downloadFileFromPath(char*,action*);
void freeStruct(StringArray*);
int numberOfOneCharInString(char*,char);
int verifyIfExtension(char*);
void displayStruct(StringArray*);

#endif //SCRAPPER_PARSER_H

