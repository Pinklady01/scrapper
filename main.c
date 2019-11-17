#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "conf_funcs.h"
#include "scrap_funcs.h"
#include <math.h>
#include <sys/stat.h>
#include "parser/parser.h"

int main() {
    //getRessourcesStream("https://www.ftfi.fr/bois/js/lightbox.js","../parser/webSiteAssets/test.js");

        time_t startTime = time(NULL), actualTime;
        settings *s = handleConf("../config.sconf");

        if (s == NULL) {
            fprintf(stderr, "conf failed");
            return 1;
        }
        while (1) {

            actualTime = time(NULL);
            long long now = (actualTime - startTime);
            for (int i = 0; i < s->nbTasks; i++) {

                if (now % s->tasks[i]->time == 0 && now != 0) {
                    if (now / s->tasks[i]->time == s->tasks[i]->timesExecuted) {
                        printf("Executing %s - %dx\n\n", s->tasks[i]->name, s->tasks[i]->timesExecuted);
                        for (int j = 0; j < s->tasks[i]->nbSites; j++) {
                            for (int k = 0; k < s->nbActions; k++) {
                                printf("action: %s sites: %s\n",s->actions[k]->name,s->tasks[i]->sites[j]);
                                if (strcmp(s->actions[k]->name, s->tasks[i]->sites[j]) == 0) {
                                    scrap(s->actions[k], s->tasks[i]);
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
