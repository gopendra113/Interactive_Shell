#ifndef __proclore_H
#define __proclore_H

#include"headers.h"

void readstatus(const char *statusFilePath, const char *infoName,pid_t pid);
void proclore(pid_t pid);

#endif