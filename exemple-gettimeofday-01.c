// ---------------------------------------------------------------------
// exemple-gettimeofday-01.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


#define NB_MEASURES 30

int main(int argc, char * argv[])
{
	struct timeval tv[NB_MEASURES];
	int i;
	for (i = 0; i < NB_MEASURES; i ++)
		gettimeofday(& (tv[i]), NULL);
	for (i = 0; i < NB_MEASURES; i ++)
		printf("%2d : %ld.%06ld\n", i,
		       tv[i].tv_sec, tv[i].tv_usec);
	return EXIT_SUCCESS;
}

