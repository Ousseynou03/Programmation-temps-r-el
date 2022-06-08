#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
    pid_t fils_pid;
    printf("Bonjour je suis le PERE avec pid %d\n", getpid());
    fils_pid=fork();
    if(fils_pid==0)
    printf("Je suis le fils avec pid %d\n",getpid());
    else
    printf("Rebonjour je suis le PERE avec pid %d\n",getpid());
    printf("fin\n");
}
