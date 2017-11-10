#include<fcntl.h>
#include<syslog.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

#define MAXFD 64
int daemon_init(const char *pathname,int facility)
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
    openlog(pathname,LOG_PID,facility);
    return 0;
}
int main(int argc,char **argv)
{

    return 0;
}
