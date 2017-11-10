#include "unp.h"
#include "err.h"
void chlid_func(int signo){
    int status;
    pid_t pid;
    while((pid=waitpid(-1,&status,WNOHANG))>0)
        printf("child:%s terminated status is %d",pid,status);
}
int main(int argc,char **argv){
   struct sockaddr_in server;
   int lisfd,clifd;
   pid_t child;
   struct sigaction nact,oact;
   nact.sa_handler=chlid_func;
   nact.sa_flags=SA_RESTART;
   sigemptyset(&nact.sa_mask);
   lisfd=socket(AF_INET,SOCK_STREAM,0);
   if(lisfd<0)
       err_sys("create socket fd error");
   server.sin_family=AF_INET;
   server.sin_port=htons(SERVER_PORT);
   server.sin_addr.s_addr=htonl(INADDR_ANY);
   bind(lisfd,(struct sockaddr *)&server,sizeof(server));
   sigaction(SIGCHLD,&nact,&oact);
   if(listen(lisfd,10) <0)
       err_sys("listen error");
   for(;;){
        struct sockaddr cli;
        int cli_len;
        cli_len=sizeof(cli);
       clifd=accept(lisfd,&cli,&cli_len);
       if(clifd < 0)
           err_sys("accept error");
       child=fork();
       if(child < 0 )
           err_sys("fork chlid error");
        else if (child == 0) {
            printf("fork chlid");
        }
       else {
            close(clifd);
       }
   }

return 0;
}
