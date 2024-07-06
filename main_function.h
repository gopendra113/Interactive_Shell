#ifndef __main_H
#define __main_H

#include"headers.h"


void kill_all(child_pr* prcs_list);
void c_handler();
child_pr* add_pid(child_pr* prcs_list,pid_t child_pid,char* command);
child_pr* prev_prcs_state(child_pr* prcs_list);
void run(char* input,int n,int fore,child_pr* prcs_list);
void com_execute(char** com_set,int k,int n);
void z_handler() ;




#endif