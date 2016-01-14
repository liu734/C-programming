	CC=gcc
	CFLAGS= -std=c99 -O2 -g
all: miaoruonan

miaoruonan: miaoruonan.o 
	$(CC) $(CFLAGS) -o miaoruonan miaoruonan.o

miaoruonan.o: miaoruonan.c 
	$(CC) $(CFLAGS) -c miaoruonan.c 
