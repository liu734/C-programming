	CC=gcc
	CFLAGS= -std=c99 -O2 -g
all: order_book

order_book: order_book.o 
	$(CC) $(CFLAGS) -pthread -o order_book order_book.o -L. -lmarket64

order_book.o: order_book.c market.h libmarket64.a
	$(CC) $(CFLAGS) -c order_book.c -pthread -L. -lmarket64
