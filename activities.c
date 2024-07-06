#include "headers.h"



char check_state(const char *statusFilePath) {
    FILE *file = fopen(statusFilePath, "r");
    if (file) {
        char buffer[1024];
        const char delimiter[] = " ";
        while (fgets(buffer, sizeof(buffer), file)) {
            char *value = NULL;
            char *token = strtok(buffer, ":"); 
            while (token != NULL) {

                if (strcmp(token, "State") == 0) {
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
                    int i=0;
                    while(value[i]!=' ' && value[i]!='\0' ){
                        i++;
                    }
                    return value[i-1];
                    
                    }
                    break;
                    
                }
                token = strtok(NULL, ":");
        }
        fclose(file);
    } else {
        perror("Error opening /proc file");
    }
}



void activities(char* token,child_pr* prcs_list){
    token=strtok(NULL," ");
    if (token!=NULL){
        printf("INVALID COMMAND\n");
    }
    else{
        child_pr* pointer=prcs_list;
        while(pointer!=NULL){
            pid_t pid=pointer->pid;
            char statusPath[256];
            snprintf(statusPath, sizeof(statusPath), "/proc/%d/status", pointer->pid);
            char state=check_state(statusPath);
            if (state=='R' || state =='S'){
                printf("%d : %s - Running\n", pid,pointer->cmd);
            }
            else if(state=='T'){
                printf("%d : %s - Stopped\n", pid,pointer->cmd);
            }

            pointer=pointer->next;
        }
        
    }
}
