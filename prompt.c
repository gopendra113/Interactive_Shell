#include "headers.h"

void prompt(int n,int time,char* cmm) {
    int flag=0;
    printf("\x1b[33m");
    char sysname[max_len];
    gethostname(sysname, max_len);
    uid_t user_id = getuid();
    struct passwd *user_info = getpwuid(user_id);
    printf("%s@%s :", user_info->pw_name,sysname);
    char path[max_len];
    getcwd(path, max_len);
    if (strlen(path)>=n){
        printf("~");
        for (int i=n;i<strlen(path);i++){
            printf("%c",path[i]);
        }
        if (time!=0){
            printf("%s :%ds",cmm,time);
            free(cmm);
        }
        printf(">");
    }
    else{ 
        for (int i=0;i<strlen(path);i++){
            printf("%c",path[i]);
        }
        if (time!=0){
            printf("%s :%ds",cmm,time);
            free(cmm);
        }
        printf(">");
    }
    printf("\x1b[0m");
}
int first_prompt(){
    char path[max_len];
    getcwd(path, max_len);
    return strlen(path);
}
