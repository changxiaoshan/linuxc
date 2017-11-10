#include "FileDistribution.h"
void daemon_init(char *name)
{
    int i;
    pid_t pid;
    if((pid=fork())<0)
        _exit(-1);
    else if (pid)
        _exit(0);
    if(setsid()<0)
         _exit(-1);
    signal(SIGHUP,SIG_IGN);
    if((pid=fork())<0)
         _exit(-1);
    else if(pid)
        _exit(0);
    chdir("/");
    for(i=0;i<MAXFD;i++)
        close(i);
    open("/dev/null",O_RDWR);
    open("/dev/null",O_RDWR);
    open("/dev/null",O_RDWR);
}
void *str_echo(void *arg)
{
    pthread_detach(pthread_self());
    int fd,n;
    time_t seconds;
    char buf[MAXLEN];
    char *timestr;
    fd=(int)arg;
    while((n=read(fd,buf,MAXLEN))>0)
    {   
        seconds=time(NULL);
        timestr=ctime(&seconds);
        memcpy(buf,timestr,strlen(timestr));
        write(fd,buf,n);
        close(fd);
    }
}
