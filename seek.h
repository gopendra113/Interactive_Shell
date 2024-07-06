#ifndef __seek_H
#define __seek_H

#include"headers.h"

typedef struct node{
    char * str;
    struct node* next;
}node;

void fun(char * path,char* name,node* final);
void read_seek(DIR *dir,struct dirent *entry,char* path,char* name,node* final);
void display(char* str,int len);
void seek(char* token);



#endif