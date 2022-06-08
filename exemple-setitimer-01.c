// ---------------------------------------------------------------------
// exemple-setitimer-01.c
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
	fprintf(stderr, "*");
}

int main(int argc, char * argv[])
{
	struct itimerval timer;
	// Installer le handler du signal SIGALRM
	signal(SIGALRM, signal_handler);
	// Preparer la structure itimerval
	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;
	timer.it_value = timer.it_interval;
	// Programmer le timer
	setitimer(ITIMER_REAL, & timer, NULL);
	while (1) 
		pause();
	return EXIT_SUCCESS;
}

