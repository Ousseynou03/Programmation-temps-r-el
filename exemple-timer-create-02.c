// ---------------------------------------------------------------------
// exemple-timer-create-02.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


static timer_t timer = (timer_t) 0;
static long int * measure = NULL;
static int nb_measures = 0;
static int nb_measures_total = 0;

void handler_signal(int inutilise)
{
	struct timespec now;
	static struct timespec previous = { 0, 0} ;

	clock_gettime (CLOCK_REALTIME, &now);
	if (previous.tv_sec > 0) {
		measure[nb_measures]  = now.tv_sec  - previous.tv_sec;
		measure[nb_measures] *= 1000000000;
		measure[nb_measures] += now.tv_nsec - previous.tv_nsec;
		nb_measures ++;
	}
	previous = now;
	if (nb_measures == nb_measures_total)
		timer_delete(timer);
}


int main(int argc, char * argv[])
{
	long int period;
	struct sigevent event;
	struct itimerspec spec;
	
	if ((argc != 2) || (sscanf(argv[1], "%ld", &period) != 1)){
		fprintf(stderr, "usage: %s period_microsec\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Allouer le tableau de mesures
	nb_measures_total = 5000000 / period; // 5 seconds
	if ((measure = calloc(nb_measures_total, sizeof(struct timespec))) == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	// Configurer le timer
	signal(SIGRTMIN, handler_signal);
	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo  = SIGRTMIN;
	period = period * 1000;  // en nanosec
	spec.it_interval.tv_sec  = period / 1000000000;
	spec.it_interval.tv_nsec = period % 1000000000;
	spec.it_value = spec.it_interval;
	// Allouer le timer
	if (timer_create(CLOCK_REALTIME, & event, & timer) != 0) {
		perror("timer_create");
		exit(EXIT_FAILURE);
	} 
	// Programmer le timer
	if (timer_settime(timer, 0, &spec, NULL) != 0) {
		perror("timer_settime");
		exit(EXIT_FAILURE);
	}
	// Attendre le dernier signal
	while (nb_measures < nb_measures_total)
		pause();
	// Afficher les mesures en micro-secondes
	for (nb_measures = 0; nb_measures < nb_measures_total; nb_measures ++)
		printf("%ld\n", measure[nb_measures]/1000);
	return EXIT_SUCCESS;
}

