#include "headers.h"

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void die(const char *s) {
    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}


int  is_numeric(char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) {
            return 0; 
        }
    }
    return 1;
}



void neonate(char* token, int fore){
    int time=-1;
    token=strtok(NULL," ");
    if (token==NULL || strcmp(token,"-n")!=0){
        printf("invalid command");
        return;
    }
    token=strtok(NULL," ");
    if (token!=NULL){
        if (is_numeric(token)) {
            time = (int)atoi(token);
        }
        else{
            printf("arg should be a number\n");
            return;
        }
    }
    else{
        printf("time arg missing\n");
        return;
    }
    char c;
    if (fore==1){
        pid_t child_pid;
        
        child_pid = fork();
        if (child_pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0) {
            while (1) {
                FILE *file = fopen("/proc/loadavg", "r");

                if (file == NULL) {
                    perror("Error opening /proc/loadavg");
                    return ;
                }

                char line[256];
                if (fgets(line, sizeof(line), file)) {
                    char *token = strtok(line, " ");
                    char *lastToken = NULL;

                    while (token != NULL) {
                        lastToken = token;
                        token = strtok(NULL, " ");
                    }

                    if (lastToken != NULL) {
                        // Convert the last token to an integer (PID)
                        int pid = atoi(lastToken);
                        printf("%d\n", pid);
                    } else {
                        printf("Unable to extract PID from /proc/loadavg\n");
                    }
                } else {
                    printf("Empty /proc/loadavg\n");
                }
                fclose(file);
                sleep(time); 
            }

            exit(EXIT_SUCCESS);
        }

        else{
           
            fore_child=child_pid;
            check_fore=1;
            enableRawMode();
            int pt = 0;
            while (read(STDIN_FILENO, &c, 1) == 1) {
                if (c==120){
                  
                    if (kill(child_pid, SIGTERM) == 0) {
                        
                    } else {
                        perror("Error sending SIGTERM");
                    }
                    break;
                }
            }
            disableRawMode();
            int status;
            check_fore=0;
        }
    }
}