#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//NB/ Connaître le nombre de boucle qui peuvent s'exécuter dans notre machine
int main(int argc, char * argv[])
{
	time_t start;
	long int nb_loops;
	long int nb_loops_max;

	start = time(NULL);
	
	nb_loops = 0;
	//Exécution de la boucle pendant dix secondes.
	while (time(NULL) < (start + 10)) {
		nb_loops ++;
	}
	fprintf(stdout, "[%d] nb loops : %ld ", getpid(), nb_loops);
	if ((argc == 2) && (sscanf(argv[1], "%ld", & nb_loops_max) == 1)) {
		fprintf(stdout, "(%.0f)", 100.0 * (float) nb_loops / nb_loops_max);
	}
	fprintf(stdout, "\n");
	return EXIT_SUCCESS;

}

