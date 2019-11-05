//
// Created by Marion Mota on 05/11/2019.
//
#ifndef UNTITLED_STRUCT_H
#define UNTITLED_STRUCT_H

#include "struct.c"

struct Tag;
struct TagChildren;

typedef struct TagChildren{
    struct Tag **arrayTag;
    int capacity;
    int size;
} TagChildren;

typedef struct Tag{
    char *tagHTML;
    char *tagString;
    TagChildren *tagChildren;
} Tag;

Tag *createTag(char*);
TagChildren *createTagChildren();
void addContentTag(Tag *,char *);
void addTagChildren(TagChildren *,Tag *);

#endif //UNTITLED_STRUCT_H

