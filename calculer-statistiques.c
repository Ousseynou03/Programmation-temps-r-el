// ---------------------------------------------------------------------
// calculer-statistiques.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LINE_LENGTH   1024

int main(int argc, char * argv[])
{
	// L'algorithme  implemente par ce programme est
	// presente  sur la page  Wikipedia  "Algorithms
	// for Calculating Variance". Il  est  construit
	// autour d'une idee de  Donald E. Knuth decrite
	// dans le second volume de "The Art of Computer
	// Programming".

	char line[LINE_LENGTH];

	double measure;
	int    nb_measures = 0;
	double minimum;
	double maximum;
	double average  =  0.0;
	double variance =  0.0;
	double delta;
	double standard_deviation;

	while (fgets(line, LINE_LENGTH, stdin) != NULL) {
		if (sscanf(line, "%lf", & measure) != 1) {
			fprintf(stderr, "Read error, line %d\n",
			        nb_measures+1);
			exit(EXIT_FAILURE);
		}
		nb_measures ++;
		if ((nb_measures == 1) || (minimum > measure))
			minimum = measure;
		if ((nb_measures == 1) || (maximum < measure))
			maximum = measure;
		delta = measure - average;
		average  += delta / nb_measures;
		variance += delta * (measure - average);
	}
	if (nb_measures > 1)
		variance = variance / (nb_measures - 1);

	standard_deviation = sqrt(variance);

	printf(" Nb measures = %d\n Minimum = %.0lf\n Maximum = %.0lf\n"
	       " Average = %.0lf\n  Standart deviation = %.0lf\n",
	        nb_measures, minimum, maximum, average, standard_deviation);

	return EXIT_SUCCESS;
}

