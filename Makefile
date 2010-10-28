#
# Created: 17 October 2010
# Author : Daniel M. Klein
#

SRCS=main.o list.o named_tag.o tag_short.o tag_string.o tag_compound.o tag_long.o tag_float.o tag_int.o tag_list.o tag_byte.o tag_byte_array.o tag_double.o tag_print.o
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
