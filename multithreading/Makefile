CC = gcc
CFLAGS = -Wall -Werror -gdwarf-2

.PHONY:	clean clobber

all: test

$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -o $(NAME).o $(NAME).c

test: test.o
	$(CC) -o test test.o

clean:
	rm -f *.o core

clobber: clean
	rm -f test