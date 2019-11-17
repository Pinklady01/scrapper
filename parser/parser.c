#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct_src.h"
#include "parser.h"
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


    //fonction qui va parcourir les structures
    //pour src= dans link et script ==> créer les directory.
    //Pour créer les directory: lire le src avant les "/" si n'existe pas dans les fichiers, le créer.
    //rajouter struct settings (action?) dans les fcts pour s->task[i]
    //envoi struct css avec href="
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
            printf("%s\n", p);
            createDirectoryFromPath(p + offset,a);
        }
    }
}

int isURL(){
    //TODO: fonction
    // commence par https::// ou http:// renvoie 1 sinon 0
    // si 1, ne pas telecharger en fichier à voire si scrapper
}

char* searchStringBetweenTwoChar(char* tab,char* startingString, char endingChar){
    char* p = strstr(tab, startingString);
    int counter = strlen(startingString);
    int counterEnd = counter;
    if(p != NULL) {
        while (p[counterEnd] != endingChar) {
            counterEnd++;
        }
        char *res = searchContentBetween2positions(p, counter, counterEnd);
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

void downloadFileFromPath(char* path){
    //retrieve URL

}

//TODO: A VERIFIER CreatePathFile
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

int verifPath(char* path, action* a){
    DIR* rep = NULL;
    char* pathOfFile = createPathFile(path,a);
    rep = opendir(pathOfFile); /* Ouverture d'un dossier */
    if (rep == NULL) /* Si le dossier n'a pas pu être ouvert */
        return 1; /* (mauvais chemin par exemple) */
    if (closedir(rep) == -1) /* S'il y a eu un souci avec la fermeture */
        return -1;
    return 0;
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


