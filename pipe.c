#include"headers.h"


void comm_exe(char *cmd, int in_fd, int out_fd) {
    pid_t pid;
    
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        if (in_fd != 0) {
            dup2(in_fd, 0); 
            close(in_fd);
        }

        if (out_fd != 1) {
            dup2(out_fd, 1); 
            close(out_fd);
        }

        char *args[32];
        int arg_count = 0;

       
        char *token = strtok(cmd, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else { 
        wait(NULL);
    }
}

int check_pipe(char* input){
    for (int i=0;i<strlen(input);i++){
        if (input[i]=='|'){
            return 1;
        }
    }
    return 0;
}
void piping(char* input){
    int flag=1;
    char* result=(char*)malloc(sizeof(char)*1000);
    
    for (int k=0;k<1000;k++){
                result[k]='\0';
            }


    char** comm=(char**)malloc(sizeof(char)*1000);
    int i=0;
    char *cmd1 = strtok(input, "|");
    while(cmd1!=NULL){
        comm[i]=(char*)malloc(sizeof(char)*1000);
        comm[i][0]='\0';
        strcpy(comm[i],cmd1);
        
        cmd1 = strtok(NULL, "|");
        i+=1;
    }

    for (int j=0;j<i;j++) {
    
        int pipe_fd[2];
    
        int second_pipe_fd[2];
    
        if (pipe(pipe_fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        if (pipe(second_pipe_fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        
        
        if (flag==1){
            comm_exe(comm[j], 0, second_pipe_fd[1]);
            close(pipe_fd[1]);
            close(pipe_fd[0]);
            flag=0;
        }
        else{
            
            ssize_t bytes_written = write(pipe_fd[1], result,strlen(result));
        
            if (bytes_written == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            close(pipe_fd[1]);
            comm_exe(comm[j], pipe_fd[0], second_pipe_fd[1]);
            close(pipe_fd[0]);
          
            for (int k=0;k<1000;k++){
                result[k]='\0';
            }
        }
    
        close(second_pipe_fd[1]);
        char buffer[1000];
       
        for (int k=0;k<1000;k++){
                buffer[k]='\0';
            }
        ssize_t bytes_read;
        while ((bytes_read = read(second_pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            strcat(result,buffer);
           
        }
        close(second_pipe_fd[0]);
        free(comm[j]);
    
    }
    free(comm);
    printf("%s",result);
    free(result);

}