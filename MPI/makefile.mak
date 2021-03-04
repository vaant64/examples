CC = mpicc
CFLAGS = -Wall -Werror

all : run

run : main.c
	$(CC) $(CFLAGS) -o run main.c -lm

clean :
	$(RM) run results.txt plot.dat
