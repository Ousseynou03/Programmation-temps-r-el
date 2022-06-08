#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    if(fork()!=0)
     fork();
     printf("Hello!\n");
exit(0);
}