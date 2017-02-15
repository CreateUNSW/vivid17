// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Queue function implementations for COMP1927 17x1 AE2.

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Graph.h"

// Node representation (stores each edge)
struct _node {
	Edge e;
	Node next;
};

// Queue representation
struct _queue {
	Node head;
	Node tail;
};

// Creates an empty queue
Queue newQueue(void) {

	// Creates space for new queue
	Queue q = malloc(sizeof(*q));
	mallocCheck(q);
	q->head = NULL;
	q->tail = NULL;

	return q;
}

void destroyQueue(Queue q) {

	mallocCheck(q);

	// Pointers to keep track of
	Node prev = NULL;
	Node curr = q->head;

	// Frees the nodes of the queue
	while(curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}

	// Frees the queue itself
	free(q);
}

void joinQueue(Queue q, Edge e) {
	
	mallocCheck(q);

	// Creates the new node in the queue
	Node new = malloc(sizeof(*new));
	mallocCheck(new);
	new->e = e;
	new->next = NULL;

	// Attaches it to the queue

	// If queue is empty, sets it to the new head
	if(q->head == NULL) {
		q->head = new;
	}
	// If the queue has a tail, attaches it onto the tail
	if(q->tail != NULL) {
		q->tail->next = new;
	}

	// Unconditionally sets new as the new tail
	q->tail = new;
}

Edge leaveQueue(Queue q) {

	// Ensures queue exists and is non-empty
	mallocCheck(q);
	mallocCheck(q->head);

	// Temp node to store head while it's being pulled out of queue
	Node temp = q->head;

	// Retrieves the edge from the head of the queue
	Edge e = temp->e;

	// Bridges next node to become the new head
	q->head = temp->next;

	// Frees the old head
	free(temp);

	// Handles case where queue is now empty
	if(q->head == NULL) {
		q->tail = NULL;
	}

	return e;
}

int queueSize(Queue q) {

	// Ensures queue is non-empty
	mallocCheck(q);

	int size = 0;
	Node curr = q->head;
	
	// Goes through the queue until it hits the end
	while(curr != NULL) {
		size++;
		curr = curr->next;
	}

	return size;
}