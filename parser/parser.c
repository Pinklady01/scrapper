#include <string.h>
//#include "struct.c"
//#include "parser.h"
int calculateFileSize(char *);
void fillStructFromHTML(char *);
int searchEndingChar2(int,char *,char *);
int searchEndingChar(int,char *,char);
char *searchContentBetween2positions(char *,int,int);
char *substr(char *src,int pos,int len);
int mysSrcmp(char *, char *);

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

void fillStructFromHTML(char *tab){
    //char *newTab=malloc(sizeof(tab));
    //char *tagName=malloc((sizeof(char)*8));
    int endingChar;
    char symbol='>';
    for(int i = 0;i < strlen(tab);i++){
        if(tab[i] == '<'){
            endingChar = searchEndingChar(i,tab,symbol);
            printf("%s\n",searchContentBetween2positions(tab,i,endingChar));
            /*if(mysSrcmp(searchContentBetween2positions(tab,i,searchEndingChar(i,tab,'=')),'<a href=') == 0){
                printf("blop\n");
            }*/
        }
    }
}
int compareTag(char * str1,char *str2){
    mysSrcmp(str1,str2);
}


int searchEndingChar2(int startingChar,char *tab,char *symbol){
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

int searchEndingChar(int startingChar,char *tab,char symbol){
    int counter = startingChar;
    while(tab[counter] != symbol){
            counter++;
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


