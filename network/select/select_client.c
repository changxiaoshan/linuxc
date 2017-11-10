#include<errno.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/time.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<math.h>
#define SERVER_PORT 8009
#define MAXLINE 1024
void str_cli(FILE *fp,int fd){
    char recv[MAXLINE],send[MAXLINE];
    int n=0,maxfd;
    fd_set rset;
   for(;;){
   FD_ZERO(&rset);
   FD_SET(fd,&rset);
   FD_SET(fileno(fp),&rset);
   maxfd=fileno(fp)>fd ? fileno(fp): fd;
   select(maxfd+1,&rset,NULL,NULL,NULL);
   if(FD_ISSET(fd,&rset)){
    n=read(fd,recv,MAXLINE);
    if(n>0){
        recv[n]='\0';
        printf("%s",recv);
    }
    else
        exit(1);
   }
    if(FD_ISSET(fileno(fp),&rset)){
        if(fgets(send,MAXLINE,fp)==NULL)
            return;
        write(fd,send,strlen(send));
    }
   }
}
int main(int argc,char **argv){
    int sockfd,err;
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(SERVER_PORT);
    inet_pton(AF_INET,argv[1],&server.sin_addr.s_addr);
    err=connect(sockfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
    if(err<0){
        printf("connect server error\n");
        exit(1);
    }
    str_cli(stdin,sockfd);
    return 0;
}
