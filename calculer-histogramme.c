// ---------------------------------------------------------------------
// calculer-histogramme.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LINE_LENGTH   1024

int main(int argc, char * argv[])
{
	char line[LINE_LENGTH];
	int nb_measures;
	int nb_samples;

	double measure;
	double minimum = -1;
	double maximum = 0;
	double sample_width;
	int *  samples;

	int i;

	if ((argc != 4)
	 || (sscanf(argv[1], "%d", & nb_samples) != 1)
	 || (sscanf(argv[2], "%lf", & minimum) != 1)
	 || (sscanf(argv[3], "%lf", & maximum) != 1)) {
		fprintf(stderr, "usage: %s  nb_samples  minimum  maximum\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (nb_samples <= 0) {
		fprintf(stderr, "Invalid value : %d\n", nb_samples);
		exit(EXIT_FAILURE);
	}

	sample_width = (double) (maximum - minimum) / nb_samples;
	samples = calloc(nb_samples, sizeof(int));

	nb_measures = 0;
	while (fgets(line, LINE_LENGTH, stdin) != NULL) {
		if (sscanf(line, "%lf", &measure) != 1) {
			fprintf(stderr, "Read error on line %d\n", nb_measures + 1);
			exit(EXIT_FAILURE);
		}
		i = (int) (measure - minimum )/ sample_width;
		if ((i < 0) || (i >= nb_samples)) {
			fprintf(stderr, "Invalid value on line %d\n", nb_measures + 1);
			exit(EXIT_FAILURE);
		}
		samples[i] ++;
	}
	for (i = 0; i < nb_samples; i ++)
		printf("%.0lf %d\n",
		       minimum + (i + 0.5) * sample_width,
		       samples[i]);
	return EXIT_SUCCESS;
}

