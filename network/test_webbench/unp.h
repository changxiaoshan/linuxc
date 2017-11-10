#ifndef _UNPH_
#define _UNPH_ 

#include<netinet/in.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<string.h> 
#include<arpa/inet.h> 
#include<signal.h>
typedef struct optArg{
    bool head;
    char *hostname;
    char *protocol;
    int method;
}
char *bulid_request(char *url);
int Socket(char *hostname,int port);
void usage();

#endif
