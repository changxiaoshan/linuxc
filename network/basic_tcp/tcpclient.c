#include "unp.h"
#include "err.h"
char recv[MAXLINE];
char send[MAXLINE];
int main(int argc,char **argv){
    struct sockaddr_in server;
    int fd,n;
    fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        err_sys("socket fd error");
    server.sin_family=AF_INET;
    sever.sin_port=htons(SERVER_PORT);
    inet_pton(AF_INET,argv[1],&server.sin_addr);
    n=connect(fd,(struct sockaddr *)&server,sizeof(server));
    if(n<0)
        err_sys("connet error");
    while(fgets(send,MAXLINE,stdin) != NULL){
        printf("%s",send);
        write(fd,send,strlen(send)+1);   
    }
return 0;
}
