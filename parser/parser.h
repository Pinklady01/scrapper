//
// Created by Marion Mota on 05/11/2019.
//


#ifndef SCRAPPER_PARSER_H
#define SCRAPPER_PARSER_H

int calculateFileSize(char *);
void fillFileFromHTML(char *);
int searchEndingChar(int,char *,char *);
char *searchContentBetween2positions(char *,int,int);
void createDirectoryIfNotExist(char *);
char *substr(char *src,int pos,int len);
int mysSrcmp(char *, char *);
int writeFile(char*,char*);

#endif //SCRAPPER_PARSER_H

