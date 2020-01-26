CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
SEQFLAGS = -O3 
MATHFLAGS = -lm
EXEC = sieve sieve1 sieve2 sieve3 sieve4

all: $(EXEC)

sieve: sieve.c $(OBJS)
	$(CC) $(SEQFLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)

sieve1: sieve1.c $(OBJS)
	$(CC) $(SEQFLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)

sieve2: sieve2.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)

sieve3: sieve3.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)
	#./sieve3 500000000 100000

sieve4: sieve4.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)
	./sieve4 500000000 100000

timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)

PA3.tar: sieve.c sieve1.c sieve2.c sieve3.c sieve4.c report.pdf makefile
	tar cvf PA3.tar sieve.c sieve1.c sieve2.c sieve3.c sieve4.c report.pdf data.ods makefile

test:
	> data.txt
	for i in 500000000 1000000000 1500000000 ; do \
		echo "n" >> data.txt ; \
		for n in 1 2 3 4 5 6 7 8 ; do \
			export OMP_NUM_THREADS=$$n ; \
			./sieve4 $$i 100000 >> data.txt ; \
		done ; \
	done ;
	javac extractor.java
	java extractor
