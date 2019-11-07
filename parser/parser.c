#include <string.h>
//#include "struct.c"
//#include "parser.h"
int calculateFileSize(char *);
void fillStructFromHTML(char *);
int searchEndingChar(int,char *,char);
char *searchContentBetween2positions(char *,int,int);
char *substr(char *src,int pos,int len);

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
    char *tagName=malloc((sizeof(char)*8));
    int endingChar;
    for(int i = 0;i < strlen(tab);i++){
        if(tab[i] == '<'){
            endingChar = searchEndingChar(i,tab,'>');
            //printf("%c",tab[endingChar]);
            //searchContentBetween2positions(tab,i,endingChar)
            printf("%s",searchContentBetween2positions(tab,i,endingChar));
        }
    }
    /*for(int i = 0;i<size;i++){
        if(tab[i]=="<"&&traitement==0){
            //verifier si cela ne va pas modifier à chaque fois les valeurs précédentes ou si nouvelle valeur
            searchTagName(i+1,&tab,&tagName);
            struct tag = new tag();
            tag->tagHTML=&tagName;
            traitement=1;
        }else if(tab[i]=="<"){
            char verifyTag=malloc(sizeof(char)*8);
            searchTagName()i+1;&tab;&verifyTag);
            //verifier comment dire "contient"
            //mettre les autres cas de balise fermante seule
            if(verifyTag=="img"){
                //l'ajoute dans la structure mais ne le met pas dans le string de la structure en cours
            }
        } else if(tab[i]=="<"&&tab[i+1]=="/"){
            //verifie si le tag après correspond à celui de la structure.
            //ajoute dans la structure le string entier avec en size "i"
        }
    }*/
}
int searchEndingChar(int startingChar,char *tab,char symbol){
    int counter=startingChar;
    while(tab[counter]!=' '&& tab[counter]!=symbol){
        counter++;
    }
    return counter;
}

char *searchContentBetween2positions(char *tab,int startingChar,int endingChar){
    char *dest = malloc(sizeof(char)*(endingChar-startingChar+1));
    int counter = 0;
    for(int i = startingChar;i<=endingChar;i++){
        dest[counter] = tab[i];
        printf("%c",tab[i]);
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


