#ifndef __Peek_H
#define __Peek_H

#include"headers.h"

typedef struct FileInfo {
    char name[300]; 
    mode_t mode;    
    uid_t uid;      
    gid_t gid;      
    off_t size;   
    time_t mtime;   
    nlink_t nlink;
}container;

int is_greater(container* first,container* second);
void merge(container** data,int l,int r);
void sort(container** data,int l,int r);
void msort(container** data,int n);
void displaymode(mode_t mode);
void read_dir(DIR *dir,struct dirent *entry,int *count,int n,const char* path);
void peek(char *path,char * home,char* prev_directory);

#endif