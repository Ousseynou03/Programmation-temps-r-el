// ---------------------------------------------------------------------
// exemple-clock-gettime-02.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int i;
	struct timespec measure[30];
	long int elapsed;

	for (i = 0; i < 30; i ++)
		clock_gettime(CLOCK_REALTIME, &(measure[i]));

	for (i = 0; i < 30; i ++) {
		if (i > 0) {
			elapsed  = measure[i].tv_sec - measure[i-1].tv_sec;
			elapsed *= 1000000000;
			elapsed += measure[i].tv_nsec - measure[i-1].tv_nsec;
		} else {
			elapsed = 0;
		}
		fprintf(stdout, "%ld.%09ld  %9ld\n",
	                 measure[i].tv_sec, measure[i].tv_nsec, elapsed);
	}
	return EXIT_SUCCESS;
}
