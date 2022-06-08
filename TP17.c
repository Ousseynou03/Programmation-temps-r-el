#include<signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void handle_signal_1(){

    printf("signal\n");
    printf("Indiquer la durée du timer \n");

    scanf("%d", );
    printf("Indiquer la période du timer");
    scanf("%d", );

}


void main(){
    timer_t timer_1;
   
    struct sigevent event_1;
    struct itimerspec spec_1;

  
    //Installation des handles
    signal(1,handle_signal_1);
    

    //Indiquer une notification désirée
    event_1.sigev_notify = SIGEV_SIGNAL;
    event_1.sigev_signo = 1;


    //Configuration de la période du timer
    spec_1.it_interval.tv_sec = 2;
    spec_1.it_interval.tv_nsec = 0;
    spec_1.it_value = spec_1.it_interval;


    //Allocation du time
    timer_create(CLOCK_REALTIME, & event_1,& timer_1);
    timer_settime(timer_1,0,&spec_1, NULL);

    while(1)
     pause();
}
