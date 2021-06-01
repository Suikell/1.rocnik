##
 # ppm.c
 # Řešení IJC-DU1, příklad a), 18.3.2020
 # Autor: Iveta Snášelová, FIT
 # Přeloženo: gcc 9.3.0
 # Popis: Implementace makefilu
##

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2


all: primes primes-i steg-decode

primes: primes.o bitset.o eratosthenes.o error.o
	$(CC) $(CFLAGS) primes.o bitset.o eratosthenes.o error.o -o primes -lm

primes-i: primes-i.o bitset-i.o eratosthenes.o error.o
	$(CC) $(CFLAGS) primes-i.o bitset-i.o eratosthenes.o error.o -DUSE_INLINE -o primes-i -lm

steg-decode: steg-decode.c ppm.o bitset.o eratosthenes.o error.o
	$(CC) $(CFLAGS) steg-decode.c ppm.o bitset.o eratosthenes.o error.o -o steg-decode -lm



primes.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -o primes.o

primes-i.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -DUSE_INLINE -o primes-i.o

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -c bitset.c -o bitset.o

bitset-i.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -c bitset.c -DUSE_INLINE -o bitset-i.o

eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o -lm

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o


run: primes primes-i
	ulimit -s unlimited && time ./primes
	ulimit -s unlimited && time ./primes-i

clean:
	rm primes primes-i steg-decode
	rm *.o

zip:
	zip xsnase07.zip *.c *.h Makefile
