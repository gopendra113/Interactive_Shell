#include"headers.h"

void iman(char * token){
    const char *host = "man.he.net";
    char command[200];
    strcpy(command,token);
    token=strtok(NULL," ");
    if (token!=NULL){
        printf("invalid command\n");
        return;
    }
    else{
        int newStringLength = strlen("/?topic=") + strlen(command) + strlen("&section=all") + 1; 
        char* path = (char*)malloc(newStringLength);
        snprintf(path, newStringLength, "/?topic=%s&section=all", command);
        struct hostent *he = gethostbyname(host);
        if (he == NULL) {
            perror("gethostbyname");
            exit(1);
        }
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            perror("socket");
            exit(1);
        }
        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(80);
        server_addr.sin_addr = *((struct in_addr *)he->h_addr);
        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("connect");
            exit(1);
        }
        char request[200];
        snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host);  
        if (send(sockfd, request, strlen(request), 0) == -1) {
            perror("send");
            exit(1);
        }

        char buffer[1000];
        int bytes_received;
        int start_printing = 0;

        while ((bytes_received = recv(sockfd, buffer, 1000 - 1, 0)) > 0) {
            buffer[bytes_received] = '\0';
            if (!start_printing) {
                char *start_marker = strstr(buffer, "NAME\n");
                if (start_marker != NULL) {
                    start_printing = 1;
                    printf("%s", start_marker);  
                }
            } else {
                    int flag=0;
                    for (int p=0;p<strlen(buffer);p++){
                        if (buffer[p]=='<'){
                            flag=1;
                        }
                        else if(buffer[p]=='>'){
                            flag=0;
                        }
                        else if(flag==0){
                            if (buffer[p]=='&'){
                                if (p+2<strlen(buffer) && buffer[p+1]=='l' && buffer[p+2]=='t'){
                                    printf("<");
                                    p+=2;
                                }
                                else if(p+2<strlen(buffer) && buffer[p+1]=='g' && buffer[p+2]=='t'){
                                    printf("gt");
                                    p+=2;
                                }
                            }
                            else{
                                printf("%c",buffer[p]);
                            }
                            
                        }
                    }
            }
        }
        printf("\n");

        if (bytes_received == -1) {
            perror("recv");
            exit(1);
        }
        close(sockfd);
    }
   
}