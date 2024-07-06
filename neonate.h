#ifndef __neonate_H
#define __neonate_H

#include"headers.h"

void disableRawMode();
void enableRawMode();
void die(const char *s);
void neonate(char* token, int fore);
int  is_numeric(char *str);


#endif