#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    int x=3;
    printf("Je suis le PERE\n");
    if(fork() !=0){
        x++;
        printf("PERE x=%d\n",x);

    }else{
        x--;
        printf("fils x=%d\n",x);
    }
    return 0;
}