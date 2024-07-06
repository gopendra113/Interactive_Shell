#include"headers.h"

void fg(char* token){
    token=strtok(NULL," ");
    pid_t pid ;
    if (token==NULL){
        printf("pid of process required\n");
        return;
    }
    else{
        if (is_numeric(token)) {
            pid = (pid_t)atoi(token);
        }
        else{
            printf("pid should be a number\n");
            return;
        }
    }
    token=strtok(NULL," ");
    if(token!=NULL){
        printf("INVALID COMMAND\n");
    }
    else{
        if (kill(pid, SIGCONT) == 0) {
            int status;
        if (waitpid(pid, &status, WUNTRACED) == -1) {
            perror("waitpid");
        }
            
        } else {
            perror("Error sending SIGCONT signal");
        }
    }
}


void bg(char* token){
    token=strtok(NULL," ");
    pid_t pid ;
    if (token==NULL){
        printf("pid of process required\n");
        return;
    }
    else{
        if (is_numeric(token)) {
            pid = (pid_t)atoi(token);
        }
        else{
            printf("pid should be a number\n");
            return;
        }
    }
    token=strtok(NULL," ");
    if(token!=NULL){
        printf("INVALID COMMAND\n");
    }
    else{
        if (kill(pid, SIGCONT) == 0) {
            printf("Sent SIGCONT signal to process with PID %d\n", pid);
        } else {
            perror("Error sending SIGCONT signal");
        }
    }
}