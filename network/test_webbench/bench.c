#include<netinet/in.h> 
#include<sys/types.h> 
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<string.h> 
#include<arpa/inet.h> 
#include<signal.h>
#include<getopt.h>
#include<errno.h>
#define REQUEST_SIZE 4096

char request[REQUEST_SIZE];
typedef struct argList {
    char *uri;
    char *hostname;
    char *data;
    char **headers;
    int num;
}argList;

char *build_request(argList *arg){
    int i=0;
    memset(request,0,REQUEST_SIZE);
    if(arg->data){
        sprintf(request,"POST %s HTTP/1.1\r\n",arg->uri);
    }
    else{
        sprintf(request,"GET %s HTTP/1.1\r\n",arg->uri);
    }
    for(i;i<arg->num;i++){
        strcat(request,arg->headers[i]);
        strcat(request,"\r\n");
    }
    strcat(request,"\r\n");
    if(arg->data){
        strcat(request,arg->data);
        strcat(request,"\r\n\r\n");
    }
    return request;
}

int Socket(char *hostname,int port){
    struct sockaddr_in server;
    struct hostent *hp;
    int sock;
    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    hp=gethostbyname("i360mall.com");
    memcpy(&server.sin_addr,hp->h_addr,hp->h_length);
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        printf("create socket error!!!");
        exit(1);
    }
    if(connect(sock,(struct sockaddr *)&server,sizeof(server))<0){
        printf("connect error!!!");
        exit(1);
    }
    return sock;
}

void err_sys(char *msg){
    perror(msg);
    exit(-1);
}

argList * get_arg_list(int argc,char **argv){
    if(argc<2){
        err_sys("参数非法:");
    }
    int opt,dnum=0,headNum=0,hostLen=0;
    argList *userArg=NULL;
    char *ptr=NULL,*uri=NULL;
    userArg=(argList *)malloc(sizeof(argList));
    userArg->headers=(char **)malloc(sizeof(char **));
    userArg->data=NULL;
    while((opt=getopt(argc,argv,"d:h:u:")) != -1){
        switch(opt){
            case 'd':
                if(dnum>1){
                    err_sys("只能有一个d参数：");
                }
                userArg->data=(char *)malloc(sizeof(optarg));
                strcpy(userArg->data,optarg);
                printf("%s",userArg->data);
                dnum++;
                break;
            case 'h':
                userArg->headers[headNum]=(char *)malloc(sizeof(optarg));
                strcpy(userArg->headers[headNum],optarg);
                headNum++;
                userArg->num=headNum;
                break;
            case 'u':
                ptr=strchr(optarg,'/')+2;
                uri=strchr(ptr,'/');
                userArg->uri=(char *)malloc(sizeof(uri));
                strcpy(userArg->uri,uri);
                hostLen=uri-ptr;
                userArg->hostname=(char *)malloc(sizeof(hostLen));
                strncpy(userArg->hostname,ptr,hostLen);
                break;
            default:
                printf("usage\n");
                break;
        }
    }
    return userArg;
}

int main(int argc,char **argv){
    int i;
    pid_t pid=0;
    argList *userArg=NULL;
    userArg=get_arg_list(argc,argv);
    build_request(userArg);
    for(i=0;i<1;i++){
        int sock;
        char rcv[REQUEST_SIZE*100];
        memset(rcv,0,REQUEST_SIZE);
        sock=Socket(userArg->hostname,80);
        write(sock,request,strlen(request));
        read(sock,rcv,REQUEST_SIZE);
        printf("sock:%s\n",rcv);
    }
    return 0;
}
