#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

int main()
{

    int startsec;
    int startnsec;
    int stopsec;
	int tempsec;
    int tempnsec;
	int stopnsec;

    struct timespec tv;

    clock_gettime(CLOCK_REALTIME,&tv);
    startsec=tv.tv_sec;
    startnsec=tv.tv_nsec;
    for(int i=0;i<100;i++){}
    clock_gettime(CLOCK_REALTIME,&tv);

    stopsec =tv.tv_sec;
    stopnsec= tv.tv_nsec;

    tempsec = stopsec - startsec;
    tempnsec=stopnsec- startnsec;
    printf("temps= %d,%d\n",tempsec,tempnsec);

    return EXIT_SUCCESS;


}