#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>  
#include<fcntl.h> 
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>
#include <sys/resource.h>
void daemonize(void);
int main(int argc,char **argv){
    DIR *dirfd;
    struct dirent *cmd;
    char pathname[255];
    int fd,nwrite;
    char *data=" ";
    if(argc !=2){
        exit(1);
    }
    daemonize();
    for(;;){ 
	dirfd=opendir(argv[1]);
        while((cmd=readdir(dirfd))!=NULL)
        {
            memset(pathname,0,sizeof(pathname));
            strcat(pathname,argv[1]);
            strcat(pathname,"/");
            if(cmd->d_type != 8){
                continue;
            }
            strcat(pathname,cmd->d_name);
            fd=open(pathname,O_WRONLY | O_TRUNC);
            if(fd<0){
                exit(1);
            }
	    lseek(fd,0,SEEK_SET);
            nwrite=write(fd,data,strlen(data));
            if(nwrite<=0){
                exit(1);
            }
	    fsync(fd);
            close(fd);
        }
    closedir(dirfd);
    sleep(5);
    }
    return 0;
}
void daemonize()
{
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;
    umask(0);
    if((pid=fork())<0)
            exit(1);
    else if (pid!=0)
        exit(0);
    setsid();
    sa.sa_handler=SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sigaction(SIGHUP,&sa,NULL);
    if((pid=fork())<0)
        exit(1);
    else if(pid !=0)
        exit(0);
    chdir("/");
    rl.rlim_max=1024;
    for(i=0;i<rl.rlim_max;i++)
        close(i);
    fd0=open("/dev/null",O_RDWR);
    fd1=dup(0);
    fd2=dup(0);
    return ;
}
