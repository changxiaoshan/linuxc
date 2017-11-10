#include "include/FileDistribution.h"
int main(int argc,char **argv)
{   int i,sk,length,clientfd;
    struct sockaddr client;
    struct sockaddr_in server;
    pthread_t tid;
    daemon_init(argv[0]);
    sk=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(SERVER_PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    bind(sk,(struct sockaddr *)&server,sizeof(server));
    listen(sk,QUEUE_LEN);
    for(;;)
    {
        length=sizeof(client);
        clientfd=accept(sk,&client,&length);
        pthread_create(&tid,NULL,str_echo,(void *)clientfd);
    }
    return 0;
}
