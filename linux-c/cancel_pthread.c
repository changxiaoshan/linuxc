#include<pthread.h>
#include<stdio.h>
void  cleanup(void *args){
    printf("cleanup:%s\n",(char *)args);
}
void * thread_func(){
    printf("thread start\n");
    pthread_cleanup_push(cleanup,"clean up the thread");
    pthread_cleanup_pop(0);
    pthread_exit((void *)0);
}
int main(){
    pthread_t tid;
    int err;
    err=pthread_create(&tid,NULL,thread_func,NULL);
    pthread_join(tid,NULL);
    printf("thread stop\n");
    return 0;
}
