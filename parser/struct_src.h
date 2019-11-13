#ifndef SCRAPPER_STRUCT_H
#define SCRAPPER_STRUCT_H

typedef struct StringArray StringArray;
StringArray *createStringArray();
void addContentString(StringArray *,char *);

#endif //SCRAPPER_STRUCT_H