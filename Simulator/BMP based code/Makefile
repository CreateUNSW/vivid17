CC = gcc
CFLAGS = -gdwarf-2

.PHONY:	clean clobber

all: colour

$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -o $(NAME).o $(NAME).c

qdbmp.o: qdbmp_1.0.0/qdbmp.o
	$(CC) $(CFLAGS) -c -o qdbmp.o qdbmp_1.0.0/qdbmp.c

colour: colour.o qdbmp.o
	$(CC) -o test colour.o qdbmp.o

clean:
	rm -f *.o core

clobber: clean
	rm -f test
