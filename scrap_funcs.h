#ifndef SCRAPPER_SCRAP_FUNCS_H
#define SCRAPPER_SCRAP_FUNCS_H

void scrap(action*,task*);
int getRessourcesStream(char *,char *);
int isVersioningOn(char*);
void saveAction(int, char* , char* );

#endif //SCRAPPER_SCRAP_FUNCS_H
