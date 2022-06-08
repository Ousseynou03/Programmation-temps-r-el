// ---------------------------------------------------------------------
// exemple-threads-rr.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define NB_THREADS 4

void * thread_function(void * arg)
{
	long int number = (long int) arg;

	struct timeval start, previous, now;
	long long int duration;

	sleep(2);

	gettimeofday(&start, NULL);

	now = start;

	while (1) {
		do {
			previous = now;
			gettimeofday(& now, NULL);
			if ((now.tv_sec - start.tv_sec) > 10) // Maxi 10 secondes;
				pthread_exit(NULL);
			duration  = now.tv_sec - previous.tv_sec;
			duration *= 1000000;
			duration += now.tv_usec - previous.tv_usec;
		} while (duration < 1000); // Preemption d'au moins une milliseconde
		fprintf(stdout, "[%ld.%06ld] %ld preempted\n",
		        previous.tv_sec, previous.tv_usec, number);
		fprintf(stdout, "[%ld.%06ld] %ld activated\n",
		        now.tv_sec, now.tv_usec, number);
	}
	
	return NULL;
}


int main(void)
{	
	long int i;
	int err;
	pthread_attr_t attr;
	struct sched_param param;
	pthread_t thr[NB_THREADS];

	pthread_attr_init (& attr);
	if ((err = pthread_attr_setschedpolicy(& attr, SCHED_RR)) != 0) {
		fprintf(stderr, "setschedpolicy: %s\n", strerror(err));
		exit(EXIT_FAILURE);
	}
	if ((err = pthread_attr_setinheritsched(& attr, PTHREAD_EXPLICIT_SCHED)) != 0) {
		fprintf(stderr, "setinheritsched: %s\n", strerror(err));
		exit(EXIT_FAILURE);
	}
	param.sched_priority = 40;
	if ((err = pthread_attr_setschedparam(& attr, & param)) != 0) {
		fprintf(stderr, "setschedparam: %s\n", strerror(err));
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < NB_THREADS; i ++) {
		if ((err = pthread_create(& (thr[i]), & attr, thread_function, (void *) (i+1))) != 0) {
			fprintf(stderr, "pthread_create: %s\n", strerror(err));
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < NB_THREADS; i ++)
		pthread_join(thr[i], NULL);

	return EXIT_SUCCESS;
}

