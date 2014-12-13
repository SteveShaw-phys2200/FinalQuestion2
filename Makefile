GRAPH = gnuplot
CC = gcc
CFLAGS = -Wall -O0 -g -std=c99
LFLAGS = -O0 -g
LIBS = -lgsl -lm -lgslcblas

all: pend-stable.png pend-unstable.png

pend-stable: pend-stable.o pend-eqs.o
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)

pend-unstable: pend-unstable.o pend-eqs.o
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)

res1: pend-stable
	./pend-stable > res1

res2: pend-unstable
	./pend-unstable > res2

pend-stable.png: pend-stable.gpl res1
	$(GRAPH) pend-stable.gpl

pend-unstable.png: pend-unstable.gpl res2
	$(GRAPH) pend-unstable.gpl
clean : 
	rm -f *~
	rm -f *.o
	rm -f pend-stable
	rm -f pend-unstable
	rm -f res1 res2
veryclean : clean
	rm -f pend-stable.png
	rm -f pend-unstable.png
