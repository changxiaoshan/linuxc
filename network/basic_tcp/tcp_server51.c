#include<error.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<signal.h>
#include<wait.h>
#define SERVER_PORT 8009
#define MAXLINE 1024
void str_echo(int clientfd){
    int n;
    char buf[MAXLINE];
    while((n=read(clientfd,buf,MAXLINE))>0){
        buf[n]='\0';
        printf("%s",buf);
        write(clientfd,buf,n);
    }
}
void sig_fuc(){
    pid_t pid;
    int stat;
    while((pid=waitpid(-1,&stat,WNOHANG))>0)
        printf("child %d terminated: %d\n",pid,stat);
}
int main(int argc,char **argv){
    int listenfd,connfd;
    pid_t childpid;
    struct sockaddr_in cliaddr,serveraddr;
    struct sigaction nact,oact;
    nact.sa_handler=sig_fuc;
    sigemptyset(&nact.sa_mask);
    nact.sa_flags=0;
    nact.sa_flags |=SA_RESTART;
    sigaction(SIGCHLD,&nact,&oact);
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htons(SERVER_PORT);
    if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0){
        printf("bind error\n");
        exit(1);
    }
    else{
        listen(listenfd,10);
        while(1){
        socklen_t cli_len=sizeof(cliaddr);
        connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&cli_len);
        if(connfd<0){
            if(errno ==EINTR)
                continue;
        }
        else{
            if((childpid=fork())==0){
                close(listenfd);
                str_echo(connfd);
                exit(0);
            }
            close(connfd);
            }
        }
    }
return 0;
}
