// ---------------------------------------------------------------------
// exemple-clock-gettime-01.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clock_display(const char * name, clockid_t clock)
{
	struct timespec res;
	struct timespec tim;

	printf("%s : \n", name);
	clock_getres  (clock, & res);
	clock_gettime (clock, & tim);
	printf("   resolution: %ld.%09ld\n", res.tv_sec, res.tv_nsec);
	printf("   time:       %ld.%09ld\n", tim.tv_sec, tim.tv_nsec);
}

int main(void)
{
	clock_display("CLOCK_REALTIME",           CLOCK_REALTIME);	
	clock_display("CLOCK_MONOTONIC",          CLOCK_MONOTONIC);	
	clock_display("CLOCK_PROCESS_CPUTIME_ID", CLOCK_PROCESS_CPUTIME_ID);	
	clock_display("CLOCK_THREAD_CPUTIME_ID",  CLOCK_THREAD_CPUTIME_ID);
	clock_display("CLOCK_MONOTONIC_RAW",      CLOCK_MONOTONIC_RAW);	
	return EXIT_SUCCESS;
}

