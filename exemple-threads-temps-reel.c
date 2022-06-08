// ---------------------------------------------------------------------
// exemple-threads-temps-reel.c
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
	int i, j;

	sleep(number*2);

	fprintf(stderr, "Thread %ld starts at %ld\n", number, time(NULL));
	for (i = 0; i < 500000; i ++)
		for (j = 0; j < 10000; j ++)
			;
	fprintf(stderr, "Thread %ld ends at %ld\n", number, time(NULL));
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
	if ((err = pthread_attr_setschedpolicy(& attr, SCHED_FIFO)) != 0) {
		fprintf(stderr, "setschedpolicy: %s\n", strerror(err));
		exit(EXIT_FAILURE);
	}
	if ((err = pthread_attr_setinheritsched(& attr, PTHREAD_EXPLICIT_SCHED)) != 0) {
		fprintf(stderr, "setinheritsched: %s\n", strerror(err));
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < NB_THREADS; i ++) {
		param.sched_priority = (i + 1) * 10;
		if ((err = pthread_attr_setschedparam(& attr, & param)) != 0) {
			fprintf(stderr, "setschedparam: %s\n", strerror(err));
			exit(EXIT_FAILURE);
		}
		if ((err = pthread_create(& (thr[i]), & attr, thread_function, (void *) (i+1))) != 0) {
			fprintf(stderr, "pthread_create: %s\n", strerror(err));
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < NB_THREADS; i ++)
		pthread_join(thr[i], NULL);

	return EXIT_SUCCESS;
}

