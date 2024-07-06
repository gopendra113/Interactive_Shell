#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>

#include<unistd.h>
#include<pwd.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<termios.h>


# include<sys/wait.h>

#define max_len 1000

#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <regex.h>

#include<ctype.h>

#include"warp.h"
#include"peek.h"
#include "prompt.h"
#include "proclore.h"
#include "seek.h"
#include"pastevents.h"
#include"neonate.h"
#include"fg_bg.h"
#include"activities.h"
#include"ping.h"
#include"iman.h"
#include"pipe.h"
#include"redirection.h"
#include"main_function.h"



extern int check_fore;
extern struct timespec start_time, end_time;
extern char* long_cmm;
extern int n;
extern child_pr* prcs_list;
extern pid_t fore_child;
extern char* fore_child_cmm;
extern char prev_directory[max_len];
extern char** history_array;
extern char home[max_len];
extern struct termios orig_termios;

#endif