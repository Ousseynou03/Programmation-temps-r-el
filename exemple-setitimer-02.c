// ---------------------------------------------------------------------
// exemple-setitimer-02.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void signal_handler(int unused)
{
	struct timeval now;
	static struct timeval previous = { 0, 0 };

	long int duration;
	static long int min_duration = -1;
	static long int max_duration =  0;
	static long int duration_sum = 0;
	float  average_duration = 0.0;
	static int nb_measures;

	gettimeofday(&now, NULL);
	if (previous.tv_sec > 0) {
		duration  = now.tv_sec  - previous.tv_sec;
		duration *= 1000000;  // conversion en micro-sec
		duration += now.tv_usec - previous.tv_usec;
		if ((min_duration < 0) || (min_duration > duration))
			min_duration = duration;
		if (max_duration < duration)
			max_duration = duration;
		duration_sum += duration;
		nb_measures ++;
		if (nb_measures == 1000) {
			average_duration = (float) duration_sum / nb_measures;
			printf("min=%4ld  max=%4ld  moy=%.0f\n",
			       min_duration, max_duration, average_duration);
			min_duration = -1;
			max_duration = 0;
			duration_sum = 0;
			nb_measures = 0;
		}
	}
	previous = now;
}


int main(int argc, char * argv[])
{
	struct itimerval timer;
	// Installer le handler du signal SIGALRM
	signal(SIGALRM, signal_handler);
	// Preparer la structure itimerval
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 1000; // 1000 us = 1 ms
	timer.it_value = timer.it_interval;
	// Programmer le timer
	setitimer(ITIMER_REAL, & timer, NULL);
	while (1) 
		pause();
	return EXIT_SUCCESS;
}

