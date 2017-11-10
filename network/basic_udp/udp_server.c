#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#define SERVER_PORT 8001
#define MAXLINE 1024
int main(){
    int sockfd,n;
    char recv[MAXLINE];
    struct sockaddr_in server;
    struct sockaddr client;
    bzero(&server,sizeof(server));
    bzero(&client,sizeof(client));
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("create socket error\n");
        exit(1);
    }
    server.sin_family=AF_INET;
    server.sin_port=htons(SERVER_PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    n=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    if(n<0){
        printf("bind error\n");
        exit(1);
    }

    for(;;){
        socklen_t len;
        n=recvfrom(sockfd,recv,MAXLINE,0,&client,&len);
        recv[n]=0;
        printf("recved data:%s\n",recv);
        sendto(sockfd,recv,n,0,&client,len);
    }   
    return 0;
}
