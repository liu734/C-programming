	CC=gcc
	CFLAGS= -std=c99 -O2 -g
all: order_book

order_book: order_book.o
	$(CC) $(CFLAGS) -o order_book order_book.o

order_book.o: order_book.c
	$(CC) $(CFLAGS) -c order_book.c
