// ---------------------------------------------------------------------
// exemple-sched-deadline.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------


#define _GNU_SOURCE

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <linux/sched.h>


#ifndef SCHED_DEADLINE

	#define SCHED_DEADLINE  6

#endif

	#include <sys/syscall.h>

	// Definitions pour x86_64
	#define SCHED_SETATTR_SYSCALL_NB 314
	#define SCHED_GETATTR_SYSCALL_NB 315

	// Definitions pour i386
	//#define SCHED_SETATTR_SYSCALL_NB 351
	//#define SCHED_GETATTR_SYSCALL_NB 352

	// Definitions pour ARM
	//#define SCHED_SETATTR_SYSCALL_NB 380
	//#define SCHED_GETATTR_SYSCALL_NB 381

	// Definitions pour PowerPC
	//#define SCHED_SETATTR_SYSCALL_NB 355
	//#define SCHED_GETATTR_SYSCALL_NB 356

	struct sched_attr {
	  __uint32_t size;

	  __uint32_t sched_policy;
	  __uint64_t sched_flags;

	  /* SCHED_OTHER */
	  __int32_t sched_nice;

	  /* SCHED_FIFO, SCHED_RR */
	  __uint32_t sched_priority;

	  /* SCHED_DEADLINE */
	  __uint64_t sched_runtime; 
	  __uint64_t sched_deadline;
	  __uint64_t sched_period;
	};

#ifndef SCHED_FLAG_RESET_ON_FORK
	#define SCHED_FLAG_RESET_ON_FORK  1
#endif

long sched_getattr(pid_t pid, struct sched_attr * attr, unsigned int size, unsigned int flags)
{
  return syscall(SCHED_GETATTR_SYSCALL_NB, pid, attr, size, flags);
}


long sched_setattr(pid_t pid, struct sched_attr * attr, unsigned int flags)
{
  return syscall(SCHED_SETATTR_SYSCALL_NB, pid, attr, flags);
}


static void rtmin_handler(int unused);

static time_t start_time;

int main(int argc, char * argv[])
{
	long int runtime;
	long int deadline;
	long int period;
	timer_t timer;
	struct sched_attr attr;
	struct sigevent  event;
	struct itimerspec spec;

	if ((argc < 4)
	 || (sscanf(argv[1], "%ld", &runtime)  != 1)
	 || (sscanf(argv[2], "%ld", &deadline) != 1)
	 || (sscanf(argv[3], "%ld", &period)   != 1)) {
		fprintf(stderr, "usage: %s <runtime> <deadline> <period> (all in usec)\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(& attr, 0, sizeof(struct sched_attr));	
	attr.size           = sizeof(struct sched_attr);
	attr.sched_flags    = SCHED_FLAG_RESET_ON_FORK;
	attr.sched_policy   = SCHED_DEADLINE;
	attr.sched_runtime  = runtime * 1000;
	attr.sched_deadline = deadline * 1000;
	attr.sched_period   = period * 1000;
	if (sched_setattr(0, & attr, 0) != 0) {
		perror("sched_setattr");
		exit(EXIT_FAILURE);
	}

	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo  = SIGRTMIN;
	signal(SIGRTMIN, rtmin_handler);


	start_time = time(NULL);

	spec.it_interval.tv_sec  = period / 1000000;
	spec.it_interval.tv_nsec = (period % 1000000) * 1000; // in nsec.
	spec.it_value = spec.it_interval;

	if (timer_create(CLOCK_REALTIME, & event, & timer) != 0) {
		perror("timer_create");
		exit(EXIT_FAILURE);
	}

	if (timer_settime(timer, 0, & spec, NULL) != 0) {
		perror("timer_settime");
		exit(EXIT_FAILURE);
	}

	while(1)
		pause();

	return EXIT_SUCCESS;
}


static void rtmin_handler(int unused)
{
	struct timeval tv;
	static struct timeval prev = {0, 0};
	long int delay;
	static long int min_delay = -1;
	static long int max_delay = -1;
	int change;

	gettimeofday(& tv, NULL);
	if (prev.tv_sec > 0) {
		delay  = (tv.tv_sec - prev.tv_sec) * 1000000
		       + (tv.tv_usec - prev.tv_usec);
		change = 0;
		if ((min_delay < 0) || (delay < min_delay)) {
			min_delay = delay;
			change = 1;
		}
		if ((max_delay < 0) || (delay > max_delay)) {
			max_delay = delay;
			change = 1;
		}
		if (change)
			fprintf(stdout, "[%ld] Min=%ld, Max=%ld\n",
			        time(NULL) - start_time, min_delay, max_delay);
	}
	prev = tv;
}
