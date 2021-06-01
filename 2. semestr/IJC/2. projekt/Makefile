##
 # Makefile
 # Řešení IJC-DU2, příklad a) i b), 16.4.2020
 # Autor: Iveta Snášelová, FIT
 # Přeloženo: gcc 9.3.0
 # Popis: Implementace makefile pro překlad a spuštění projektu
 #
 ##

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

HTAB_FILES = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_move.o htab_size.o

all: tail wordcount wordcount-dynamic

# ======= Tail =======
tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail #problem when -c?? WHY!!

# ======= Wordcount =========
wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) wordcount.o io.o libhtab.a -o wordcount

# ======= Wordcount dynamicky ========
# Je nutné před spuštěním zadat do termínalu: export LD_LIBRARY_PATH="."
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -fPIC wordcount.o io.o libhtab.so -o wordcount-dynamic

# Při testování htab_move je třeba vožit flag -DMOVETEST
wordcount.o: wordcount.c htab.h htab_struct.h io.h
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o

# ======= Read_word ========
io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o

# ======= Knihovna obsahujicí htab ========
# parametry ar - rcs (replace, create, sort)
libhtab.a: $(HTAB_FILES)
	ar rcs libhtab.a $(HTAB_FILES)

# ======= Knihovna obsahujicí htab dynamicky ==========
libhtab.so: $(HTAB_FILES)
	$(CC) $(CFLAGS) -fPIC -shared $(HTAB_FILES) -o libhtab.so

# Při testování mé vlastní htab_hash_function je třeba vložit -DHASHTEST
htab_hash_function.o: htab_hash_function.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_hash_function.c -o htab_hash_function.o

htab_bucket_count.o: htab_bucket_count.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count.o

htab_clear.o: htab_clear.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear.o

htab_erase.o: htab_erase.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_erase.c -o htab_erase.o

htab_find.o: htab_find.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_find.c -o htab_find.o

htab_for_each.o: htab_for_each.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_for_each.c -o htab_for_each.o

htab_free.o: htab_free.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free.o

htab_init.o: htab_init.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init.o

htab_lookup_add.o: htab_lookup_add.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add.o

htab_move.o: htab_move.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_move.c -o htab_move.o

htab_size.o: htab_size.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_size.c -o htab_size.o

clean:
	rm tail wordcount wordcount-dynamic
	rm libhtab.a libhtab.so
	rm *.o

zip:
	zip xsnase07.zip *c *h Makefile