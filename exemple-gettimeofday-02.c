// ---------------------------------------------------------------------
// exemple-gettimeofday-02.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


#define MAX_MEASURES 100

int main(int argc, char * argv[])
{
	long int threshold;
	struct timeval now;
	struct timeval start;
	struct timeval previous;
	struct timeval before_preemption[MAX_MEASURES];
	struct timeval after_preemption[MAX_MEASURES];
	long long int duration;

	int nb_measures = 0;
	int i;

	if ((argc != 2)
	 || (sscanf(argv[1], "%ld", &threshold) != 1)) {
		fprintf(stderr, "usage: %s threshold-microsec\n",
		                argv[0]);
		exit(EXIT_FAILURE);
	}
	gettimeofday(&start, NULL);
	previous = start; 

	do {
		gettimeofday(&now, NULL);
		duration  = now.tv_sec - previous.tv_sec;
		duration *= 1000000;
		duration += now.tv_usec - previous.tv_usec;
		if (duration >= threshold) {
			before_preemption[nb_measures] = previous;
			after_preemption[nb_measures] = now;
			nb_measures ++;
			if (nb_measures >= MAX_MEASURES)
				break;
		} 
		previous = now;
	} while (now.tv_sec - start.tv_sec <= 5);
	for (i = 0; i < nb_measures ; i ++)
		printf("[%d] %ld.%06ld  ->  %ld.%06ld\n",
		        i + 1,
		        before_preemption[i].tv_sec,
		        before_preemption[i].tv_usec,
		        after_preemption[i].tv_sec,
		        after_preemption[i].tv_usec);
	return EXIT_SUCCESS;
}

