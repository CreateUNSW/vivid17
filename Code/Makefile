CC = gcc
CFLAGS = -Wall -Werror -gdwarf-2

.PHONY:	clean clobber

all: assn2

$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c -o $(NAME).o $(NAME).c

assn2: main.o Graph.o Agent.o Queue.o PQ.o Item.o
	$(CC) -o assn2 main.o Graph.o Agent.o Queue.o PQ.o Item.o

test: testGraph.o Graph.o Queue.o
	$(CC) -o testGraph testGraph.o Graph.o Queue.o

clean:
	rm -f *.o core

clobber: clean
	rm -f assn2