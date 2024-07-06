#include "headers.h"

int check_fore=0;
struct timespec start_time, end_time;
char* long_cmm;
int n;
child_pr* prcs_list;
pid_t fore_child;
char* fore_child_cmm;

char prev_directory[max_len];
char** history_array;
char home[max_len];

struct termios orig_termios;


int main()
{
    check_fore=0;
    n=first_prompt();
    getcwd(home,max_len);
    prcs_list=NULL;
    strcpy(prev_directory,home);
    history_array=extract_history(home);
    signal(SIGTSTP, z_handler);
    long_cmm=NULL;
   
    start_time.tv_sec=0;
    end_time.tv_sec=0;
    end_time.tv_nsec=0;
    start_time.tv_nsec=0;
    signal(SIGINT,c_handler);
    while (1)
    {
        
        double execution_time = (end_time.tv_sec - start_time.tv_sec) +
                           1e-9 * (end_time.tv_nsec - start_time.tv_nsec);
        int rounded_execution_time = (int)round(execution_time);
        if (execution_time>2){
            
            prompt(n,rounded_execution_time,long_cmm);
        }
        else{
            
            prompt(n,0,long_cmm);
        }
        char input[4096];
        if(fgets(input, 4096, stdin)==0)
        {
            kill_all(prcs_list);
            printf("\n") ;
            exit(EXIT_SUCCESS);
        }
        if(input[strlen(input)-1]=='\n'){
            input[strlen(input)-1]='\0';    
        }
        check(history_array,input);

        prcs_list=prev_prcs_state(prcs_list);

        int k=0;
        int p=0;
        char** comm_set=(char**)malloc(sizeof(char)*max_len);
        comm_set[0]=(char*)malloc(sizeof(char)*max_len);
        for (int i=0;i<strlen(input);i++){
            if(input[i]==';'){
                comm_set[k][p]='\0';
                k+=1;
                
                com_execute(comm_set,k,n);
                comm_set=(char**)malloc(sizeof(char*)*max_len);
                comm_set[0]=(char*)malloc(sizeof(char)*max_len);
                k=0;
                p=0;
            }
            else if (input[i]=='&'){
                comm_set[k][p]='\0';
                k+=1;
                comm_set[k]=(char*)malloc(sizeof(char)*max_len);
                comm_set[k][0]='\0';

                if (i==strlen(input)-1){
                    
                    com_execute(comm_set,k+1,n);
                }
                p=0;
            }
            else if(i==strlen(input)-1){
                comm_set[k][p]=input[i];
                comm_set[k][p+1]='\0';
                k+=1;
                
                com_execute(comm_set,k,n);
            }
            else{
                comm_set[k][p]=input[i];
                p+=1;
            }

        }
        write_history(history_array,home);
    }
}
