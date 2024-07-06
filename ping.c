#include"headers.h"

void ping(char* token){
    token=strtok(NULL," ");
    pid_t pid ;
    int signal_number;
    if (token!=NULL){
        if (is_numeric(token)) {
            pid = (pid_t)atoi(token);
        }
        else{
            printf("pid should be a number\n");
            return;
        }
        
    }
    else{
        printf("INVALID COMMAND\n");
        return;
    }
    token=strtok(NULL," ");
   
    if (token!=NULL){
        
        if (is_numeric(token)) {
            signal_number = ((int)atoi(token)) % 32;
        }
        else{
            printf("signal should be a number\n");
            return;
        }
    }
    else{
        printf("INVALID COMMAND\n");
        return;
    }
    token=strtok(NULL," ");
    if(token!=NULL){
        printf("INVALID COMMAND\n");
        return;
    }
    else{
        if (kill(pid, signal_number) == 0) {
                printf("Sent signal %d to process with pid %d\n", signal_number, pid);
        } else {
            perror("kill");
            return ;
        }
    }
}