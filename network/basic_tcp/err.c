#include "err.h"
void err_sys(char *msg){
    printf("%s",msg);
    exit(1);
}
