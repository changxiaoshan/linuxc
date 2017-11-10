#include <syslog.h> 
#include<stdio.h>    
#include<sys/socket.h>
#include<unistd.h>   
#include<string.h>   
#include<netinet/in.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<fcntl.h>
void sig_child(int signo);
void sig_int(int signo);
void web_child(int connfd);
void pr_cpu_time(void);
void dameonize(char *);
#define MAXN 16384

int 
main (int argc,char **argv)
{
    int listenfd,connfd,client_len;
    pid_t child;
    struct sockaddr_in server;
    struct sigaction ochild,nchild,oint,nint;
    struct sockaddr client;
    nchild.sa_handler=sig_child;
    nchild.sa_flags=SA_RESTART;
    
    nint.sa_handler=sig_int;
    nint.sa_flags=SA_RESTART;

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_port=htons(atoi(argv[1]));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htons(INADDR_ANY);

    bind(listenfd,(struct sockaddr *)&server,sizeof(server));
    listen(listenfd,10);

    sigaction(SIGCHLD,&nchild,&ochild);
    sigaction(SIGINT,&nint,&oint);

    while(1){
        client_len=sizeof(client);
        connfd=accept(listenfd,&client,&client_len);
        if(connfd<0){
            if(errno == EINTR)
                continue;
            else
                exit(1);
        }
        child=fork();
        if(child==0){
            close(listenfd);
            web_child(connfd);
        }
        close(connfd);
    }
    return 0;
}

void sig_child(int signo)
{
    pid_t pid;
    int stat;
    while((pid=waitpid(-1,NULL,WNOHANG))>0){
        printf("child:%d terminated:%d\n",pid,stat);
    }
    return;
}

void sig_int(int signo)
{
    pr_cpu_time();
    return;
}

void web_child(int connfd)
{
    int ntowrite,nread;
    char line[MAXN],result[MAXN]="hello world";
    while(1){
        nread=read(connfd,line,MAXN);
        ntowrite=atol(line);
        if(ntowrite <=0 || ntowrite > MAXN)
            exit(1);
        write(connfd,result,strlen(result));
    }
    return ;
}

void pr_cpu_time(void)
{   struct rusage myusage,children;
    int user,sys;
    getrusage(RUSAGE_SELF,&myusage);
    getrusage(RUSAGE_CHILDREN,&children);
    user=myusage.ru_utime.tv_sec+children.ru_utime.tv_sec;
    sys=myusage.ru_stime.tv_sec+children.ru_stime.tv_sec;
    printf("user time:%d,sys time:%d\n",user,sys);
    return;
}
void daemonize(char *cmd){
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct sigaction sa;
    struct rlimit rl;
    umask(0);
    if((pid=fork())<0)
        exit(1);
    else if (pid != 0)
        exit(0);
    setsid();
    sa.sa_handler=SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sigaction(SIGHUP,&sa,NULL);
    if((pid=fork())<0)
        exit(1);               
    else if (pid != 0)         
        exit(0);
    chdir("/");
    for (i=0;i<1024;i++)
        close(i);
    fd0=open("/dev/null",O_RDWR);
    fd1=dup(fd0);
    fd2=dup(fd0);
    openlog(cmd,LOG_CONS,LOG_DAEMON);
}
