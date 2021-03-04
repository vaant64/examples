.PHONY: all clean

EXEC = xpat
LIBS = -lX11 -lm
HEADDIR = -I.
CC = cc #$(HEADDIR)
CFLAGS = -Wall
OBJECTS = xpat0.o xpat1.o
INCLUDES = xpat.h

all : $(EXEC)
	
$(EXEC) : $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(LIBS)

clean :
	$(RM) *.o xpat
