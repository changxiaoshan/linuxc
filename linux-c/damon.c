#include<fcntl.h>
#include<unistd.h>
#include<wait.h>
#include<syslog.h>
#include<stdlib.h>
#include<sys/resource.h>
#include<time.h>
void demaon(void){
    }
int main(){
    struct sigaction act;
    pid_t pid;
    struct rlimit rl;
    int i=0,fd0,fd1,fd2,log;
    getrlimit(RLIMIT_NOFILE,&rl);
    if((pid=fork())<0)
        exit(1);
    else if (pid !=0)
        exit(0);
    umask(0);
    setsid();
    act.sa_handler=SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGHUP,&act,NULL);
    if((pid=fork())<0)
        exit(1);
    else if (pid !=0)
        exit(0);
    chdir("/");
    for(i;i<rl.rlim_max;i++)
        close(i);
    fd0=open("/dev/null",O_RDWR);
    fd1=dup(0);
    fd2=dup(0);
    int log,line=4096,i=0;
    char *line="hello";
    demaon();
    log=open("/home/xschang/record.log",O_RDWR | O_CREAT);
    for(i;i<line;i++){
        write(log,line,sizeof(line));
        sleep(1);
    }   
    return 0;
}
