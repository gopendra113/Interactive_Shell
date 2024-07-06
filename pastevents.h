#ifndef __Pastevents_H
#define __Pastevents_H

#include"headers.h"

void modify(char** array,int i);
void add(char** array,char* input);
void check(char ** array,char* input);
void display_history(char** array);
void write_history(char** array,char* home);
char** extract_history (char* home) ;
void pastevents(char* token,char** array,char* home);



#endif