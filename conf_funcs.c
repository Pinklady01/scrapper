#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf_funcs.h"

settings * handleConf(char *filename){
    char buf[1000];
    int nbTasks = 0, nbActions = 0;
    task ** tasks;
    action ** actions;
    settings * s;

    FILE *f = fopen(filename, "r");

    if (!f)
        return NULL;

    while (fgets(buf, 100, f) != NULL){
        
        if (buf[0] == '='){
            if (buf[1] == '='){
                nbTasks++;
            } else {
                nbActions++;
            }
        }
    }

    fseek(f, 0, SEEK_SET);

    tasks = malloc(sizeof(task*) * nbTasks);
    actions = malloc(sizeof(action*) * nbActions);

    nbTasks = 0;
    nbActions = 0;
    while (fgets(buf, 100, f) != NULL){
        if (buf[0] == '='){
            if (buf[1] == '='){
                tasks[nbTasks] = handleTask(f);
                nbTasks++;
            } else {
                
                actions[nbActions] = handleAction(f);
                nbActions++;
            }
        }
    }

    s = malloc(sizeof(settings));
    s->nbActions = nbActions;
    s->nbTasks = nbTasks;
    s->actions = malloc(sizeof(action **));
    s->tasks = malloc(sizeof(task **));

    s->actions = actions;
    s->tasks = tasks;

    return s;
}

action * handleAction(FILE *f){
    action *a = malloc(sizeof(action));
    int nbAssocs = 0, i;
    char buf[100];

    //printf("%s\n",buf);
    setActionName(f, a);
    fgets(buf, 100, f);
    setActionURL(f, a);
    fgets(buf, 100, f);
    fgets(buf, 100, f);

    nbAssocs = getNbAssoc(f);

    a->options = malloc(sizeof(assoc*) * nbAssocs);
    a->nbOptions = nbAssocs;

    for (i = 0; i < nbAssocs; i++){
        setActionOption(f, a, i);
    }

    return a;
}

task * handleTask(FILE *f){
    task *t = malloc(sizeof(task));
    int nbSites = 0, c;
    char buf[100];

    setTaskName(f, t);
    fgets(buf, 100, f);

    setTime(f, t);

    while((c = getc(f)) != '(');

    nbSites = getNbSites(f);

    t->sites = malloc(sizeof(char*) * nbSites);
    setSites(f, t, nbSites);

    t->nbSites = nbSites;

    t->timesExecuted = 1;

    return t;
}

void setActionName(FILE *f, action *a){
    int current_pos, c, count = 0;
    char name[100];

    current_pos = ftell(f);
    fseek(f, 9, SEEK_CUR);
    while((c = getc(f)) != '}'){
        name[count] = (char)c;
        count++;
    }
    name[count] = '\0';
    //printf("name : %s\n",name);
    fseek(f, current_pos, SEEK_SET);
    a->name = malloc(sizeof(char) * (count + 1));
    strcpy(a->name, name);
}

void setActionURL(FILE *f, action *a){
    int current_pos, c, count = 0;
    char url[100];

    current_pos = ftell(f);
    fseek(f, 8, SEEK_CUR);

    while((c = getc(f)) != '}'){
        url[count] = (char)c;
        count++;
    }
    url[count] = '\0';
    //printf("url : %s\n",url);
    fseek(f, current_pos, SEEK_SET);
    a->url = malloc(sizeof(char) * (count + 1));
    strcpy(a->url, url);
}

void setTaskName(FILE *f, task *t){
    int current_pos, c, count = 0;
    char name[100];

    current_pos = ftell(f);
    fseek(f, 9, SEEK_CUR);
    while((c = getc(f)) != '}'){
        name[count] = (char)c;
        count++;
    }
    name[count] = '\0';
    fseek(f, current_pos, SEEK_SET);
    t->name = malloc(sizeof(char) * (count + 1));
    strcpy(t->name, name);
}

int getNbAssoc(FILE *f){
    char buf[100];
    int count = 0, actual;
    actual = ftell(f);
    int end = 0;
    while(fgets(buf, 100, f) != NULL){
        
        if (buf[0] != '{'){
            end = 1;
        } else if (buf[0] == '{'){
            count++;
        }
        if(end == 1) break;
    }
    fseek(f, actual, SEEK_SET);
    return count;
}

void setActionOption(FILE *f, action *a, int pos){
    char buf[100], key[100], value[100];
    int c, actual, count = 0;

    assoc * o = malloc(sizeof(assoc));

    actual = ftell(f);
    fseek(f, 1, SEEK_CUR);
    while((c = getc(f)) != ' '){
        key[count] = (char) c;
        count++;
    }
    key[count] = '\0';

    o->key = malloc(sizeof(char) * (count + 1));

    strcpy(o->key, key);


    fseek(f, 3, SEEK_CUR);
    count = 0;
    while((c = getc(f)) != '}'){
        value[count] = (char) c;
        count++;
    }
    value[count] = '\0';

    o->value = malloc(sizeof(char) * (count + 1));
    strcpy(o->value, value);

    a->options[pos] = o;

    fseek(f, actual, SEEK_SET);
    fgets(buf, 100, f);
}

void setTime(FILE *f, task *t){
    int lines, pos, c, start;
    char buf[100], number[20];

    lines = getNbAssoc(f);

    t->time = 0;

    for (int i = 0; i < lines; i++){
        int j = 0, res = 0;
        pos = ftell(f);
        fseek(f, 1, SEEK_CUR);

        start = getc(f);
        while((c = getc(f)) != '>');
        fseek(f, 1, SEEK_CUR);
        while((c = getc(f)) != '}'){
            number[j] = (char) c;
            j++;
        }
        number[j] = '\0';
        res = atoi(number);

        switch(start){
            case 's':
                t->time += res;
                break;
            case 'm':
                t->time += (res * 60);
                break;
            case 'h':
                t->time += (res * 3600);
                break;
            default:
                break;
        }

        fseek(f, pos, SEEK_SET);
        fgets(buf, 100, f);
    }
}

int getNbSites(FILE *f){
    int count = 1, position, c;
    position = ftell(f);
    while((c = getc(f)) != ')'){
        if (c == ',')
            count++;
    }
    fseek(f, position, SEEK_SET);
    return count;
}

void setSites(FILE *f, task *t, int nbSites){
    int pos, c, count;
    char *buf;

    for (int i = 0; i < nbSites; i++){
        pos = ftell(f);
        count = 0;
        c = getc(f);
        while(c  != ',' && c != ')'){
            count++;
            c = getc(f);
        }
        buf = malloc(sizeof(char) * (count + 2));
        fseek(f, pos, SEEK_SET);
        for (int j = 0; j < count; j++){
            buf[j] = (char) getc(f);
        }
        buf[count] = '\0';
        t->sites[i] = malloc(sizeof(char) * (count + 1));
        strcpy(t->sites[i], buf);
        fseek(f, 2, SEEK_CUR);
    }
}