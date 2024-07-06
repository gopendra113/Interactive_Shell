
#include"headers.h"

void readstatus(const char *statusFilePath, const char *infoName,pid_t pid) {
    FILE *file = fopen(statusFilePath, "r");
    if (file) {
        char buffer[1024];
        const char delimiter[] = " ";
        while (fgets(buffer, sizeof(buffer), file)) {
            char *value = NULL;
            char *token = strtok(buffer, ":"); 
            while (token != NULL) {

                if (strcmp(token, infoName) == 0) {
                    token = strtok(NULL, ":"); 
                    if (token != NULL) {
                        while (*token && isspace(*token)) {
                            token++;
                        }
                        int len = strlen(token);
                        while (len > 0 && isspace(token[len - 1])) {
                            len--;
                        }
                        value = (char *)malloc(len + 1);
                        strncpy(value, token, len);
                        value[len] = '\0';
                    }
                    if (infoName[0]=='P'){
                        printf("pid: ");
                        int i=0;
                        while(value[i]!=' ' && value[i]!='\0'){
                            printf("%c",value[i]);
                            i++;
                        }
                        printf("\n");

                    }
                    else if (infoName[0]=='S'){
                        printf("process status: ");
                        int i=0;
                        while(value[i]!=' ' && value[i]!='\0' ){
                            printf("%c",value[i]);
                            i++;
                        }
                    
                        pid_t pgid = getpgid(pid);
                        pid_t fg_pgid = tcgetpgrp(STDIN_FILENO);

                        if (pgid == fg_pgid) {
                            printf("+");
                        } 
                        printf("\n");
                    }
                    else if (infoName[0]=='V'){
                        printf("Virtual memory: ");
                        int i=0;
                        while(value[i]!=' ' && value[i]!='\0'){
                            printf("%c",value[i]);
                            i++;
                        }
                        printf("\n");
                    }
                    break;
                    
                }
                token = strtok(NULL, ":");
                
            }
        }
        fclose(file);
    } else {
        perror("Error opening /proc file");
    }
}




void proclore(pid_t pid) {
    if (pid==0){
        pid =getpid();
    }
    printf("%d\n",pid);
    char statusPath[256];
    snprintf(statusPath, sizeof(statusPath), "/proc/%d/status", pid);
    
    readstatus(statusPath, "Pid",pid);
    readstatus(statusPath, "State",pid);
    readstatus(statusPath, "VmSize",pid);

    pid_t pgid = getpgid(pid);
    if (pgid!=-1){
        printf("Process Group: %d\n", pgid);
    }
    else{
        perror("Error getting pgid");
    }
    char exePath[256];
    snprintf(exePath, sizeof(exePath), "/proc/%d/exe", pid);
    ssize_t exePathLength = readlink(exePath, exePath, sizeof(exePath) - 1);

    if (exePathLength != -1) {
        exePath[exePathLength] = '\0';
        printf("executable Path: %s\n", exePath);
    } else {
        perror("Error retrieving executable path");
    }
}
