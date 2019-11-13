#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct_src.h"
#include "parser.h"

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

void createDirectoryIfNotExist(char *directory){
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        mkdir(directory, 0700);
    }
}

void fillFileFromHTML(char *tab) {
    char link[] = "a href=";
    char picture[] = "img src=";
    char script[] = "script ";
    char css[]="link ";
    int endingChar;
    StringArray *arrayLink = createStringArray();
    StringArray *arrayPicture = createStringArray();
    StringArray *arrayScript = createStringArray();
    StringArray *arrayCss = createStringArray();

    for (int i = 0; i < strlen(tab); i++) {
        if (tab[i] == '<') {
            endingChar = searchEndingChar(i, tab, ">=");
            if (mysSrcmp(searchContentBetween2positions(tab, i + 1, endingChar), link) == 0) {
                addContentString(arrayLink,searchContentBetween2positions(tab, i, searchEndingChar(i, tab, ">")));
                //writeFile(searchContentBetween2positions(tab, i, searchEndingChar(i, tab, ">")), "../parser/docTemp/link.txt");
            } else if (mysSrcmp(searchContentBetween2positions(tab, i + 1, endingChar), picture) == 0) {
                addContentString(arrayPicture,searchContentBetween2positions(tab, i, searchEndingChar(i, tab, ">")));
                //writeFile(searchContentBetween2positions(tab, i, searchEndingChar(i, tab, ">")), "../parser/docTemp/picture.txt");
            } else if (mysSrcmp(searchContentBetween2positions(tab, i + 1,searchEndingChar(i, tab, "> =")),script) == 0) {
                addContentString(arrayScript,searchContentBetween2positions(tab, i,searchEndingChar(i, tab, ">")));
                //writeFile(searchContentBetween2positions(tab, i,searchEndingChar(i, tab, ">")),"../parser/docTemp/script.txt");
            } else if (mysSrcmp(searchContentBetween2positions(tab, i + 1,searchEndingChar(i, tab, "> ")),css) == 0) {
                addContentString(arrayCss,searchContentBetween2positions(tab, i,searchEndingChar(i, tab, ">")));
                //writeFile(searchContentBetween2positions(tab, i,searchEndingChar(i, tab, ">")),"../parser/docTemp/css.txt");
            }
        }
    }
    printf("execution finie\n");

    //fonction qui va parcourir les structures
    //pour src= dans link et script ==> créer les directory.
    //      Pour créer les directory: lire le src avant les "/" si n'existe pas dans les fichiers, le créer.
    //Télécharger le fichier dans le bon dossier.
}

void writeFile(char* string,char* filename){
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
    char *dest = malloc(sizeof(char)*(endingChar-startingChar+2));
    int counter = 0;
    for(int i = startingChar;i<=endingChar;i++){
        dest[counter] = tab[i];
        counter++;
    }
    dest[counter]='\0';
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


