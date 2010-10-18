#
# Created: 17 October 2010
# Author : Daniel M. Klein
#

SRCS=main.o list.o
EXEC=main
OBJS=$(SRCS:.c=.o)
CC=gcc
CFLAGS=-c -Wall -O3 --std=c99
LDFLAGS=-lz

all: $(SRCS) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -fr *.o $(EXEC) *.stackdump
