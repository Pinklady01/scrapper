#ifndef SCRAPPER_CONF_FUNCS_H
#define SCRAPPER_CONF_FUNCS_H

typedef struct assoc{
    char * key;
    char * value;
} assoc;

typedef struct action{
    char * name;
    char * url;
    int nbOptions;
    assoc ** options;
} action;

typedef struct task{
    char * name;
    long time;
    int nbSites;
    char ** sites;
    int timesExecuted;
} task;

typedef struct settings {
    int nbActions;
    int nbTasks;
    action ** actions;
    task ** tasks;
} settings;

settings * handleConf(char * filename);

#endif //SCRAPPER_CONF_FUNCS_H
