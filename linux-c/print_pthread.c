#include<pthread.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
pthread_t ntid1,ntid2;
void * thread_func1(){
    pid_t pid;
    pthread_t self;
    printf("pid:%u,thread id:%u(0x%x)\n",getpid(),pthread_self());
    return ((void *)0);
}
void * thread_func2(){
    printf("thread2 is returning\n");
    return ((void *)2);
}
int main(){
    int err;
    void **ret1,**ret2;
    err=pthread_create(&ntid1,NULL,thread_func1,NULL);
    err=pthread_create(&ntid2,NULL,thread_func2,NULL);
    err=pthread_join(ntid1,ret1);
    printf("thread 1 return code:%d\n",(int)(*ret1));
    err=pthread_join(ntid2,ret2);
    printf("thread 2 return code:%d\n",(int)(*ret2));
    return 0;
}
