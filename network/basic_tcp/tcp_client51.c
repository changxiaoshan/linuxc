#include "unp.h"
int main(int argc,char **argv){
    int socketfd,n;
    struct sockaddr_in serveraddr;
    if(argc != 2)
        exit(1);
    struct sigaction nact,oact;
    nact.sa_handler=sig_func;
    sigemptyset(&nact.sa_mask);
    nact.sa_flags=0;
    nact.sa_flags |= SA_RESTART;
    sigaction(SIGPIPE,&nact,&oact);
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&serveraddr,sizeof(struct sockaddr_in));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(SERVER_PORT);
    inet_pton(AF_INET,argv[1],&serveraddr.sin_addr);
    n=connect(socketfd,(struct sockaddr *)&serveraddr,sizeof(struct sockaddr));
    if(n<0){
        printf("connect error\n");
        exit(1);
    }
    else{
        str_cli(stdin,socketfd);
    }
    return 0;
}
void str_cli(FILE *fp,int socketfd){  
        char sendline[MAXLINE],recvline[MAXLINE];  
            int n;  
            while(fgets(sendline,MAXLINE,fp) != NULL){  
                write(socketfd,sendline,strlen(sendline));  
                    if((n=read(socketfd,recvline,MAXLINE))==0)  
                            exit(1);  
                    else{  
                            printf("%s",recvline);  
                        }  
        }  
}    
void sig_func(){  
        printf("SIGPIPIPE\n");  
} 
