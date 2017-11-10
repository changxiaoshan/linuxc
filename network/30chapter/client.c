#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>
#define MAXN 16384
int
main(int argc,char **argv){
    int fd,nchild,nloops,nbytes,i,j,n,nwrite;
    pid_t pid;
    struct sockaddr_in server;
    char request[MAXN],reply[MAXN];
    if(argc !=6 ){
        printf("参数不对\n");
        exit(1);
    }
    nchild=atoi(argv[3]);
    nloops=atoi(argv[4]);
    nbytes=atoi(argv[5]);
    snprintf(request,sizeof(request),"%d",nbytes);
    for(i=0;i<nchild;i++){
        pid=fork();
        if(pid==0){
            for(j=0;j<nloops;j++){
                    fd=socket(AF_INET,SOCK_STREAM,0);
                    server.sin_family=AF_INET;
                    server.sin_port=htons(atoi(argv[2]));
                    inet_pton(AF_INET,argv[1],&server.sin_addr);
                    connect(fd,(struct sockaddr *)&server,sizeof(server));
                    nwrite=write(fd,request,strlen(request));
                    if(nwrite<0){
                        printf("write error\n");
                        exit(1);
                    }
                    n=read(fd,reply,sizeof(reply));
                    reply[n]='\0';
                    printf("%s\n",reply);
                    close(fd);
                }
        }
    }
    while(wait(NULL)>0);
return 0;
}
