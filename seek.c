#include"headers.h"



int flag_d,flag_f,flag_e;

void read_seek(DIR *dir,struct dirent *entry,char* path,char* name,node* final){
    if (((entry = readdir(dir)) != NULL) ){
        if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
            int i=0;
            struct stat info;
            if (strlen(name)<=strlen(entry->d_name)){
                for (i=0;i<strlen(name);i++){
                    if (entry->d_name[i]!=name[i]){
                        break;
                    }
                }
            }
            char* new_path=(char*)malloc(sizeof(char)*(strlen(path)+strlen(entry->d_name)+1));
            new_path[0]='\0';
            strcat(new_path,path);
            strcat(new_path,"/");
            strcat(new_path,entry->d_name);

            if (stat(new_path, &info) != 0) {
                perror("Error in stat");
            }

            if (i==strlen(name)&& (entry->d_name[i]=='\0'|| entry->d_name[i]=='.')){
                if (S_ISDIR(info.st_mode)){
                    if (flag_d==1 || (flag_d==0&&flag_f==0)){
                        final->str=(char*)malloc(sizeof(char)*((strlen(path)+strlen(entry->d_name)+1)));
                        strcpy(final->str,new_path);
                        final->next=(node*)malloc(sizeof(node));
                        final=final->next;
                        final->str=NULL;
                    }
                }
                else if(flag_f==1 || (flag_d==0&&flag_f==0)){
                    final->str=(char*)malloc(sizeof(char)*((strlen(path)+strlen(entry->d_name)+1)));
                    strcpy(final->str,new_path);
                    final->next=(node*)malloc(sizeof(node));
                    final=final->next;
                    final->str=NULL;
                }
            }
            read_seek(dir,entry,path,name,final);

            if (S_ISDIR(info.st_mode)){
                dir = opendir(new_path);
                if (dir == NULL) {
                    perror("opendir");
                    exit(EXIT_FAILURE);
                }
                read_seek(dir,entry,new_path,name,final);
                closedir(dir);
                
            }
            free(new_path);
        }
        else{
            read_seek(dir,entry,path,name,final);
        }
        
           
        
    }
    
}

void fun(char * path,char* name,node* final){
    DIR *dir;
    struct dirent *entry;
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    read_seek(dir,entry,path,name,final);
    closedir(dir);
}

void display(char* str,int len){
    printf(".");
    for (int i=len;i<strlen(str);i++){
        printf("%c",str[i]);
    }
    printf("\n");
}
void seek(char* token){
    char input[]="seek -f -e yyy";
    flag_d=0;flag_e=0;flag_f=0;
    node *final=(node*)malloc(sizeof(node));
    final->str=NULL;
    const char delimiter[] = " ";
    char* buffer1=(char*)malloc(sizeof(char)*max_len);
    char* buffer2=(char*)malloc(sizeof(char)*max_len);
    buffer2[0]='\0';
    token=strtok(NULL, delimiter);
        while (token!=NULL){
            if (strcmp(token,"-d")==0){
                flag_d=1;
            }
            else if(strcmp(token,"-f")==0){
                flag_f=1;
            }
            else if(strcmp(token,"-e")==0 || strcmp(token,"-la")==0){
                flag_e=1;
            }
            else{
                strcpy(buffer1,token);
                token=strtok(NULL, delimiter);
                if (token!=NULL){
                    strcpy(buffer2,token);
                }
                break;
            }
            token=strtok(NULL, delimiter);
        }
    
    if (!(flag_d==1 && flag_f==1) || !(flag_d==0 && flag_f==0 && flag_e==1)){
        if (buffer2[0]=='\0'){
            getcwd(buffer2,max_len);
            printf("%s\n",buffer1);
            printf("%s\n",buffer2);
            fun(buffer2,buffer1,final);
        }
        else{
            char* ab_path=(char*)malloc(sizeof(char)*max_len);
            if (buffer2[0]=='.'){
                if (realpath(buffer2, ab_path) == NULL) {
                    perror("realpath");
                    exit(EXIT_FAILURE);
                }
                strcpy(buffer2,ab_path);
            }
            
            free(ab_path);
            fun(buffer2,buffer1,final);
            
        }
        int len=strlen(buffer2);
        if(flag_e==0){
            if (final->str==NULL){
                printf("No match found!\n");
            }
            else{
                while(final!=NULL){
                if (final->str!=NULL){
                    display(final->str,len);
                }
                else{
                    break;
                }
                final=final->next;
                }
            }
            
        }
        else if (flag_e==1){
            if (final->str==NULL){
                printf("No match found!\n");
            }
            else if (final->next->str==NULL){
                display(final->str,len);
                if (flag_d==1){
                    if (chdir(final->str)!=0){
                    perror("chdir");
                    }
                }
                else{
                    FILE *file = fopen(final->str, "r");
                    if (file == NULL) {
                        perror("Error opening file");
                    }
                    char buffer[max_len];
                    size_t bytesRead;
                    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                        fwrite(buffer, 1, bytesRead, stdout);
                    }
                    printf("\n");
                    fclose(file);
                }
            }
            else{
                while(final!=NULL){
                    if (final->str!=NULL){
                        display(final->str,len);
                    }
                    else{
                        break;
                    }
                    final=final->next;
                }
            }
        }
    }
    else{
        printf("Invalid flags!\n");
    }
    
    
    free(buffer1);
    free(buffer2);
}