#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

void main(){
    struct timespec temps_actuel;
    clock_gettime(CLOCK_MONOTONIC,&temps_actuel);
    printf("seconds:%ld\n nano seconde : %ld",temps_actuel.tv_sec,temps_actuel.tv_nsec);
}