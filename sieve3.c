/*/////////////////////////////////////////////////////////////////////////////
//
// File name : sieve3.c
// Author    : Nissa Osheim
// Date      : 2010/19/10
// Desc      : Finds the primes up to N
//
// updated Wim Bohm
/////////////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

long min(long x, long y) {
    return (x > y) ? y : x;
}

int main(int argc, char **argv) {
    
    long    N = 100,
            blockSize = 30,
            size,
            curr,
            i, j, n, ii,
            count,
            numPrimes,
            start;
    
    long *mark;
    long *primes;
    
    // Time
    double time;
    
    if (argc > 1)
        N = atoi(argv[1]);
    
    if (argc > 2)
        blockSize = atoi(argv[2]);
    
    // Start Timer
    initialize_timer();
    start_timer();
    
    size = (N+1)*sizeof(long);
    mark = (long *)malloc(size);
    
    mark[0] = mark[1] = 1;
    for (i = 2; i <= N; ++i) {
        if (i % 2 == 0)
            mark[i] = 1;
        else
            mark[i] = 0;
    }
    
    curr = 2;
    while (curr*curr <= sqrt(N)) {
        for (i = curr*curr; i <= sqrt(N); i+=curr) {
            mark[i] = 1;
        }
        while (mark[++curr]) ; // Do nothing
    }
    
    // Find numPrimes
    numPrimes = 0;
    for (i = 3; i <= sqrt(N); ++i) {
        if (mark[i] == 0) {
            ++numPrimes;
        }
    }
    
    primes = (long *)malloc((numPrimes+1)*sizeof(long));
    for (i = 3, j = 0; i <= sqrt(N); ++i) {
        if (mark[i] == 0) {
            primes[j] = i;
            ++j;
        }
    }
    
    start = floor(sqrt(N));    
    for (ii = start; ii <= N; ii+=blockSize) {
        for (j = 0; j < numPrimes; ++j) {
            long prime = primes[j];
            long FMIB = (ii + (prime - (ii % prime)));
            for (i = FMIB; i <= min(ii+blockSize, N); i+=prime) {
                mark[i] = 1;
            }
        }
    }
    
    // Stop timer
    stop_timer();
    time = elapsed_time();
    
    // Number of primes
    count = 1;
    for (i = 3; i <= N; i+=2) {
        if (mark[i] == 0) {
            //printf("\t prime %ld\n", i);
            ++count;
        }
    }
    
    // Print results
    printf("There are %ld primes less than or equal to %ld\n", count, N);
    printf("First three primes:");
    j = 1;
    printf("%d ", 2);
    for (i = 3; i <= N && j < 3; i+=2) {
        if (mark[i] == 0) {
            printf("%ld ", i);
            ++j;
        }
    }
    printf("\n");
    /*for (i = 3; i <= N; i+=2) {
        if (mark[i] == 0) {
            printf("%ld ", i);
            ++j;
        }
    }
    printf("\n");*/
    
    printf("Last three primes:");
    j = 0;
    n = (N % 2 ? N : N-1);
    for (i = n; i > 1 && j < 3; i-=2) {
        if (mark[i] == 0) {
            printf("%ld ", i);
            j++;
        }
    }
    printf("\n");
    
    printf("elapsed time = %lf (sec)\n", time);
    
    free(mark);
    return 0;
}


