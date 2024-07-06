#include"headers.h"


#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"


container** data;


int is_greater(container* first,container* second){
    int n1=strlen(first->name);
    int n2=strlen(second->name);
    if (n1<=n2){
        for (int i=0;i<n1;i++){
            if (first->name[i]<second->name[i]){
                return 0;
            }
            else if(first->name[i]>second->name[i]){
                return 1;
            }
        }
        return 0;
    }
    else{
        for (int i=0;i<n2;i++){
            if (first->name[i]<second->name[i]){
                return 0;
            }
            else if(first->name[i]>second->name[i]){
                return 1;
            }
        }
        return 1;
    }
}
void merge(container** data,int l,int r){
    container ** arr=(container** )malloc(sizeof(container*)*(r-l+1));
    for (int i=0;i<(r-l+1);i++){
        arr[i]=(container*)malloc(sizeof(container));
    }
    int i=l,j=((l+r)/2)+1;
    int k=0;
    while(i<=(l+r)/2 && j<=r && i>=0 && j>=0){
        if (is_greater(data[i],data[j])){
            *(arr[k++])=*(data[i++]);
        }
        else{
            *(arr[k++])=*(data[j++]);
        }
    }
    while(i<=(l+r)/2 && i>=0){
        *(arr[k++])=*(data[i++]);
    }
    while(j<=r && j>=0){
        *(arr[k++])=*(data[j++]);
    }
    k=0;
    for (int p=l;p<=r;p++){
        *(data[p])=*(arr[k]);
        free(arr[k++]);
    }
    free (arr);
}
void sort(container** data,int l,int r){
    if (l!=r && l<r && l>=0 && r>=0){
        sort(data,l,(l+r)/2);
        sort(data,((l+r)/2)+1,r);
        merge(data,l,r);
    }
}
void msort(container** data,int n){
    if (n>=0){
        sort(data,0,n-1);
    }
}

void displaymode(mode_t mode) {
    (S_ISDIR(mode)) ? printf("d") : printf("-"); 
    (S_ISLNK(mode))  ? printf("l") : printf("-"); 
    (mode & S_IRUSR) ? printf("r") : printf("-"); 
    (mode & S_IWUSR) ? printf("w") : printf("-"); 
    (mode & S_IXUSR) ? printf("x") : printf("-"); 
    (mode & S_IRGRP) ? printf("r") : printf("-");  
    (mode & S_IWGRP) ? printf("w") : printf("-"); 
    (mode & S_IXGRP) ? printf("x") : printf("-"); 
    (mode & S_IROTH) ? printf("r") : printf("-"); 
    (mode & S_IWOTH) ? printf("w") : printf("-"); 
    (mode & S_IXOTH) ? printf("x") : printf("-"); 
}


void read_dir(DIR *dir,struct dirent *entry,int *count,int n,const char* path){
    if ((entry = readdir(dir)) != NULL){
        (*count)++;
        read_dir(dir,entry,count,n+1,path);
        data[n]=(container*)malloc(sizeof(container));
        strcpy(data[n]->name,entry->d_name);

        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", path, entry->d_name);
        
        struct stat fileStat;
    
        if (stat(filePath, &fileStat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        strncpy(data[n]->name, entry->d_name, sizeof(data[n]->name));
        data[n]->mode = fileStat.st_mode;
        data[n]->uid = fileStat.st_uid;
        data[n]->gid = fileStat.st_gid;
        data[n]->size = fileStat.st_size;
        data[n]->mtime = fileStat.st_mtime;
        data[n]->nlink = fileStat.st_nlink;
    }
    else{
        data=(container**)malloc(sizeof(container*)*(*count));
    }
}


void peek(char *token,char *home,char * prev_directory){
    const char delimiter[] = " ";
    char* path=(char*)malloc(sizeof(char)*max_len);
    path[0]='\0';
    int flag_a=0,flag_l=0,flag_al=0;
    token=strtok(NULL, delimiter);
        while (token!=NULL){
            if (strcmp(token,"-a")==0){
                flag_a=1;
            }
            else if(strcmp(token,"-l")==0){
                flag_l=1;
            }
            else if(strcmp(token,"-al")==0 || strcmp(token,"-la")==0){
                flag_al=1;
            }
            else{
                strcpy(path,token);
            }
            token=strtok(NULL, delimiter);
        }
    int count;
    DIR *dir;
    struct dirent *entry;
    char* ab_path=(char*)malloc(sizeof(char)*max_len);
    if (strcmp(path,"~")==0){
        strcpy(ab_path,home);
    }
    else if(strcmp(path,"-")==0){
        strcpy(ab_path,prev_directory);
    }
    else if (path[0]=='\0' || strcmp(path,".")==0){
        getcwd(ab_path,max_len);
    }
    else{
        if (realpath(path, ab_path) == NULL) {
            perror("realpath");
            exit(EXIT_FAILURE);
        }
    }
    free(path);
    dir = opendir(ab_path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    count = 0;
    read_dir(dir,entry,&count,0,ab_path);
    closedir(dir);

    msort(data,count);
    struct passwd *pwd;
    struct group *grp;
    char time[100];
    for (int i = 0; i < count; i++) {
        if ((flag_a==0 && flag_al==0) && (strcmp(data[i]->name,".")==0 || strcmp(data[i]->name,"..")==0)){
            continue;
        }
        if (flag_l==1 || flag_al==1){
            pwd = getpwuid(data[i]->uid);
            grp = getgrgid(data[i]->gid);
            strftime(time, sizeof(time), "%b %d %H:%M", localtime(&data[i]->mtime));

            displaymode(data[i]->mode);
            printf("%2ld %8s %8s %8ld %s",
                    (long) data[i]->nlink,
                    (pwd!= NULL) ? pwd->pw_name : "unknown",
                    (grp!= NULL) ? grp->gr_name : "unknown",
                    (long) data[i]->size,
                    time);
        }
        
        if (S_ISDIR(data[i]->mode)) {
            printf(ANSI_COLOR_BLUE " %s" ANSI_COLOR_RESET, data[i]->name);
        }
        else if (data[i]->mode & S_IXUSR) {
            printf(ANSI_COLOR_GREEN " %s" ANSI_COLOR_RESET, data[i]->name);
        }
        else {
            printf(" %s", data[i]->name);
        }
        if (flag_l==1 || flag_al==1){
            printf("\n");
        }
        free(data[i]);
    }
    if (flag_l==0 && flag_al==0){
            printf("\n");
        }
    
    free(ab_path);
    free(data);
}

