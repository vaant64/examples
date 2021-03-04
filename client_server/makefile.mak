CC = gcc
CFLAGS = -Wall -Werror

all : cprem server

cprem : client.c
	$(CC) $(CFLAGS) -o cprem client.c

server : server.c
	$(CC) $(CFLAGS) -o server server.c

clean :
	$(RM) cprem server
