#include <string.h>
//#include "struct.c"
//#include "parser.h"
int calculateFileSize(char *);
void fillStructFromHHTML(char *);
int searchTagName(int,char *);

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

void fillStructFromHHTML(char *tab){
    //char *newTab=malloc(sizeof(tab));
    char *tagName=malloc((sizeof(char)*8));
    int traitement=0;
    int endingChar;
    for(int i = 0;i < strlen(tab);i++){
        if(tab[i] == '<' && traitement == 0){
            endingChar = searchTagName(i+1,tab)-1;
            traitement = 1;
            //printf("%c",tab[endingChar]);
            break;
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
int searchTagName(int startingChar,char *tab){
    int counter=startingChar;
    while(tab[counter]!=' '&& tab[counter]!='>'){
        counter++;
    }
    return counter;
}


