#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{

    int startsec;
    int startusec;
    int stopsec;
	int tempsec;
    int tempusec;
	int stopusec;
    struct timeval tv;

    gettimeofday(&tv,NULL);
    startsec=tv.tv_sec;
    startusec=tv.tv_usec;
    for(int i=0;i<1000000000000;i++){}
    gettimeofday(&tv,NULL);

    stopsec =tv.tv_sec;
    stopusec= tv.tv_usec;

    tempsec = stopsec - startsec;
    tempusec=stopusec- startusec;
    printf("temps= %d,%d\n",tempsec,tempusec);

    return EXIT_SUCCESS;


}