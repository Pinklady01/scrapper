
#ifndef STRUCT_SRC_H
#define STRUCT_SRC_H

struct StringArray;

typedef struct StringArray{
    char **tab;
    int counter;
    int capacity;
} StringArray;

StringArray *createStringArray();
void addContentString(StringArray *,char *);

#endif //STRUCT_SRC_H


