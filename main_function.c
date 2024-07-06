#include"headers.h"


void kill_all(child_pr* prcs_list){
    while(prcs_list!=NULL){
        kill(prcs_list->pid,SIGKILL);
        prcs_list=prcs_list->next;
    }
}

void c_handler(){
    printf("\n");
    if ((check_fore==0)){
        prompt(n,0,long_cmm);
        
    }
    else{
        check_fore=0;
    }
    
    fflush(stdout);
    return;
}

child_pr* add_pid(child_pr* prcs_list,pid_t child_pid,char* command){
    if (prcs_list==NULL){
        prcs_list=(child_pr*)malloc(sizeof(child_pr));
        prcs_list->cmd=(char*)malloc(sizeof(char)*strlen(command));
        strcpy(prcs_list->cmd,command);
        prcs_list->pid=child_pid;
        prcs_list->next=NULL;
    }
    else{
        child_pr* pointer=prcs_list;
        while(pointer->next!=NULL){
            pointer=pointer->next;
        }
        pointer->next=(child_pr*)malloc(sizeof(child_pr));
        prcs_list->next->cmd=(char*)malloc(sizeof(char)*strlen(command));
        strcpy(prcs_list->next->cmd,command);
        // pointer->next->cmd=command;
        pointer->next->pid=child_pid;
        pointer->next->next=NULL;
    }
    return prcs_list;
}
child_pr* prev_prcs_state(child_pr* prcs_list){
    child_pr* pointer=prcs_list;
    while (pointer!=NULL){
        int status;
        child_pr* prev;
        char statusPath[256];
        snprintf(statusPath, sizeof(statusPath), "/proc/%d/status", pointer->pid);
        char state=check_state(statusPath);
        if (state=='R' || state=='T' || state=='S'){
            prev=pointer;
            pointer=pointer->next;
        }
        else{
            waitpid(pointer->pid, &status, WNOHANG);
            if (WIFEXITED(status)) {
                printf("%s exited normally (%d)\n",pointer->cmd,pointer->pid);
            } else if (WIFSIGNALED(status)) {
                printf("%s exited abnormally (%d)\n",pointer->cmd,pointer->pid);
            }
            if (pointer==prcs_list){
                prcs_list=pointer->next;
                free(pointer->cmd);
                free(pointer);
                pointer=prcs_list;
            }
            else{
                prev->next=pointer->next;
                free(pointer->cmd);
                free(pointer);
                pointer=prev->next;
            }
        }
        
    }
    return prcs_list;
}

void run(char* input,int n,int fore,child_pr* prcs_list){
    if (check_pipe(input)==1){
        piping(input);
    }
    else if(check_redirection(input)==1){
        redirect(input);
    }
    else{
        char command[max_len];
        strcpy(command,input);
        const char delimiter[] = " ";
        char *token = strtok(input, delimiter);
        
        
        if (strcmp(token,"warp")==0){
            warp(token,prev_directory,home,n);
        }

        else if (strcmp(token,"peek")==0){
            peek(token,home,prev_directory);
        }

        else if(strcmp(token,"proclore")==0){
            token=strtok(NULL, delimiter);
            if (token==NULL){
                proclore(0);
            }
            else{
                int pid=atoi(token);
                proclore(pid);
            }
        }

        else if(strcmp(token,"seek")==0){
            seek(token);
        }
        else if(strcmp(token,"pastevents")==0){
            pastevents(token,history_array,home);
        }
        else if(strcmp(token,"activities")==0){
            activities(token,prcs_list);
            

        }
        else if(strcmp(token,"bg")==0){
            bg(token);
            
            
        }
        else if(strcmp(token,"fg")==0){
            fg(token);
            
        }
        else if(strcmp(token,"neonate")==0){
            neonate(token,fore);
        }
        else if (strcmp(token,"ping")==0){
            ping(token);
        }
        else if(strcmp(token,"iMan")==0){
            token=strtok(NULL," ");
            iman(token);
        }
        else{
            if (fore==1){
                pid_t child_pid;
                child_pid = fork();
                if (child_pid == -1) {
                    perror("Fork failed");
                    exit(EXIT_FAILURE);
                }
                
                if (child_pid == 0) {
                    char *args[32];
                    int arg_count = 0;

                    while (token != NULL) {
                        args[arg_count++] = token;
                        token = strtok(NULL, " ");
                    }
                    args[arg_count] = NULL;
                    
                    if (execvp(args[0], args) == -1) {
                        printf("Error: %s is not a valid command\n", args[0]);
                        exit(EXIT_FAILURE);
                    }
                    exit(EXIT_SUCCESS);
                }
                else{
                    fore_child=child_pid;
                    check_fore=1;
                    int status;
                    waitpid(child_pid, &status, WUNTRACED);
                    check_fore=0;
                }
            }
            else{
                char *args[32];
                int arg_count = 0;
                
                while (token != NULL) {
                    args[arg_count++] = token;
                    token = strtok(NULL, " ");
                }
                args[arg_count] = NULL;
                
                if (execvp(args[0], args) == -1) {
                    printf("Error: %s is not a valid command\n", args[0]);
                    exit(EXIT_FAILURE);
                }
            }
            
        }
    }
    
    
}
void com_execute(char** com_set,int k,int n){
    for (int i=0;i<k-1;i++){
        pid_t child_pid;
        child_pid = fork();
        if (child_pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        
        if (child_pid == 0) {
            run(com_set[i],n,0,prcs_list);
            
            exit(EXIT_SUCCESS);
        }
        else{
            prcs_list=add_pid(prcs_list,child_pid,com_set[i]);
            printf("%d\n",child_pid);
            
        }
    }
    
    if (strlen(com_set[k-1])!=0){
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        fore_child_cmm=com_set[k-1];
        run(com_set[k-1],n,1,prcs_list);
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        if ((end_time.tv_sec - start_time.tv_sec) +
                           1e-9 * (end_time.tv_nsec - start_time.tv_nsec) >2){
            long_cmm=(char*)malloc(sizeof(char)*(strlen(com_set[k-1])));
            strcpy(long_cmm,com_set[k-1]);
            long_cmm=strtok(long_cmm," ");
        }
       
    }
    
    

}
void z_handler() {
    if (check_fore==1){
        tcsetpgrp(STDIN_FILENO,getpgrp());
        kill(fore_child, SIGTSTP);
        prcs_list=add_pid(prcs_list,fore_child,fore_child_cmm);
        check_fore=0;
    }
}
