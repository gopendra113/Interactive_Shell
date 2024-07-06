

#include"headers.h"
void modify(char** array,int i){
    char* command=(char*)malloc(sizeof(char)*max_len);
    strcpy(command,array[i]);
    int j;
    for (j=i;j<14;j++){
        if (array[j+1][0]=='\0'){
            break;
        }
        strcpy(array[j],array[j+1]);
    }
    strcpy(array[j],command);
    free(command);
}
void add(char** array,char* input){
    if (array[14][0]=='\0'){
        for (int i=0;i<15;i++){
            if (array[i][0]=='\0'){
                strcpy(array[i],input);
                break;
            }
        
        }
    }
    else{
        strcpy(array[0],input);
        char* command=(char*)malloc(sizeof(char)*max_len);
        strcpy(command,array[0]);
        int i;
        for (i=0;i<14;i++){
            if (array[i+1][0]=='\0'){
                break;
            }
            strcpy(array[i],array[i+1]);
        }
        strcpy(array[i],command);
        free(command);
        }
    
}
void check(char ** array,char* input){
    if (strcmp(input,"pastevents")==0){
        return;
    }
    for (int i=0;i<15;i++){
        if (array[i][0]=='\0'){
            break;
        }
        if (strcmp(array[i],input)==0){
            modify(array,i);
            return;
        }
    }
    add(array,input);

}
void display_history(char** array){
    for (int i=0;i<15;i++){
        if (array[i][0]=='\0'){
            break;
        }
        printf("%s\n",array[i]);
    }
}
void write_history(char** array,char* home){
    char *filename=(char*)malloc(sizeof(char)*max_len);
    filename[0]='\0';
    strcat(filename,home);
    strcat(filename,"/");
    strcat(filename,"history.txt");
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        perror("Error opening file");
    }
    for (int i = 0; i < 15; i++) {
        if (array[i][0]=='\0'){
            break;
        }
        fprintf(file, "%s\n", array[i]);
    }

    fclose(file);
}
char** extract_history (char* home) {
    FILE *historyFile;
    char *filename=(char*)malloc(sizeof(char)*max_len);
    filename[0]='\0';
    strcat(filename,home);
    strcat(filename,"/");
    strcat(filename,"history.txt");

    
    historyFile = fopen(filename, "r");
    if (historyFile == NULL) {
        perror("Error opening history file");
        
    }
    char** array=(char**)malloc(sizeof(char*)*15);
    for (int i=0;i<15;i++){
        array[i]=(char*)malloc(sizeof(char)*max_len);
        array[i][0]='\0';
    }
    char buffer[max_len]; 
    int i=0;
    while (fgets(buffer, sizeof(buffer), historyFile) != NULL) {
        buffer[strlen(buffer)-1]='\0';
        strcpy(array[i++],buffer);
    }
    
    fclose(historyFile);
    free(filename);
    return array;
}
  void pastevents(char* token,char** array,char* home){
    char * ar1=(char*)malloc(sizeof(char)*100);
    ar1[0]='\0';
    int ar2=0;
    token=strtok(NULL," ");
    if (token!=NULL){
        strcpy(ar1,token);
        token=strtok(NULL," ");
        if (token!=NULL){
            ar2=atoi(token);
        }
    }
    if (strcmp(ar1,"purge")==0){
        char *filename=(char*)malloc(sizeof(char)*max_len);
        filename[0]='\0';
        strcat(filename,home);
        strcat(filename,"/");
        strcat(filename,"history.txt");
        FILE *file = fopen(filename, "w");

        if (file == NULL) {
            perror("Error opening file");
            
        }
        fclose(file);
        for (int i=0;i<15;i++){
            (array)[i][0]='\0';
        }
    }
    else if(ar1[0]=='\0'){
        display_history(array);
    }
    
  }