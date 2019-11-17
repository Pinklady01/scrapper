#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct_src.h"
#include "parser.h"
#include "../scrap_funcs.h"
#include <dirent.h>

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

void createDirectoryIfNotExist(char *directory, action* a){
    struct stat st = {0};
    char* pathSearch = createPathFile(directory,a);
    if (stat(pathSearch, &st) == -1) {
        mkdir(pathSearch, 0700);
    }
}

void fillFileFromHTML(char *tab, action* a) {
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
    readStruct(arrayPicture,"src=\"",a);
    readStruct(arrayScript,"src=\"",a);
    readStruct(arrayCss,"href=\"",a);
    printf("execution finie\n");

    //TODO: fonction Télécharger le fichier dans le bon dossier.
}

void readStruct(struct StringArray* structArray,char *string, action* a) {
    char *p;
    for (int i = 0; i < structArray->counter; i++) {
        p = searchStringBetweenTwoChar(structArray->tab[i],string,'\"');
        int offset = 0;
        if (p[0] == '/') {
            offset = 1;
        }
        if (p) {
            //printf("%s\n", p);
            if(isURL(p) == 0){
                createDirectoryFromPath(p + offset,a);
                downloadFileFromPath(p + offset,a);
            }
        }
    }
}

int isURL(char * tab){
    if (strstr(tab, "https://") != NULL){
        return 1;
    }else if(strstr(tab, "http://") != NULL){
        return 1;
    }
    return 0;
}

char* searchStringBetweenTwoChar(char* tab,char* startingString, char endingChar){
    char* p = strstr(tab, startingString);
    int counter = strlen(startingString);
    int counterEnd = counter;
    if(p != NULL) {
        while (p[counterEnd] != endingChar) {
            counterEnd++;
        }
        char *res = searchContentBetween2positions(p, counter, counterEnd-1);
        return res;
    }
    return "";
}

void createDirectoryFromPath(char *path, action* a) {
    int exist;
    char* pathSearch = malloc(sizeof(char)*strlen(path));
    if(strlen(path) > 1){
        for(int i = 0;i<strlen(path);i++){
            if(path[i] == '/'){
                pathSearch[i] = '\0';
                createDirectoryIfNotExist(pathSearch,a);
            }
            pathSearch[i] = path[i];
        }
    }else{
            createDirectoryIfNotExist(pathSearch,a);
        }
}

void downloadFileFromPath(char* path,action* a){
    char url[500];
    sprintf(url,"%s/%s",a->url,path);
    getRessourcesStream(url,createPathFile(path,a));

    printf("dest : %s\nurl : %s\n",createPathFile(path,a),url);
}

char* createPathFile(char* path, action* a){
    char* pathOfFile = malloc(sizeof(char)*(strlen(a->name))+strlen(path)+4);
    strcpy(pathOfFile,"../");
    strcat(pathOfFile,a->name);
    if(strlen(path)>1){
        strcat(pathOfFile,"/");
        strcat(pathOfFile,path);
    }
    return pathOfFile;
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


