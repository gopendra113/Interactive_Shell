#include "headers.h"

void warp(char* token,char* prev_directory,char* home,int n){
    token=strtok(NULL, " ");
    char* path=(char*)malloc(sizeof(char)*max_len);
    char* currpath=(char*)malloc(sizeof(char)*max_len);
        
    if (token==NULL){
        getcwd(currpath,max_len);
            if (chdir(home)!=0){
                perror("chdir");
            }
            else{
                strcpy(prev_directory,currpath);
            }
            getcwd(path,max_len);
            printf("%s\n",path);
    }
    while (token!=NULL){
        if (token=="."){
            getcwd(currpath,max_len);
            printf("%s\n",currpath);
        }
        else if (token==".."){
            getcwd(currpath,max_len);
            getcwd(path,max_len);
            int i=1;
            while(path[strlen(path)-i]!='/'){
                i++;
            }
            path[strlen(path)-i]='\0';
            if (chdir(path)!=0){
                perror("chdir");
            }
            else{
                strcpy(prev_directory,currpath);
            }
            getcwd(path,max_len);
            printf("%s\n",path);
        }
        else if(strcmp(token,"-")==0){
            
            getcwd(currpath,max_len);
            if (chdir(prev_directory)!=0){
                perror("chdir");
            }
            else{
                strcpy(prev_directory,currpath);
            }
            getcwd(path,max_len);
            printf("%s\n",path);
        }
        else if(token[0]=='~' && token[1]=='/'){
            getcwd(currpath,max_len);
            strcpy(path,home);
            int i=1;
            for (i=1;i<strlen(token);i++){
                path[n+i-1]=token[i];
            }
            path[n+i-1]='\0';
            if (chdir(path)!=0){
                perror("chdir");
            }
            else{
                strcpy(prev_directory,currpath);
            }
            getcwd(path,max_len);
            printf("%s\n",path);
        }
        else if(strcmp(token,"~")==0){
            getcwd(currpath,max_len);
            if (chdir(home)!=0){
                perror("chdir");
            }
            else{
                strcpy(prev_directory,currpath);
            }
            getcwd(path,max_len);
            printf("%s\n",path);
        }
        else{
            getcwd(currpath,max_len);
            if (chdir(token)!=0){
            perror("chdir");
            }
            else{
                strcpy(prev_directory,currpath);
            }
            getcwd(path,max_len);
            printf("%s\n",path);
        }
        token=strtok(NULL, " ");
    }
}