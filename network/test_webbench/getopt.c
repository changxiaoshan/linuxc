#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<getopt.h>
#include<string.h>
int main(int argc,char *argv[]){
    int opt;
    while((opt=getopt(argc,argv,"v:s:")) != -1){
        switch(opt){
            case 'v':
                printf("%d,%s\n",optind,optarg);
                break;
            case 's':
                printf("%d,%s\n",optind,optarg);
                break;
        }
    }
    int i;
    char *url="http://www.baidu.com";
    printf("%d,%s\n",i=strstr(url,"://")-url+3,strstr(url,"://"));

return 0;
}
