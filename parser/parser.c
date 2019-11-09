#include <string.h>
//#include "struct.c"
//#include "parser.h"
int calculateFileSize(char *);
void fillStructFromHTML(char *);
int searchEndingChar(int,char *,char *);
char *searchContentBetween2positions(char *,int,int);
char *substr(char *src,int pos,int len);
int mysSrcmp(char *, char *);
int writeFile(char*,char*);

int calculateFileSize(char *fileName){
    FILE *f = fopen(fileName,"r");
    char c;
    int counter = 0;
    while ((c=fgetc(f))!=EOF){
        counter++;
    }
    fclose(f);
    return counter;
}

void fillStructFromHTML(char *tab) {
    char link[] = "a href=";
    char picture[] = "img src=";
    char script[] = "script ";
    int endingChar;
    for (int i = 0; i < strlen(tab); i++) {
        if (tab[i] == '<') {
            endingChar = searchEndingChar(i, tab, ">=");
            if (mysSrcmp(searchContentBetween2positions(tab, i + 1, endingChar), link) == 0) {
                writeFile(searchContentBetween2positions(tab, i, searchEndingChar(i, tab, ">")), "../parser/link.txt");
            } else if (mysSrcmp(searchContentBetween2positions(tab, i + 1, endingChar), picture) == 0) {
                writeFile(searchContentBetween2positions(tab, i, searchEndingChar(i, tab, ">")), "../parser/picture.txt");
            } else if (mysSrcmp(searchContentBetween2positions(tab, i + 1,searchEndingChar(i, tab, "> =")),script) == 0) {
                writeFile(searchContentBetween2positions(tab, i,searchEndingChar(i, tab, ">")),"../parser/script.txt");
            }

        }
    }
}

int writeFile(char* string,char* filename){
    FILE* f=fopen(filename,"a");
        fputs(string,f);
        fputc('\n',f);
    fclose(f);
}


int searchEndingChar(int startingChar,char *tab,char *symbol){
    int counter = startingChar;
    int true = 1;
    while(true == 1){
        for(int i = 0;i <= strlen(symbol);i++){
            if(tab[counter] != symbol[i]){
                continue;
            }else{
                true = 0;
            }
        }
        if(true == 1){
            counter++;
        }
    }
    return counter;
}

char *searchContentBetween2positions(char *tab,int startingChar,int endingChar){
    char *dest = malloc(sizeof(char)*(endingChar-startingChar+1));
    int counter = 0;
    for(int i = startingChar;i<=endingChar;i++){
        dest[counter] = tab[i];
        //printf("%c",tab[i]);
        counter++;
    }
    return dest;
}


char *substr(char *src,int pos,int len) {
    char *dest=NULL;
    if (len>0) {
        dest = (char *) malloc(len+1);
        strncat(dest,src+pos,len);
    }
    return dest;
}

/*
 * return 0 if two strings are identicals
 */
int mysSrcmp(char *strg1, char *strg2){
    while( ( *strg1 != '\0' && *strg2 != '\0' ) && *strg1 == *strg2 ){
        strg1++;
        strg2++;
    }
    if(*strg1 == *strg2){
        return 0;
    }else{
        return *strg1 - *strg2;
    }
}


