# ----------------------------------------------------------------------
# Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
# (C) 2012-2015 - Christophe BLAESS
# http://christophe.blaess.fr
# ----------------------------------------------------------------------

CROSS_COMPILE ?=
CC      = $(CROSS_COMPILE)gcc
CFLAGS  = -Wall -g -pthread
LDFLAGS   = -pthread 
LOADLIBES = -lrt -lm

EXEMPLES=                          \
  exemple-sched-get-priorities     \
  exemple-boucle-temps-reel        \
  exemple-threads-temps-reel       \
  exemple-threads-rr               \
  exemple-sched-deadline           \


.PHONY: all
all : ${EXEMPLES}

.PHONY: clean
clean : 
	@rm -f core *.o *.out *.bb *.bbg *.gcov *.da *~
	@rm -f ${EXEMPLES}

