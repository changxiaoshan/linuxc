#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<syslog.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<time.h>
#include<string.h>

#define MAXFD 64
#define QUEUE_LEN 10
#define SERVER_PORT 8001
#define MAXLEN 2048
void daemon_init(char *name);
void sys_err(char *msg);
void *str_echo(void *arg);
