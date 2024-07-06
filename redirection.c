#include"headers.h"

int check_redirection(char* input){
    for (int i=0;i<strlen(input);i++){
        if (input[i]=='>'){
            return 1;
        }
    }
    return 0;
}

void redirect(char * input) {
    int flag=0;
    char cmm[1000];
    char op_file[1000];
    for (int i=0;i<strlen(input);i++){
        if (input[i]=='>'){
            cmm[i]='\0';
            i+=1;
            if (i==strlen(input)){
                printf("specify output file name\n");
                return;
            }
            else if (input[i]=='>'){
                flag=1;
                i+=1;
            }
            int k=0;
            while(i<strlen(input)){
                op_file[k++]=input[i++];
            }
            op_file[k]='\0';
            break;
        }
        else{
            cmm[i]=input[i];
        }
    }

   
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        
        int outputFile;
        if (flag==0){
            outputFile = open(op_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else{
            outputFile = open(op_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        if (outputFile == -1) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }

       
        dup2(outputFile, STDOUT_FILENO);
        close(outputFile);

      
        int execResult = execlp("/bin/sh", "sh", "-c", cmm, NULL);

        if (execResult == -1) {
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }

      
    } else {
        
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Command exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Command did not exit normally\n");
        }
    }
}
