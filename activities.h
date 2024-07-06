#ifndef __activities_H
#define __activities_H

#include"headers.h"

typedef struct child_proc{
    char * cmd;
    pid_t pid;
    struct child_proc * next;
}child_pr;

void activities(char* token,child_pr* prcs_list);
char check_state(const char *statusFilePath) ;

#endif