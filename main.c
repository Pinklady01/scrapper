#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "conf_funcs.h"
#include "scrap_funcs.h"
#include <math.h>
#include "parser/parser.h"

int main() {
    printf("pass\n");
    FILE *f=fopen("./Mon deuxieme site.html","rb");
    if(f!=NULL)
    {
        printf("FOPEN\n");
    }
    else printf("FERROR\n");
    int sizeFile = calculateFileSize("./Mon deuxieme site.html");
    printf("sizeFile = %d\n",sizeFile);
    char *contentFile = malloc(sizeFile);
    printf("pass\n");
    fread(contentFile,1,sizeFile,f);
    //printf("%s",contentFile);
    fillFileFromHTML(contentFile);
    fclose(f);
    getRessourcesStream("https://www.ftfi.fr/bois/js/lightbox.js","../parser/webSiteAssets/test.js");

    /*time_t startTime = time(NULL), actualTime;
    settings * s = handleConf("./config.sconf");

    if (s == NULL){
        fprintf(stderr, "conf failed");
        return 1;
    }*/
    // for(int i = 0; i < s->nbActions;i++)
    // {
    //     printf("name : %s\n",s->actions[i]->name);
    //     printf("url : %s\n",s->actions[i]->url);
    //     for(int j = 0; j < s->actions[i]->nbOptions;j++)
    //     {
    //         printf("key : %s\n",s->actions[i]->options[j]->key);
    //         printf("value : %s\n",s->actions[i]->options[j]->value);
    //     }
    //     ;
    
    // }
    // for(int i = 0; i < s->nbTasks; i++)
    // {
    //     printf("task : %s\n",s->tasks[i]->name);
    // }
    

/*
    while(1){
        
        actualTime = time(NULL);
        long long now = (actualTime - startTime);
        //printf("nb task %d\n",s->nbTasks);
        for (int i = 0; i < s->nbTasks; i++){
            
            if (now % s->tasks[i]->time == 0 && now != 0) {
                if (now / s->tasks[i]->time == s->tasks[i]->timesExecuted ){
                    printf("Executing %s - %dx\n\n", s->tasks[i]->name, s->tasks[i]->timesExecuted);
                    for(int j = 0; j < s->tasks[i]->nbSites; j++){
                        for (int k = 0; k < s->nbActions; k++){
                            if (strcmp(s->actions[k]->name, s->tasks[i]->sites[j]) == 0){
                                scrap(s->actions[k]);
                            }
                        }
                    }
                    printf("\n");
                    s->tasks[i]->timesExecuted++;
                }
            }
        }
        
    }
    return 0;
    */
}