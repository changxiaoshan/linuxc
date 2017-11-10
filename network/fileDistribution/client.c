#include "FileDistribution.h"
int main(int argc,char **argv)
{
    int sockfd,conn;
    char *buf="hello";
    char rcvbuf[MAXLEN];
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(SERVER_PORT);
    inet_pton(AF_INET,argv[1],&server.sin_addr);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    conn=connect(sockfd,(struct sockaddr *)&server,sizeof(server));
    if(conn<0)
    {
        perror("connect error:");
        exit(1);
    }
    printf("connect to server:%s\n",buf);
    write(sockfd,buf,sizeof(buf)+1);
    read(sockfd,rcvbuf,MAXLEN);
    printf("recv:%s\n",rcvbuf);
    return 0;
}
