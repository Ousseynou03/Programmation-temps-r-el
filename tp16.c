

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


#define NB_MEASURES 30

int main(int argc, char * argv[])																						Q
{
	struct timespec tv[NB_MEASURES];
	int i;
	for (i = 0; i < NB_MEASURES; i ++)
		clock_gettime(CLOCK_REALTIME,&tv[i]);
	for (i = 0; i < NB_MEASURES; i ++)
		printf("%2d : %ld.%06ld\n", i,
		       tv[i].tv_sec, tv[i].tv_nsec);
	return EXIT_SUCCESS;
}

