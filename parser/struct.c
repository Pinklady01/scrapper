//
// Created by Marion Mota on 05/11/2019.
//

#include <string.h>
//#include "struct.h"

struct Tag;
struct TagChildren;

typedef struct TagChildren{
    Tag **arrayTag;
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

Tag *createTag(char* tagName){
    Tag *newTag = malloc(sizeof(struct Tag*));
    newTag->tagHTML = malloc(sizeof(char)*strlen(tagName));
    strcpy(newTag->tagHTML,tagName);
    newTag->tagChildren = createTagChildren();
    return newTag;
}

void addContentTag(Tag *tag,char *content){
    tag->tagString = malloc(sizeof(char)*strlen(content));
    strcpy(tag->tagString,content);
}

TagChildren *createTagChildren(){
    TagChildren *newTagChildren = malloc(sizeof(struct TagChildren*));
    newTagChildren->arrayTag = malloc(sizeof(Tag*)*10);
    newTagChildren->capacity = 10;
    newTagChildren->size = 0;
    return newTagChildren;
}

void addTagChildren(TagChildren *tagChildren,Tag *tag){
    if(tagChildren->size == tagChildren->capacity){
        tagChildren->capacity*=2;
        Tag **arrayTag = malloc(sizeof(Tag*)*tagChildren->capacity);
        for (int i = 0;i<tagChildren->size;i++){
            arrayTag[i] = tagChildren->arrayTag[i];
        }
        free(tagChildren->arrayTag);
        tagChildren->arrayTag = arrayTag;
    }
    tagChildren->arrayTag[tagChildren->size] = tag;
}



