#include <stdio.h>
#include <time.h>
#include <string.h>
#include "conf_funcs.h"
#include "scrap_funcs.h"
#include <math.h>

int main() {
    time_t startTime = time(NULL), actualTime;
    settings * s = handleConf("../config.sconf");

    if (s == NULL){
        fprintf(stderr, "conf failed");
        return 1;
    }



    while(1){
        actualTime = time(NULL);
        long long now = (actualTime - startTime);

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
}