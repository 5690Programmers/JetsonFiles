SHELL = /bin/sh
CFLAGS = -g
LDFLAGS = 
CC = gcc
##############################################################################

PROGRAM = server
PROGRAM2 = client
OBJECTS = server.o
OBJECTS2 = client.o
SOURCES = server.c
SOURCES2 = client.c
COMMON_OBJS = open_sockets.o packets.o
ALLSOURCES = client.c server.c open_sockets.c packets.c

##############################################################################
.DEFAULT_GOAL := all
.c.o:   
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $*.o $<

$(PROGRAM) : $(OBJECTS) $(COMMON_OBJS)
	$(CC) -o $(LDFLAGS) $(PROGRAM) $(OBJECTS) $(COMMON_OBJS) $(LIBRARIES)

$(OBJECTS) : $(SOURCES)
	$(CC) -c $(CFLAGS) -DSERVER $(INCLUDES) -o $(OBJECTS) $(SOURCES)

$(PROGRAM2) : $(OBJECTS2) $(COMMON_OBJS)
	$(CC) -o $(LDFLAGS) $(PROGRAM2) $(OBJECTS2) $(COMMON_OBJS) $(LIBRARIES)

$(OBJECTS2) : $(SOURCES2)
	$(CC) -c $(CFLAGS) -DCLIENT $(INCLUDES) -o $(OBJECTS2) $(SOURCES2)

clean : 
	-rm -f *.o
	-rm -f *~
	-rm -f *.lst
	-rm -f $(PROGRAM2) $(PROGRAM)

depend : Makefile
	makedepend -f Makefile $(ALLSOURCES)

all : $(PROGRAM2) $(PROGRAM)

# DO NOT DELETE THIS LINE -- make depend depends on it.
