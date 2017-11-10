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
void sig_func(){
    pid_t pid;
    int stat;
    while(pid=waitpid(-1,&stat,WNOHANG))
        printf("child %d terminated,the state is %d\n",stat);
}
int main(int argc,char **argv){
    int listenfd,clientfd,err;
    struct sockaddr_in server,client;
    struct sigaction act;
    act.sa_handler=sig_func;
    act.sa_flag=0;
    act.sa_flags |= SA_RESTART;
    sigemptyset(&act.sa_mask);
    bzero(&server,sizeof(server));
    bzero(&client,sizeof(client));
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0)
        exit(1);
    server.sin_port=htons(SERVER_PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_family=AF_INET;
    err=bind(listenfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
    if(err<0)
        exit(1);
    for(;;){
        int clientlen;
        pid_t child;
        clientlen=sizeof(client);
        listen(listenfd,5);
        clientfd=accept(listenfd,(struct sockaddr *)&client,&clientlen);
        if(clientfd <0 ){
            if(errno == EINTR)
                continue;
        }
        if((child=fork())<0)
            exit(1);
        else if(child != 0){
            //父进程关闭减少客户端套接字的连接次数
            close(clientfd);
        }
        else{
        //子进程处理客户端的连接
        exit(0);
        }
    
    }
    return 0;
}
