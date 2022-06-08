// ---------------------------------------------------------------------
// exemple-perturbateur.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


int main(void)
{
	struct timeval now;
	struct timeval loop_start;
	struct timeval programme_start;
	long long int  duration;

	gettimeofday(& programme_start, NULL);

	while (1) {
		gettimeofday(& loop_start, NULL);
		do {
			gettimeofday(& now, NULL);
			duration  = now.tv_sec - loop_start.tv_sec;
			duration *= 1000000;
			duration += now.tv_usec - loop_start.tv_usec;
		} while (duration < 100);

		usleep(20);

		duration  = now.tv_sec - programme_start.tv_sec;
		duration *= 1000000;
		duration += now.tv_usec - programme_start.tv_usec;
	
		if ((now.tv_sec - programme_start.tv_sec) > 10)
			break;
	}
	return EXIT_SUCCESS;
}
