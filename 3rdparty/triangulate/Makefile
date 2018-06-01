inclpath = .

CC=gcc

CFLAGS= -UCLOCK -I$(inclpath)


# DEBUG: turn on debugging output
#
# STANDALONE: run as a separate program. read data from file.
#	      If this flag is False, then use the interface procedure 
#	      triangulate_polygon() instead.


LDFLAGS= -lm

SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:./%.c=./%.o)
INCLUDES = $(shell find . -name "*.h")
LIB = libtriangulate.a

default_target: $(LIB)

$(LIB): $(OBJS)
	ar -rv $@ $^

$(OBJS): %.o: %.c $(INCLUDES)
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -f $(OBJS)
	rm -f $(LIB)
.PHONY : clean
