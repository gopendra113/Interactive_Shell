#ifndef __pipe_H
#define __pipe_H

#include"headers.h"

void comm_exe(char *cmd, int in_fd, int out_fd);
void piping(char* input);
int check_pipe(char* input);

#endif